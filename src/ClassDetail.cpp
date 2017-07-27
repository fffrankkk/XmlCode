/*******************************************************************************
 * ClassDetail.cpp
 *
 * Created on: 2015-10-25
 *     Author: fuliang
 *******************************************************************************/

#include "BUtility.h"
#include "Utility.h"
#include "ClassDetail.h"
#include "ClassCont.h"

#include <iostream>
#include <algorithm>

CClassMember::CClassMember()
{
}

CClassMember::~CClassMember()
{
}

void CClassMember::SetAttrName(const string& strAttrName)
{
    m_strAttrName = strAttrName;
}

string CClassMember::GetAttrName()
{
    return m_strAttrName;
}

void CClassMember::SetName(const string& strName)
{
    m_strName = strName;
}

void CClassMember::SetType(const string& strType)
{
    m_strType = strType;
}

string CClassMember::GetName()
{
    return m_strName;
}

string CClassMember::GetType()
{
    return m_strType;
}

void CClassMember::Print()
{
    cout << "member name:" << m_strName << "\t" << m_strType << endl;
}

/*******************************************************************************
 * construction
 *******************************************************************************/
CClassDetail::CClassDetail()
{

}

/*******************************************************************************
 * deconstruction
 *******************************************************************************/
CClassDetail::~CClassDetail()
{

}

void CClassDetail::SetName(const string& strName)
{
    m_strName = strName;
}

string CClassDetail::GetName()
{
    return m_strName;
}

void CClassDetail::SetType(const string& strType)
{
    m_strType = strType;
}

string CClassDetail::GetType()
{
    return m_strType;
}

vector<CClassMember *>& CClassDetail::GetMember()
{
    return m_vecMem;
}


void CClassDetail::AddAttribute(const string& strName, const string& strAttr)
{
    BT_AUTO(iterMem, m_vecAttr.begin());
    for (; iterMem != m_vecAttr.end() && (*iterMem)->GetName() != strName; ++iterMem);
    if (iterMem == m_vecAttr.end()) {
        CClassMember* pCMem = new CClassMember;
        pCMem->SetName(strName);
        pCMem->SetType("a");
        pCMem->SetAttrName(strAttr);
        m_vecAttr.push_back(pCMem);
    }
}

void CClassDetail::AddMember(const string& strName, const string& strType)
{
    BT_AUTO(iterMem, m_vecMem.begin());
    for (; iterMem != m_vecMem.end() && (*iterMem)->GetName() != strName; ++iterMem);
    if (iterMem == m_vecMem.end()) {
        CClassMember* pCMem = new CClassMember;
        pCMem->SetName(strName);
        pCMem->SetType("c");
        m_vecMem.push_back(pCMem);
    } else {
        CClassMember* pCMem = *iterMem;
        if (strType == "c+" && strType != pCMem->GetType()) {
            pCMem->SetType("c+");
        }
    }
}

vector<CClassDetail *> CClassDetail::GetChildren()
{
    vector<CClassDetail *> vecChildren;
    for (BT_AUTO(iterChild, m_mapChildren.begin()); iterChild != m_mapChildren.end(); ++iterChild) {
        vecChildren.push_back(iterChild->second);
    }
    return vecChildren;
}

CClassDetail* CClassDetail::GetChild(const string& strName)
{
    map<string, CClassDetail*>::iterator iterFind = m_mapChildren.find(strName);
    return iterFind != m_mapChildren.end() ? iterFind->second : NULL;
}

vector<string> CClassDetail::GenerateDeclare(const int& iLevel)
{
    string strBeg(iLevel, '\t');
    vector<string> vecLines;
    vecLines.push_back(strBeg + string("class C") + NUtility::First2Up(m_strName));
    vecLines.push_back(strBeg + "{");
    if (!m_mapChildren.empty()) {
        vecLines.push_back(strBeg + "\tpublic:");
        for (map<string, CClassDetail*>::iterator iterChild = m_mapChildren.begin(); iterChild != m_mapChildren.end(); ++iterChild) {
            vector<string> vecChild = iterChild->second->GenerateDeclare(iLevel + 2);
            for (vector<string>::iterator iterChildLine = vecChild.begin(); iterChildLine != vecChild.end(); ++iterChildLine) {
                vecLines.push_back(*iterChildLine);
            }
        }
    }
    vecLines.push_back(strBeg + "\tpublic:");
    vecLines.push_back(strBeg + string("\t\tC") + NUtility::First2Up(m_strName) + "();");
    vecLines.push_back(strBeg + string("\t\t~C") + NUtility::First2Up(m_strName) + "();");
    vecLines.push_back("");
    if (iLevel == 0) {
        vecLines.push_back(strBeg + "\t\tbool ParseFromXML(const char* pszFile);");
        vecLines.push_back("");
        vecLines.push_back(strBeg + "\t\tstatic inline CConfig* GetInstance();");
        vecLines.push_back(strBeg + "\t\tstatic void DestroyInstance();");
    } else {
        vecLines.push_back(strBeg + "\t\tbool ParseFromNode(CXMLNode* pCNode);");
    }
    vecLines.push_back("");

    for (vector<CClassMember *>::iterator iterAttr = m_vecAttr.begin(); iterAttr != m_vecAttr.end(); ++iterAttr) {
        vecLines.push_back(strBeg + string("\t\tinline const string& Get") + NUtility::First2Up((*iterAttr)->GetName()) + "();");
        vecLines.push_back(strBeg + string("\t\tinline const string& Get") + NUtility::First2Up((*iterAttr)->GetName()) + "() const;");
        vecLines.push_back("");
    }

    for (vector<CClassMember *>::iterator iterMember = m_vecMem.begin(); iterMember != m_vecMem.end(); ++iterMember) {
        if ((*iterMember)->GetType() == "c") {
            vecLines.push_back(strBeg + string("\t\tinline const string& Get") + NUtility::First2Up((*iterMember)->GetName()) + "();");
            vecLines.push_back(strBeg + string("\t\tinline const string& Get") + NUtility::First2Up((*iterMember)->GetName()) + "() const;");
            vecLines.push_back("");
        } else if ((*iterMember)->GetType() == "c+") {
            vecLines.push_back(strBeg + string("\t\tinline const vector<string>& Get") + NUtility::First2Up((*iterMember)->GetName()) + "();");
            vecLines.push_back(strBeg + string("\t\tinline const vector<string>& Get") + NUtility::First2Up((*iterMember)->GetName()) + "() const;");
            vecLines.push_back("");
        }
    }

    for (map<string, CClassDetail*>::iterator iterChild = m_mapChildren.begin(); iterChild != m_mapChildren.end(); ++iterChild) {
        if (iterChild->second->GetType() == "s") {
            vecLines.push_back(strBeg + "\t\tinline const C" +  NUtility::First2Up(iterChild->first) + "& Get" +  NUtility::First2Up(iterChild->first) + "();");
            vecLines.push_back(strBeg + "\t\tinline const C" +  NUtility::First2Up(iterChild->first) + "& Get" +  NUtility::First2Up(iterChild->first) + "() const;");
            vecLines.push_back("");
        } else if (iterChild->second->GetType() == "m") {
            vecLines.push_back(strBeg + "\t\tinline const vector<C" + NUtility::First2Up(iterChild->first) + ">& Get" + NUtility::First2Up(iterChild->first) + "();");
            vecLines.push_back(strBeg + "\t\tinline const vector<C" + NUtility::First2Up(iterChild->first) + ">& Get" + NUtility::First2Up(iterChild->first) + "() const;");
            vecLines.push_back("");
        }
    }
    if (m_vecMem.empty() && m_mapChildren.empty()) {
        vecLines.push_back(strBeg + "\t\tinline const string& GetValue();");
        vecLines.push_back(strBeg + "\t\tinline const string& GetValue() const;");
        vecLines.push_back("");
    }

    vecLines.erase(vecLines.begin() + vecLines.size() - 1);
    vecLines.push_back(strBeg + "\tprivate:");

    vector<pair<string, string> > vecMem;
    size_t zuMaxLength = 0;
    for (vector<CClassMember *>::iterator iterAttr = m_vecAttr.begin(); iterAttr != m_vecAttr.end(); ++iterAttr) {
        //vecLines.push_back(strBeg + string("\t\tstring m_str") + NUtility::First2Up((*iterAttr)->GetName()) + ";");
        vecMem.push_back(make_pair("string", string("m_str") + NUtility::First2Up((*iterAttr)->GetName())));
        if (vecMem[vecMem.size() - 1].first.length() > zuMaxLength) {
            zuMaxLength = vecMem[vecMem.size() - 1].first.length();
        }
    }

    for (vector<CClassMember *>::iterator iterMember = m_vecMem.begin(); iterMember != m_vecMem.end(); ++iterMember) {
        if ((*iterMember)->GetType() == "c") {
            //vecLines.push_back(strBeg + string("\t\tstring m_str") + NUtility::First2Up((*iterMember)->GetName()) + ";");
            vecMem.push_back(make_pair("string", string("m_str") + NUtility::First2Up((*iterMember)->GetName())));
            if (vecMem[vecMem.size() - 1].first.length() > zuMaxLength) {
                zuMaxLength = vecMem[vecMem.size() - 1].first.length();
            }
        } else if ((*iterMember)->GetType() == "c+") {
            //vecLines.push_back(strBeg + string("\t\vector<string> m_vec") + NUtility::First2Up((*iterMember)->GetName()) + ";");
            vecMem.push_back(make_pair("vector<string>", string("m_vec") + NUtility::First2Up((*iterMember)->GetName())));
            if (vecMem[vecMem.size() - 1].first.length() > zuMaxLength) {
                zuMaxLength = vecMem[vecMem.size() - 1].first.length();
            }
        }
    }
    for (map<string, CClassDetail*>::iterator iterChild = m_mapChildren.begin(); iterChild != m_mapChildren.end(); ++iterChild) {
        if (iterChild->second->GetType() == "m") {
            //vecLines.push_back(strBeg + string("\t\tvector<") + NUtility::First2Up(iterChild->first) + "> m_C" + NUtility::First2Up(iterChild->first) + ";");
            vecMem.push_back(make_pair(string("vector<C") + NUtility::First2Up(iterChild->first) + ">", string("m_vec") + NUtility::First2Up(iterChild->first)));
            if (vecMem[vecMem.size() - 1].first.length() > zuMaxLength) {
                zuMaxLength = vecMem[vecMem.size() - 1].first.length();
            }
        } else if (iterChild->second->GetType() == "s") {
            //vecLines.push_back(strBeg + string("\t\tC") + NUtility::First2Up(iterChild->first) + " m_C" + NUtility::First2Up(iterChild->first) + ";");
            vecMem.push_back(make_pair(string("C") + NUtility::First2Up(iterChild->first), string("m_C") +  NUtility::First2Up(iterChild->first)));
            if (vecMem[vecMem.size() - 1].first.length() > zuMaxLength) {
                zuMaxLength = vecMem[vecMem.size() - 1].first.length();
            }
        }
    }
    if (m_vecMem.empty() && m_mapChildren.empty()) {
        vecMem.push_back(make_pair("string", "m_strValue"));
    }
    for (vector<pair<string, string> >::iterator iterPair = vecMem.begin(); iterPair != vecMem.end(); ++iterPair) {
        vecLines.push_back(strBeg + "\t\t" +  iterPair->first + string(zuMaxLength - iterPair->first.length() + 1, ' ') + iterPair->second + ";");
    }
    if (iLevel == 0) {
        vecLines.push_back(strBeg + "\tprivate:");
        vecLines.push_back(strBeg + "\t\tstatic CConfig* sm_pCInstance;");
    }
    vecLines.push_back(strBeg + "};");
    return vecLines;
}

vector<string> CClassDetail::GenerateGet(const string& strBase)
{
    CClassCont CCont;
    vector<string> vecLines;

    string strClass = string("C") + NUtility::First2Up(m_strName);
    if (!strBase.empty()) {
        strClass = strBase + "::" + strClass;
    } else {
        vecLines.push_back(CCont.StrGetCommentStart());
        vecLines.push_back(" * get instance");
        vecLines.push_back(" * Return-Value: instance");
        vecLines.push_back(CCont.StrGetCommentEnd());
        vecLines.push_back("inline CConfig* CConfig::GetInstance()");
        vecLines.push_back("{");
        vecLines.push_back("\treturn sm_pCInstance;");
        vecLines.push_back("}");
        vecLines.push_back("");
    }
    for (vector<CClassMember *>::iterator iterAttr = m_vecAttr.begin(); iterAttr != m_vecAttr.end(); ++iterAttr) {
        vecLines.push_back(CCont.SrcGet(strClass, "string", NUtility::First2Up((*iterAttr)->GetName()), string("m_str") + NUtility::First2Up((*iterAttr)->GetName()),false));
        vecLines.push_back(CCont.SrcGet(strClass, "string", NUtility::First2Up((*iterAttr)->GetName()), string("m_str") + NUtility::First2Up((*iterAttr)->GetName()),true));
        /*vecLines.push_back(string("inline const string& Get") + NUtility::First2Up((*iterAttr)->GetName()) + "();");
        vecLines.push_back(string("inline const string& Get") + NUtility::First2Up((*iterAttr)->GetName()) + "(); const");
        vecLines.push_back("");*/
    }

    if (m_vecMem.empty() && m_mapChildren.empty()) {
        vecLines.push_back(CCont.SrcGet(strClass, "string", "Value", "m_strValue", false));
        vecLines.push_back(CCont.SrcGet(strClass, "string", "Value", "m_strValue", true));
    }

    for (vector<CClassMember *>::iterator iterMember = m_vecMem.begin(); iterMember != m_vecMem.end(); ++iterMember) {
        if ((*iterMember)->GetType() == "c") {
            vecLines.push_back(CCont.SrcGet(strClass, "string", NUtility::First2Up((*iterMember)->GetName()), string("m_str") + NUtility::First2Up((*iterMember)->GetName()),false));
            vecLines.push_back(CCont.SrcGet(strClass, "string", NUtility::First2Up((*iterMember)->GetName()), string("m_str") + NUtility::First2Up((*iterMember)->GetName()),true));

            /*vecLines.push_back(string("inline const string& Get") + NUtility::First2Up((*iterMember)->GetName()) + "();");
            vecLines.push_back(string("inline const string& Get") + NUtility::First2Up((*iterMember)->GetName()) + "() const;");
            */
            vecLines.push_back("");
        } else if ((*iterMember)->GetType() == "c+") {
            vecLines.push_back(CCont.SrcGet(strClass, "vector<string>", NUtility::First2Up((*iterMember)->GetName()), string("m_vec") + NUtility::First2Up((*iterMember)->GetName()),false));
            vecLines.push_back(CCont.SrcGet(strClass, "vector<string>", NUtility::First2Up((*iterMember)->GetName()), string("m_vec") + NUtility::First2Up((*iterMember)->GetName()),true));
         //   vecLines.push_back("");
        }
    }

    for (map<string, CClassDetail*>::iterator iterChild = m_mapChildren.begin(); iterChild != m_mapChildren.end(); ++iterChild) {
        if (iterChild->second->GetType() == "s") {
            string strName = (strBase.empty() ? "" : strBase + "::") + "C" + NUtility::First2Up(m_strName) + "::";
            vecLines.push_back(CCont.SrcGet(strClass, strName + string("C") + NUtility::First2Up(iterChild->first), NUtility::First2Up(iterChild->second->GetName()), string("m_C") + NUtility::First2Up(iterChild->second->GetName()),false));
            vecLines.push_back(CCont.SrcGet(strClass, strName + string("C") + NUtility::First2Up(iterChild->first), NUtility::First2Up(iterChild->second->GetName()), string("m_C") + NUtility::First2Up(iterChild->second->GetName()),true));
/*
            vecLines.push_back(string("inline const C") +  NUtility::First2Up(iterChild->first) + "& Get" +  NUtility::First2Up(iterChild->first) + "();");
            vecLines.push_back(string("inline const C") +  NUtility::First2Up(iterChild->first) + "& Get" +  NUtility::First2Up(iterChild->first) + "() const;");
          */
           // vecLines.push_back("");
        } else if (iterChild->second->GetType() == "m") {
            string strName = (strBase.empty() ? "" : strBase + "::") + "C" + NUtility::First2Up(m_strName) + "::";
            vecLines.push_back(CCont.SrcGet(strClass, string("vector<") + strName + string("C") + NUtility::First2Up(iterChild->first) + ">", NUtility::First2Up(iterChild->second->GetName()), string("m_vec") + NUtility::First2Up(iterChild->second->GetName()),false));
            vecLines.push_back(CCont.SrcGet(strClass, string("vector<") + strName + string("C") + NUtility::First2Up(iterChild->first) + ">", NUtility::First2Up(iterChild->second->GetName()), string("m_vec") + NUtility::First2Up(iterChild->second->GetName()),true));
/*
            vecLines.push_back(string("inline const vector<") + NUtility::First2Up(iterChild->first) + ">& Get" + NUtility::First2Up(iterChild->first) + "();");
            vecLines.push_back(string("inline const vector<") + NUtility::First2Up(iterChild->first) + ">& Get" + NUtility::First2Up(iterChild->first) + "() const;");
  */
           // vecLines.push_back("");
        }
    }

    return vecLines;
}

vector<string> CClassDetail::GenerateConstruct(const string& strBase)
{
    vector<string> vecLines;
    if (strBase.empty()) {
        vecLines.push_back("/*******************************************************************************");
        vecLines.push_back(" * construction");
        vecLines.push_back(" *******************************************************************************/");
        vecLines.push_back("CConfig::CConfig()");
        vecLines.push_back("{");
        vecLines.push_back("\tatexit(CConfig::DestroyInstance);");
        vecLines.push_back("}");
        vecLines.push_back("");
        vecLines.push_back("/*******************************************************************************");
        vecLines.push_back(" * deconstruction");
        vecLines.push_back(" *******************************************************************************/");
        vecLines.push_back("CConfig::~CConfig()");
        vecLines.push_back("{");
        vecLines.push_back("}");
        vecLines.push_back("");
        vecLines.push_back("/*******************************************************************************");
        vecLines.push_back(" * destroy instance");
        vecLines.push_back(" *******************************************************************************/");
        vecLines.push_back("void CConfig::DestroyInstance()");
        vecLines.push_back("{");
        vecLines.push_back("\tif (sm_pCInstance != NULL) {");
        vecLines.push_back("\t\tdelete sm_pCInstance;");
        vecLines.push_back("\t\tsm_pCInstance = NULL;");
        vecLines.push_back("\t}");
        vecLines.push_back("}");
        vecLines.push_back("");
    } else {
        CClassCont CContent;
        vecLines.push_back(CContent.SrcStruct(string("C") + NUtility::First2Up(m_strName), strBase));
    }
    return vecLines;
}

vector<string> CClassDetail::GenerateParse(const string& strBase)
{
    CClassCont CContent;
    vector<string> vecLines;
    vecLines.push_back(CContent.StrGetCommentStart());
    if (strBase.empty()) {
        vecLines.push_back(" * parse from XML file");
    } else {
        vecLines.push_back(" * parse from XML node");
    }
    vecLines.push_back(" * Parameters:");
    if (strBase.empty()) {
        vecLines.push_back(" * pszFile: XML file to parse");
    } else {
        vecLines.push_back(" * pCNode: XML node to parse");
    }
    vecLines.push_back(" * Return-Value: success return true, or else return false");
    vecLines.push_back(CContent.StrGetCommentEnd());
    if (strBase.empty()) {
        vecLines.push_back(string("bool ") + string("C") + NUtility::First2Up(m_strName) + "::ParseFromXML(const char* pszFile)");
    } else {
        vecLines.push_back(string("bool ") + strBase + "::" + string("C") + NUtility::First2Up(m_strName) + "::ParseFromNode(CXMLNode* pCNode)");
    }
    vecLines.push_back("{");
    if (strBase.empty()) {
        vecLines.push_back("\tCXMLTree CXML;");
        vecLines.push_back("\tif(!CXML.Create(pszFile)) return false;");
        vecLines.push_back("");
        vecLines.push_back("\tCXMLNode* pCNode = CXML.GetRoot();");
        vecLines.push_back("\tif(pCNode == NULL) return false;");
        vecLines.push_back("");
    }
    if (!m_vecAttr.empty()) {
        vecLines.push_back(string("\tmap<string, string> mapAttribute = pCNode->GetAttribute();"));
        vecLines.push_back(string("\tfor (map<string, string>::iterator iterAttribute = mapAttribute.begin(); iterAttribute != mapAttribute.end(); ++iterAttribute) {"));
        bool bAttri = false;
        for (vector<CClassMember *>::iterator iterAttr = m_vecAttr.begin(); iterAttr != m_vecAttr.end(); ++iterAttr) {
            if (bAttri) {
                vecLines.erase(vecLines.begin() + vecLines.size() - 1);
                vecLines.push_back(string("\t\t} else if (iterAttribute->first == \"") + (*iterAttr)->GetAttrName() + "\") {");
            } else {
                vecLines.push_back(string("\t\tif (iterAttribute->first == \"") + (*iterAttr)->GetAttrName() + "\") {");
            }
            bAttri = true;
            vecLines.push_back(string("\t\t\tm_str") + NUtility::First2Up((*iterAttr)->GetName()) + " = iterAttribute->second;");
            vecLines.push_back(string("\t\t}"));
        }
        vecLines.push_back(string("\t}"));

    }
    if (!m_vecMem.empty() || !m_mapChildren.empty()) {

        vecLines.push_back(string("\tstd::vector<CXMLNode *> vecNodes = pCNode->GetChildren();"));
        vecLines.push_back("\tfor (std::vector<CXMLNode *>::iterator iterNode = vecNodes.begin(); iterNode != vecNodes.end(); ++iterNode) {");
        bool bMem = false;
        for (vector<CClassMember *>::iterator iterMember = m_vecMem.begin(); iterMember != m_vecMem.end(); ++iterMember) {
            string strLine = string("\t\t") + (bMem ? "} else if ": "if ");
            if (bMem) {
                vecLines.erase(vecLines.begin() + vecLines.size() - 1);
            }
            strLine += string("((*iterNode)->GetName() == \"" + (*iterMember)->GetName() + "\") {");
            vecLines.push_back(strLine);
            if ((*iterMember)->GetType() == "c") {
                vecLines.push_back(string("\t\t\tm_str") + NUtility::First2Up((*iterMember)->GetName()) + " = (*iterNode)->GetValue();");
            } else if ((*iterMember)->GetType() == "c+") {
                vecLines.push_back(string("\t\t\tm_vec") + NUtility::First2Up((*iterMember)->GetName()) + ".push_back((*iterNode)->GetValue());");
            }
            vecLines.push_back("\t\t}");
            bMem = true;
        }

        for (map<string, CClassDetail*>::iterator iterChild = m_mapChildren.begin(); iterChild != m_mapChildren.end(); ++iterChild) {
            string strLine = string("\t\t") + (bMem ? "} else if ": "if ");
            if (bMem) {
                vecLines.erase(vecLines.begin() + vecLines.size() - 1);
            }
            strLine += string("((*iterNode)->GetName() == \"" + iterChild->first + "\") {");
            vecLines.push_back(strLine);
            if (iterChild->second->GetType() == "s") {
                vecLines.push_back(string("\t\t\tm_C") + NUtility::First2Up(iterChild->first) + ".ParseFromNode(*iterNode);");
            } else if (iterChild->second->GetType() == "m") {
                vecLines.push_back(string("\t\t\tm_vec") + NUtility::First2Up(iterChild->first) + ".push_back(C" + NUtility::First2Up(iterChild->first) +  "());");
                vecLines.push_back(string("\t\t\tm_vec") + NUtility::First2Up(iterChild->first) + "[m_vec" + NUtility::First2Up(iterChild->first) +".size() - 1].ParseFromNode(*iterNode);");
            }
            bMem = true;
            vecLines.push_back("\t\t}");
        }
        vecLines.push_back("\t}");
    } else {
        vecLines.push_back("\tm_strValue = pCNode->GetValue();");
    }

    vecLines.push_back("\treturn true;");
    vecLines.push_back("}");
    return vecLines;
}

void CClassDetail::Print()
{
    cout << "node name:"<< m_strName << "\t" << m_strType << endl;
    for (unsigned int uiCount = 0; uiCount < m_vecMem.size(); ++uiCount) {
        m_vecMem[uiCount]->Print();
    }
    for (unsigned int uiCount = 0; uiCount < m_vecAttr.size(); ++uiCount) {
        m_vecAttr[uiCount]->Print();
    }
}
