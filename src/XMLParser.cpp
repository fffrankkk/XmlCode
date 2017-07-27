/*******************************************************************************
 * XMLParser.cpp
 *
 * Created on: 2015-10-25
 *     Author: fuliang
 *******************************************************************************/

#include "UtlDef.h"
#include "Utility.h"
#include "BUtility.h"
#include "XMLParser.h"

#include <stdio.h>
#include <iostream>

using namespace std;

/*******************************************************************************
 * construction
 *******************************************************************************/
CXMLParser::CXMLParser()
{

}

/*******************************************************************************
 * deconstruction
 *******************************************************************************/
CXMLParser::~CXMLParser()
{

}

vector<CClassDetail *> CXMLParser::Parse(const char* pszFile)
{
    vector<CClassDetail *> vecDetail;
    CXMLTree CParser;
    if (!CParser.Create(pszFile)) {
        ERROR_OUT("create [%s].", pszFile);
        return vecDetail;
    }

    CXMLNode* pCRoot = CParser.GetRoot();
    if (PTR_NULL(pCRoot)) {
        return vecDetail;
    }
    vector<CXMLNode *> vecChildren = pCRoot->GetChildren();
    map<string, CClassDetail *> mapDetail;
    for (BT_AUTO(iterNode, vecChildren.begin()); iterNode != vecChildren.end(); ++iterNode) {
        CXMLNode* pCNode = *iterNode;
        if (pCNode->HasAttribute() || pCNode->HasChildren()) {
            BT_AUTO(iterDetail, mapDetail.find(pCNode->GetName()));
            CClassDetail* pCDetail = NULL;
            if (iterDetail == mapDetail.end()) {
                pCDetail = new CClassDetail;
                pCDetail->SetType("s");
                mapDetail.insert(make_pair(pCNode->GetName(), pCDetail));
                vecDetail.push_back(pCDetail);
            } else {
                pCDetail = iterDetail->second;
                pCDetail->SetType("m");
            }
            ParseNode(pCNode, pCDetail);
        }
    }
    return vecDetail;
}

CClassDetail* CXMLParser::ParseRoot(const char* pszFile)
{
    CClassDetail* pCClass = new CClassDetail;
    CXMLTree CParser;
    if (!CParser.Create(pszFile)) {
        ERROR_OUT("create [%s].", pszFile);
        return pCClass;
    }

    CXMLNode* pCRoot = CParser.GetRoot();
    if (PTR_NULL(pCRoot)) {
        return pCClass;
    }
    pCClass->SetType("s");

    BT_AUTO(mapAttribute, pCRoot->GetAttribute());
    const string& strName = pCRoot->GetName();
    for (BT_AUTO(iterAttr, mapAttribute.begin()); iterAttr != mapAttribute.end(); ++iterAttr) {
        const string& strAttr = iterAttr->first;
        pCClass->AddAttribute(strName + NUtility::First2Up(strAttr), strAttr);
    }

    vector<CXMLNode *> vecChildren = pCRoot->GetChildren();
    map<string, unsigned int> mapMember;
    for (vector<CXMLNode *>::iterator iterNode = vecChildren.begin(); iterNode != vecChildren.end(); ++iterNode) {
        if (!(*iterNode)->HasChildren() && !(*iterNode)->HasAttribute()) {
            map<string, unsigned int>::iterator iterFind = mapMember.find((*iterNode)->GetName());
            if (iterFind != mapMember.end()) {
                ++ (iterFind->second);
            } else {
                mapMember[(*iterNode)->GetName()] = 1;
            }
        }
    }
    for (map<string, unsigned int>::iterator iterMem = mapMember.begin(); iterMem != mapMember.end(); ++iterMem) {
        if (iterMem->second == 1) {
            pCClass->AddMember(iterMem->first, "c");
        } else {
            pCClass->AddMember(iterMem->first, "c+");
        }
    }
    return pCClass;
}

void CXMLParser::ParseNode(CXMLNode* pCNode, CClassDetail* pCDetail)
{
    pCDetail->SetName(pCNode->GetName());
    ParseAttribute(pCNode, pCDetail);
    ParseChildren(pCNode, pCDetail);
}

void CXMLParser::ParseAttribute(CXMLNode* pCNode, CClassDetail* pCDetail)
{
    BT_AUTO(mapAttribute, pCNode->GetAttribute());
    const string& strName = pCNode->GetName();
    for (BT_AUTO(iterAttr, mapAttribute.begin()); iterAttr != mapAttribute.end(); ++iterAttr) {
        const string& strAttr = iterAttr->first;
        pCDetail->AddAttribute(strName + NUtility::First2Up(strAttr), strAttr);
        //pCDetail->AddAttribute(strName, strAttr);

    }
}

void CXMLParser::ParseChildren(CXMLNode* pCNode, CClassDetail* pCDetail)
{
    BT_AUTO(vecChildren, pCNode->GetChildren());
    for (BT_AUTO(iterChild, vecChildren.begin()); iterChild != vecChildren.end(); ++iterChild) {
        if ((*iterChild)->HasAttribute() || (*iterChild)->HasChildren()) {
            CClassDetail* pCChild = NULL;
            if (PTR_NULL(pCChild = pCDetail->GetChild((*iterChild)->GetName()))) {
                pCChild = new CClassDetail;
                pCChild->SetType("s");
                pCDetail->AddChild((*iterChild)->GetName(), pCChild);
            } else {
                pCChild->SetType("m");
            }
            ParseNode(*iterChild, pCChild);
        } else {
            //ParseAttribute(*iterChild, pCDetail);
            pCDetail->AddMember((*iterChild)->GetName(), pCNode->GetChildren((*iterChild)->GetName()).size() == 1 ? "c" : "c+");
        }
    }
}
