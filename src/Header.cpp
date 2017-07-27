/*******************************************************************************
 * Header.cpp
 *
 * Created on: 2015-10-25
 *     Author: fuliang
 *******************************************************************************/

#include "Header.h"
#include "XmlCode.h"
#include "Utility.h"
#include "BUtility.h"
#include "ClassCont.h"

#include <stdio.h>

/*******************************************************************************
 * construction
 *******************************************************************************/
CHeader::CHeader()
{
    Cout.open(INC_FILE, ios::app);
}

/*******************************************************************************
 * deconstruction
 *******************************************************************************/
CHeader::~CHeader()
{
    Cout.close();
}

void CHeader::Core(vector<CClassDetail *>& vecDetail)
{
    CClassCont CCont;
    WriteCommit2Include(NeedVector(vecDetail));
    vector<CClassPara> vecPara;
    CClassPara CCfgPara;
    GetPara(vecPara, CCfgPara, vecDetail);
    for (unsigned int uiCount = 0; uiCount < vecPara.size(); ++uiCount) {
        ClassDeclare(vecPara[uiCount]);
    }
    ClassDeclare(CCfgPara, false);
    for (unsigned int uiCount = 0; uiCount < vecPara.size(); ++uiCount) {
        ClassDefine(vecPara[uiCount]);
    }
    ClassDefine(CCfgPara, false);
    Cout << "} // CFG_N\n" << endl;
    Cout <<  CCont.GetMacroEndif() << endl;
}

void CHeader::ClassDeclare(CClassPara& CPara, bool bSet)
{
    CClassCont CCont;
    Cout << CCont.GetStruct(CPara.GetClassName());
    Cout << endl;
    if (!bSet) {
        Cout << "\t\tstatic inline CConfig* GetInstance();" << endl;
        Cout << "\t\tstatic void DestroyInstance();\n" << endl;
    }
    for (vector<pair<string, string> >::iterator iterMem = CPara.Begin(); iterMem != CPara.End(); ++iterMem) {
        if (bSet) {
            Cout << CCont.IncSet(iterMem->first, iterMem->second) << endl;
            if (iterMem->first.find("vector") != string::npos) {
                Cout << CCont.IncAdd("string", iterMem->second) << endl;
            }
        }
        Cout << CCont.IncGet(iterMem->first, iterMem->second) << endl;
        Cout << CCont.IncGetConst(iterMem->first, iterMem->second) << endl;
        Cout << endl;
    }

    // CConfig
    if (!bSet) {
        Cout << "\t\tbool Parse(const char* pszFile);" << endl;
        Cout << endl;
    }
    Cout << CCont.GetClassVar(CPara.GetMember());
    if (!bSet) {
        Cout << "\n\t\tstatic CConfig* sm_pCIns;" << endl;
    }
    Cout << CCont.GetClassEnd() << endl;
}

void CHeader::ClassDefine(CClassPara& CPara, bool bSet)
{
    if (!bSet) {
        Cout << "/*******************************************************************************" << endl;
        Cout << " * get instance" << endl;
        Cout << " * Return-Value: CConfig instance" << endl;
        Cout << " *******************************************************************************/" << endl;
        Cout << "inline CConfig* CConfig::GetInstance()" << endl;
        Cout << "{" << endl;
        Cout << "\t return sm_pCIns;" << endl;
        Cout << "}" << endl;
        Cout << endl;
    }

    CClassCont CCont;
    for (vector<pair<string, string> >::iterator iterMem = CPara.Begin(); iterMem != CPara.End(); ++iterMem) {
        if (bSet) {
            Cout << CCont.SrcSet(CPara.GetClassName(), iterMem->first, iterMem->second) << endl;
            if (iterMem->first.find("vector") != string::npos) {
                Cout << CCont.SrcAdd(CPara.GetClassName(), "string", iterMem->second) << endl;
            }
        }
        Cout << CCont.SrcGet(CPara.GetClassName(), iterMem->first, iterMem->second) << endl;
        Cout << CCont.SrcGet(CPara.GetClassName(), iterMem->first, iterMem->second, true) << endl;
    }
}

void CHeader::GetPara(vector<CClassPara>& vecPara, CClassPara& CCfgPara, vector<CClassDetail *>& vecDetail)
{
    CLASS_S stCfg = {{0}, {0}};
    strcpy(stCfg.m_szName, "Config");
    for(BT_AUTO(iterDetail, vecDetail.begin()); iterDetail != vecDetail.end(); ++iterDetail) {
        CClassDetail* pCDetail = *iterDetail;

        // class of child node
        BT_AUTO(vecCls, pCDetail->GetMember());
        if (!vecCls.empty()) {
            CLASS_S stCls = {{0}, {0}};
            strcpy(stCls.m_szName, pCDetail->GetName().c_str());
            for (unsigned int uiCount = 0; uiCount < vecCls.size(); ++uiCount) {
			    if (vecCls[uiCount]->GetType() == "c+") {
                    sprintf(stCls.m_szMember + strlen(stCls.m_szMember), "vector<string> %s\n", vecCls[uiCount]->GetName().c_str());
                } else {
                    sprintf(stCls.m_szMember + strlen(stCls.m_szMember), "string %s\n", vecCls[uiCount]->GetName().c_str());
                }
            }
            if (pCDetail->GetType() == "s") {
                sprintf(stCfg.m_szMember + strlen(stCfg.m_szMember), "C%s %s\n", \
                    NUtility::First2Up(pCDetail->GetName()).c_str(), pCDetail->GetName().c_str());
            } else {
                sprintf(stCfg.m_szMember + strlen(stCfg.m_szMember), "vector<C%s> %s\n", \
                    NUtility::First2Up(pCDetail->GetName()).c_str(), pCDetail->GetName().c_str());
            }
            vecPara.push_back(CClassPara());
            vecPara[vecPara.size() - 1].Parse(&stCls);
        } else {

            // class of config
            if (pCDetail->GetType() == "m") {
                sprintf(stCfg.m_szMember + strlen(stCfg.m_szMember), "vector<string> %s\n", pCDetail->GetName().c_str());
            } else {
                sprintf(stCfg.m_szMember + strlen(stCfg.m_szMember), "string %s\n", pCDetail->GetName().c_str());
            }
        }
    }
    CCfgPara.Parse(&stCfg);
}

void CHeader::WriteCommit2Include(bool bVector)
{
    CClassCont CCont;
    Cout << CCont.GetFileComment(INC_FILE) << endl;
    Cout << CCont.GetMacroIfndef(INC_FILE) << CCont.GetMacroDefine(INC_FILE) << endl;
    if (bVector) {
        Cout << "#include <vector>" << endl;
    }
    Cout << "#include <string>\n" << endl;

    Cout << "namespace CFG_N {\n" << endl;

    if (bVector) {
        Cout << "using std::vector;" << endl;
    }
    Cout << "using std::string;\n" << endl;
}

bool CHeader::NeedVector(vector<CClassDetail *>& vecDetail)
{
    for (unsigned int uiCls = 0; uiCls < vecDetail.size(); ++uiCls) {
        if (vecDetail[uiCls]->GetType() == "m") {
            return true;
        }
        BT_AUTO(vecMem, vecDetail[uiCls]->GetMember());
        for (unsigned int uiMem = 0; uiMem < vecMem.size(); ++uiMem) {
            if (vecMem[uiMem]->GetType() == "c+") {
                return true;
            }
        }
    }
    return false;
}
