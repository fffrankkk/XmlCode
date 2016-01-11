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
    return vecDetail;
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
    }
}

void CXMLParser::ParseChildren(CXMLNode* pCNode, CClassDetail* pCDetail)
{
    BT_AUTO(vecChildren, pCNode->GetChildren());
    for (BT_AUTO(iterChild, vecChildren.begin()); iterChild != vecChildren.end(); ++iterChild) {
        ParseAttribute(*iterChild, pCDetail);
        pCDetail->AddMember((*iterChild)->GetName(), pCNode->GetChildren((*iterChild)->GetName()).size() == 1 ? "c" : "c+");
    }
}
