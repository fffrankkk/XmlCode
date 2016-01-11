/*******************************************************************************
 * Source.cpp
 *
 * Created on: 2015-10-26
 *     Author: fuliang
 *******************************************************************************/

#include "Source.h"
#include "XmlCode.h"
#include "Utility.h"
#include "BUtility.h"
#include "ClassCont.h"

/*******************************************************************************
 * construction
 *******************************************************************************/
CSource::CSource()
{
    Cout.open(SRC_FILE, ios::app);
}

/*******************************************************************************
 * deconstruction
 *******************************************************************************/
CSource::~CSource()
{
    Cout.close();
}

void CSource::Core(vector<CClassDetail *>& vecDetail)
{
    WriteCommit2Commit(vecDetail);
    Cout << "bool CConfig::Parse(const char* pszFile)\n{" << endl;
    Cout << "\tCXMLTree CXMLTreeIns;\n\tif(!CXMLTreeIns.Create(pszFile)) return false;\n" << endl;
    Cout << "\tCXMLNode* pCRoot = CXMLTreeIns.GetRoot();\n\tif(pCRoot == NULL) return false;\n" << endl;
    for (BT_AUTO(iterDetail, vecDetail.begin()); iterDetail != vecDetail.end(); ++iterDetail) {
        CClassDetail* pCDetail = *iterDetail;
        if (pCDetail->GetType() == "s") {
            if (!pCDetail->GetMember().empty()) {
                // C
                WriteC(pCDetail);
            } else {
                // string
                WriteString(pCDetail);
            }
        } else if (pCDetail->GetType() == "m") {
            if (!pCDetail->GetMember().empty()) {
                // vector<C>
                WriteVectorC(pCDetail);
            } else {
                // vector<string>
                WriteVectorString(pCDetail);
            }
        }
    }
    Cout << "\treturn true;\n}\n" << endl;
    Cout << "} // CFG_N" << endl;
}

void CSource::WriteVectorC(CClassDetail* pCDetail)
{
    // c and mutil
    string strVec = string("m_vec") + NUtility::First2Up(pCDetail->GetName());
    string strType = string("C") + NUtility::First2Up(pCDetail->GetName());
    string strIns = strType + "Ins";
    // node name, attribute name
    map<string, vector<string> > mapAttr = GetNameWithAttribute(pCDetail);

    Cout << "\t{" << endl;
    Cout << "\t\t" << "// parse " << pCDetail->GetName() << endl;
    Cout << "\t\t" << "std::vector<CXMLNode *> vecChildren = pCRoot->GetChildren(\"" << pCDetail->GetName() << "\");" << endl;
    Cout << "\t\t" << "if (vecChildren.empty()) return false;" << endl;
    Cout << "\t\t" << "for (std::vector<CXMLNode *>::iterator iterChild = vecChildren.begin(); iterChild != vecChildren.end(); ++iterChild) {" << endl;
    Cout << "\t\t\tCXMLNode* pCChild = *iterChild;" << endl;
    Cout << "\t\t\t" << strType << " " << strIns << ";" << endl;
    map<string, vector<string> >::iterator iterAttr = mapAttr.find(pCDetail->GetName());
    if (iterAttr != mapAttr.end()) {
            for (unsigned int uiCount = 0; uiCount < iterAttr->second.size(); ++uiCount) {
            Cout << "\t\t\t" << strIns << ".Set" << NUtility::First2Up(pCDetail->GetName()) << \
                NUtility::First2Up(iterAttr->second[uiCount]) << "(pCChild->GetAttribute(\"" << \
                iterAttr->second[uiCount] << "\"));" << endl;
        }
    }
    Cout << "\t\t\tstd::vector<CXMLNode *> vecNodes = pCChild->GetChildren();" << endl;
    Cout << "\t\t\tfor (std::vector<CXMLNode *>::iterator iterNode = vecNodes.begin(); iterNode != vecNodes.end(); ++iterNode) {" << endl;
    Cout << "\t\t\t\tCXMLNode* pCNode = *iterNode;" << endl;
    bool bIf = true;
    vector<CClassMember *> vecMem = pCDetail->GetMember();
    for (unsigned int uiCount = 0; uiCount < vecMem.size(); ++uiCount) {
        CClassMember* pCMem = vecMem[uiCount];
        if (pCMem->GetType() == "a") {
            continue;
        }
        if (bIf) {
            Cout << "\t\t\t\tif ";
            bIf = false;
        } else {
            Cout << " else if ";
        }
        Cout << "(pCNode->GetName() == \"" << pCMem->GetName() <<  "\") {" << endl;
        iterAttr = mapAttr.find(pCMem->GetName());
        if (iterAttr != mapAttr.end()) {
            for (unsigned int uiCount = 0; uiCount < iterAttr->second.size(); ++uiCount) {
                Cout << "\t\t\t\t\t" << strIns << ".Set" << NUtility::First2Up(pCMem->GetName()) << \
                   NUtility::First2Up(iterAttr->second[uiCount]) << "(pCNode->GetAttribute(\"" << \
                   iterAttr->second[uiCount] << "\"));" << endl;
            }
        }
        if (pCMem->GetType() == "c") {
            Cout << "\t\t\t\t\t" << strIns << ".Set" << NUtility::First2Up(pCMem->GetName()) << \
                "(pCNode->GetValue());" << endl;
        } else if (pCMem->GetType() == "c+") {
            Cout << "\t\t\t\t\t" << strIns << ".Add" << NUtility::First2Up(pCMem->GetName()) << \
                "(pCNode->GetValue());" << endl;
        }
        Cout << "\t\t\t\t}";
    }
    Cout << endl;

    Cout << "\t\t\t}" << endl;
    Cout << "\t\t\t" << strVec << ".push_back(" << strIns << ");" << endl;
    Cout << "\t\t}" << endl;
    Cout << "\t}" << endl;
}

void CSource::WriteC(CClassDetail* pCDetail)
{
    string strIns = string("m_C") + NUtility::First2Up(pCDetail->GetName());
    // node name, attribute name
    map<string, vector<string> > mapAttr = GetNameWithAttribute(pCDetail);

    // c and single
    Cout << "\t{" << endl;
    Cout << "\t\t" << "// parse " << pCDetail->GetName() << endl;
    Cout << "\t\t" << "std::vector<CXMLNode *> vecChildren = pCRoot->GetChildren(\"" << pCDetail->GetName() << "\");" << endl;
    Cout << "\t\t" << "if (vecChildren.size() != 1) return false;" << endl;
    Cout << "\t\t" << "CXMLNode* pCNode = vecChildren[0];" << endl;
    map<string, vector<string> >::iterator iterAttr = mapAttr.find(pCDetail->GetName());
    if (iterAttr != mapAttr.end()) {
        for (unsigned int uiCount = 0; uiCount < iterAttr->second.size(); ++uiCount) {
            Cout << "\t\t" << strIns << ".Set" << NUtility::First2Up(pCDetail->GetName()) << \
                NUtility::First2Up(iterAttr->second[uiCount]) << "(pCNode->GetAttribute(\"" << \
                iterAttr->second[uiCount] << "\"));" << endl;
        }
    }

    Cout << "\t\tstd::vector<CXMLNode *> vecNodes = pCNode->GetChildren();" << endl;
    Cout << "\t\tfor (std::vector<CXMLNode *>::iterator iterNode = vecNodes.begin(); iterNode != vecNodes.end(); ++iterNode) {" << endl;
    Cout << "\t\t\tCXMLNode* pCNode = *iterNode;" << endl;
    bool bIf = true;
    vector<CClassMember *> vecMem = pCDetail->GetMember();
    for (unsigned int uiCount = 0; uiCount < vecMem.size(); ++uiCount) {
        CClassMember* pCMem = vecMem[uiCount];
        if (pCMem->GetType() == "a") {
            continue;
        }
        if (bIf) {
            Cout << "\t\t\tif ";
            bIf = false;
        } else {
            Cout << " else if ";
        }
        Cout << "(pCNode->GetName() == \"" << pCMem->GetName() <<  "\") {" << endl;

        iterAttr = mapAttr.find(pCMem->GetName());
        if (iterAttr != mapAttr.end()) {
            for (unsigned int uiCount = 0; uiCount < iterAttr->second.size(); ++uiCount) {
                Cout << "\t\t\t\t" << strIns << ".Set" << NUtility::First2Up(pCMem->GetName()) << \
                   NUtility::First2Up(iterAttr->second[uiCount]) << "(pCNode->GetAttribute(\"" << \
                   iterAttr->second[uiCount] << "\"));" << endl;
            }
        }
        if (pCMem->GetType() == "c") {
            Cout << "\t\t\t\t" << strIns << ".Set" << NUtility::First2Up(pCMem->GetName()) << \
                "(pCNode->GetValue());" << endl;
        } else if (pCMem->GetType() == "c+") {
            Cout << "\t\t\t\t" << strIns << ".Add" << NUtility::First2Up(pCMem->GetName()) << \
                "(pCNode->GetValue());" << endl;
        }
        Cout << "\t\t\t}";
    }
    Cout << endl;
    Cout << "\t\t}" << endl;

    Cout << "\t}" << endl;
}

void CSource::WriteVectorString(CClassDetail* pCDetail)
{
    // no member and mutil
    Cout << "\t{" << endl;
    Cout << "\t\t" << "// parse " << pCDetail->GetName() << endl;
    Cout << "\t\t" << "std::vector<CXMLNode *> vecChildren = pCRoot->GetChildren(\"" << pCDetail->GetName() << "\");" << endl;
    Cout << "\t\t" << "if (vecChildren.empty()) return false;" << endl;
    Cout << "\t\t" << "for (std::vector<CXMLNode *>::iterator iterChild = vecChildren.begin(); iterChild != vecChildren.end(); ++iterChild) {" << endl;
    Cout << "\t\t\tm_vec" << NUtility::First2Up(pCDetail->GetName()) << ".push_back((*iterChild)->GetValue());" << endl;
    Cout << "\t\t}" << endl;
    Cout << "\t}" << endl;
}

void CSource::WriteString(CClassDetail* pCDetail)
{
    // no member and single
    Cout << "\t{" << endl;
    Cout << "\t\t" << "// parse " << pCDetail->GetName() << endl;
    Cout << "\t\t" << "std::vector<CXMLNode *> vecChildren = pCRoot->GetChildren(\"" << pCDetail->GetName() << "\");" << endl;
    Cout << "\t\t" << "if (vecChildren.size() != 1) return false;" << endl;
    Cout << "\t\tm_str" << NUtility::First2Up(pCDetail->GetName()) << " = vecChildren[0]->GetValue();" << endl;
    Cout << "\t}" << endl;
}

void CSource::WriteCommit2Commit(vector<CClassDetail *>& vecDetail)
{
    CClassCont CCont;
    Cout << CCont.GetFileComment(SRC_FILE) << endl;
    Cout << CCont.GetInclude("Config.h");
    Cout << CCont.GetInclude("XMLTree.h") << endl;
    Cout << "#include <stdlib.h>" << endl;
    Cout << endl;

    Cout << "namespace CFG_N {\n" << endl;

    Cout << "CConfig* CConfig::sm_pCIns = new CConfig;\n" << endl;

    for (unsigned int uiCount = 0; uiCount < vecDetail.size(); ++uiCount) {
        if (!vecDetail[uiCount]->GetMember().empty()) {
            Cout << CCont.SrcStruct(string("C") + NUtility::First2Up(vecDetail[uiCount]->GetName())) << endl;
        }
    }

    Cout << \
        string("/*******************************************************************************\n") + \
        string(" * construction\n") + \
        string(" *******************************************************************************/\n") +\
        string("CConfig::CConfig") + string("()\n{\n\tatexit(CConfig::DestroyInstance);\n}\n\n") + \
        string("/*******************************************************************************\n") + \
        string(" * deconstruction\n") + \
        string(" *******************************************************************************/\n") + \
        string("CConfig::~CConfig") + string("()\n{\n\n}\n");

    Cout << "/*******************************************************************************" << endl;
    Cout << " * destroy instance" << endl;
    Cout << " *******************************************************************************/" << endl;
    Cout << "void CConfig::DestroyInstance()" << endl;
    Cout << "{" << endl;
	Cout << "\tif (sm_pCIns != NULL) {" << endl;
    Cout << "\t\tdelete sm_pCIns;\n\t\tsm_pCIns = NULL;\n\t}" << endl;
    Cout << "}\n" << endl;
    Cout << "/*******************************************************************************" << endl;
    Cout << " * parse all parameters" << endl;
    Cout << " * Parameters:" << endl;
    Cout << " * pszFile: xml file" << endl;
    Cout << " * Return-Value: success return true, or else return false." << endl;
    Cout << " *******************************************************************************/" << endl;
}

map<string, vector<string> > CSource::GetNameWithAttribute(CClassDetail* pCDetail)
{
    map<string, vector<string> > mapAttr;
    vector<CClassMember *> vecMem = pCDetail->GetMember();
    for (BT_AUTO(iterMem, vecMem.begin()); iterMem != vecMem.end(); ++iterMem) {
        CClassMember* pCMem = *iterMem;
        if (pCMem->GetType() == "a") {
            string strName = pCMem->GetName();
            string strAttr = pCMem->GetAttrName();
            mapAttr[strName.substr(0, strName.length() - strAttr.length())].push_back(strAttr);
        }
    }
    return mapAttr;
}
