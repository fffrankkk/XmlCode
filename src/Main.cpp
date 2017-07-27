/*
 * Main.cpp
 *
 * Created on: 2015-10-14
 *     Author: fuliang
 */

#include "Main.h"
#include "Header.h"
#include "Source.h"
#include "Utility.h"
#include "BUtility.h"
#include "XMLParser.h"
#include "ClassPara.h"
#include "ClassCont.h"

#include <map>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>

#include <stdio.h>

CMain::CMain()
{

}

CMain::~CMain()
{

}

void CMain::Core(OPTION_S* pstOpt)
{
    CXMLParser CParser;
    BT_AUTO(vecDetail, CParser.Parse(pstOpt->m_szXMLFile));
    CClassDetail* pCRoot = CParser.ParseRoot(pstOpt->m_szXMLFile);
//    PrintDetail(vecDetail);
    Inc(vecDetail, pCRoot);
    Src(vecDetail, pCRoot);

/*
    for (BT_AUTO(iterDetail, vecDetail.begin()); iterDetail != vecDetail.end(); ++iterDetail) {
        //PrintDetail(*iterDetail, 1);
        vector<string> vecDeclare = (*iterDetail)->GenerateGet("CConfig");
        for (size_t zuCount = 0; zuCount < vecDeclare.size(); ++zuCount) {
            cout << vecDeclare[zuCount] << endl;
        }
    }

    //vector<string> vecDeclare = CCfgDetail.GenerateDeclare();
    vector<string> vecDeclare = CCfgDetail.GenerateGet();
    for (size_t zuCount = 0; zuCount < vecDeclare.size(); ++zuCount) {
        cout << vecDeclare[zuCount] << endl;
    }

*/

}

void CMain::Src(vector<CClassDetail *>& vecDetail, CClassDetail* pCRoot)
{
    ofstream ofsWriter;
    ofsWriter.open("Config.cpp");

    CClassCont CContent;
    string strComment = CContent.GetFileComment("Config.cpp");
    ofsWriter << strComment << endl;

    ofsWriter << "#include \"Config.h\"" << endl;
    ofsWriter << endl;
    ofsWriter << "#include <map>" << endl;
    ofsWriter << endl;
    ofsWriter << "#include <stdlib.h>" << endl;
    ofsWriter << endl;
    ofsWriter << "using std::map;" << endl;
    ofsWriter << endl;
    ofsWriter << "CConfig* CConfig::sm_pCInstance = new CConfig;" << endl;
    ofsWriter << endl;

    pCRoot->SetName("Config");

    for (BT_AUTO(iterDetail, vecDetail.begin()); iterDetail != vecDetail.end(); ++iterDetail) {
        pCRoot->AddChild((*iterDetail)->GetName(), *iterDetail);
    }

    stack<pair<CClassDetail*, string> > staClasses;
    staClasses.push(make_pair(pCRoot, ""));
    vector<pair<CClassDetail*, string> > vecClasses;
    while (!staClasses.empty()) {
        pair<CClassDetail*, string> paiClass = staClasses.top();
        staClasses.pop();

        vecClasses.push_back(paiClass);

        vector<CClassDetail *> vecChildren = paiClass.first->GetChildren();

        string strBase = string("C") + NUtility::First2Up(paiClass.first->GetName());
        if (!paiClass.second.empty()) {
            strBase = paiClass.second + "::" + strBase;
        }

        for (size_t zuCount = 0; zuCount < vecChildren.size(); ++zuCount) {
            staClasses.push(make_pair(vecChildren[zuCount], strBase));
        }
    }

    for (BT_AUTO(iterPair, vecClasses.rbegin()); iterPair != vecClasses.rend(); ++iterPair) {

        vector<string> vecStr = iterPair->first->GenerateConstruct(iterPair->second);
        for (size_t zuCount = 0; zuCount < vecStr.size(); ++zuCount) {
            ofsWriter  << vecStr[zuCount] << endl;
        }

        //if (!iterPair->second.empty()) {
        vector<string> vecParse = iterPair->first->GenerateParse(iterPair->second);
        for (size_t zuCount = 0; zuCount < vecParse.size(); ++zuCount) {
            ofsWriter << vecParse[zuCount] << endl;
        }
        ofsWriter << endl;
        //}
    }
}

void CMain::Inc(vector<CClassDetail *>& vecDetail, CClassDetail* pCRoot)
{
    ofstream ofsWriter;
    ofsWriter.open("Config.h");
    CClassCont CContent;
    string strComment = CContent.GetFileComment("Config.h");
    string strIfndef = CContent.GetMacroIfndef("Config.h");
    string strDefine = CContent.GetMacroDefine("Config.h");

    ofsWriter << strComment << endl << strIfndef << strDefine << endl;

    ofsWriter << "#include \"XMLTree.h\"" << endl;
    ofsWriter << endl;
    ofsWriter << "#include <string>" << endl;
    ofsWriter << "#include <vector>" << endl;
    ofsWriter << endl;
    ofsWriter << "using std::string;" << endl;
    ofsWriter << "using std::vector;" << endl;
    ofsWriter << endl;

    pCRoot->SetName("Config");

    for (BT_AUTO(iterDetail, vecDetail.begin()); iterDetail != vecDetail.end(); ++iterDetail) {
        pCRoot->AddChild((*iterDetail)->GetName(), *iterDetail);
    }


    stack<pair<CClassDetail*, string> > staClasses;
    staClasses.push(make_pair(pCRoot, ""));
    vector<pair<CClassDetail*, string> > vecClasses;
    while (!staClasses.empty()) {
        pair<CClassDetail*, string> paiClass = staClasses.top();
        staClasses.pop();

        vecClasses.push_back(paiClass);

        vector<CClassDetail *> vecChildren = paiClass.first->GetChildren();

        string strBase = string("C") + NUtility::First2Up(paiClass.first->GetName());
        if (!paiClass.second.empty()) {
            strBase = paiClass.second + "::" + strBase;
        }

        for (size_t zuCount = 0; zuCount < vecChildren.size(); ++zuCount) {
            staClasses.push(make_pair(vecChildren[zuCount], strBase));
        }
    }

    vector<string> vecDeclare = pCRoot->GenerateDeclare();
    for (size_t zuCount = 0; zuCount < vecDeclare.size(); ++zuCount) {
        ofsWriter << vecDeclare[zuCount] << endl;
    }
    ofsWriter << endl;

    for (BT_AUTO(iterPair, vecClasses.rbegin()); iterPair != vecClasses.rend(); ++iterPair) {

        vector<string> vecGet = iterPair->first->GenerateGet(iterPair->second);
        for (size_t zuCount = 0; zuCount < vecGet.size(); ++zuCount) {
            ofsWriter << vecGet[zuCount] << endl;
        }
    }

    string strEndif = CContent.GetMacroEndif();
    ofsWriter << strEndif;
}

void CMain::PrintDetail(vector<CClassDetail *>& vecDetail)
{
    for (BT_AUTO(iterDetail, vecDetail.begin()); iterDetail != vecDetail.end(); ++iterDetail) {
        (*iterDetail)->Print();
    }
}

void CMain::PrintDetail(CClassDetail* pCDetail, const int& iLevel)
{
    for (int iCount = 0; iCount < iLevel; ++iCount) {
        printf("-");
    }
    printf("\n");
    pCDetail->Print();
    vector<CClassDetail *> vecChildren = pCDetail->GetChildren();
    for (size_t zuCount = 0; zuCount < vecChildren.size(); ++zuCount) {
        PrintDetail(vecChildren[zuCount], iLevel + 1);
    }
}
