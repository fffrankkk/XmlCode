/*******************************************************************************
 * ClassPara.cpp
 *
 * Created on: 2015-10-13
 *     Author: fuliang
 *******************************************************************************/

#include "Dir.h"
#include "BString.h"
#include "ClassPara.h"

#include <iostream>

using namespace std;

struct MEMSEP_S { bool operator()(char cChar) const {return cChar == '\n';}} stMem;
struct PRINT_S {void operator()(const string& strCont) const {cout << strCont << "\t";}\
    void operator()(const pair<string, string>& paiData){cout << paiData.first << "\t" << paiData.second << endl;}} stPrint;
struct TYPESEP_S {
    TYPESEP_S(vector<pair<string, string> >& vecMem):m_vecMem(vecMem){};
    vector<pair<string, string> >& m_vecMem;
    void operator()(const string strText) const {
        size_t zuLastSpace = strText.find_last_of(' ');
        if (zuLastSpace != string::npos) {
            m_vecMem.push_back(make_pair(strText.substr(0, zuLastSpace), strText.substr(zuLastSpace + 1)));
        }
    }
};
CClassPara::CClassPara()
{

}

CClassPara::~CClassPara()
{

}


/*******************************************************************************
 * parse class parameters
 * Parameters:
 * pstOpt: option
 *******************************************************************************/
void CClassPara::Parse(const CLASS_S* pstOpt)
{
    m_strParaName = m_strName = pstOpt->m_szName;
    m_strName[0] = toupper(m_strName[0]);
    vector<string> vecMem;
    string strText = pstOpt->m_szMember;
    BT_Split(vecMem, strText, stMem);
    for_each(vecMem.begin(), vecMem.end(), TYPESEP_S(m_vecMember));
//    for_each(m_vecMember.begin(), m_vecMember.end(), stPrint);
}

string CClassPara::GetIncDir()
{
    if (CDir::Exist("./inc/") && CDir::Exist("./src/")) {
        return string("./inc/");
    } else if (CDir::Exist("../inc/") && CDir::Exist("../src/")) {
        return string("../inc/");
    }
    return string("./");
}

string CClassPara::GetSrcDir()
{
    if (CDir::Exist("./src/") && CDir::Exist("./src/")) {
        return string("./src/");
    } else if (CDir::Exist("../inc/") && CDir::Exist("../src/")) {
        return string("../src/");
    }
    return string("./");
}

vector<pair<string, string> >::iterator CClassPara::Begin()
{
    return m_vecMember.begin();
}

vector<pair<string, string> >::iterator CClassPara::End()
{
    return m_vecMember.end();
}

const vector<pair<string, string> >& CClassPara::GetMember()
{
    return m_vecMember;
}
