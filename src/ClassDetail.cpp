/*******************************************************************************
 * ClassDetail.cpp
 *
 * Created on: 2015-10-25
 *     Author: fuliang
 *******************************************************************************/

#include "BUtility.h"
#include "ClassDetail.h"

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
    cout << m_strName << "\t" << m_strType << endl;
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
    BT_AUTO(iterMem, m_vecMem.begin());
    for (; iterMem != m_vecMem.end() && (*iterMem)->GetName() != strName; ++iterMem);
    if (iterMem == m_vecMem.end()) {
        CClassMember* pCMem = new CClassMember;
        pCMem->SetName(strName);
        pCMem->SetType("a");
        pCMem->SetAttrName(strAttr);
        m_vecMem.push_back(pCMem);
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

void CClassDetail::Print()
{
    cout << "------------------------------------------------------" << endl;
    cout << m_strName << "\t" << m_strType << endl;
    for (unsigned int uiCount = 0; uiCount < m_vecMem.size(); ++uiCount) {
        m_vecMem[uiCount]->Print();
    }
}
