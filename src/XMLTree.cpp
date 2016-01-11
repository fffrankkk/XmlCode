/*
 * XMLTree.cpp
 *
 * Created on: 2014-08-05
 *     Author: fuliang
 */

#include "XMLTree.h"

#include <libxml/tree.h>
#include <libxml/parser.h>

#include <stdio.h>

CXMLNode::CXMLNode()
{
}

CXMLNode::~CXMLNode()
{
}

/*******************************************************************************
 * set node name
 * Parameters:
 * strName: node name
 *******************************************************************************/
void CXMLNode::SetName(const std::string& strName)
{
	m_strName = strName;
}

/*******************************************************************************
 * set node value
 * Parameters:
 * strName: node value
 *******************************************************************************/
void CXMLNode::SetValue(const std::string& strValue)
{
	m_strValue = strValue;
}

/*******************************************************************************
 * set attribute
 * Parameters:
 * strName: attribute name
 * strValue: attribute value
 *******************************************************************************/
void CXMLNode::SetAttribute(const std::string& strName, const std::string& strValue)
{
	m_mapAttribute[strName] = strValue;
}

/*******************************************************************************
 * add child
 * Parameters:
 * pCNode: child node
 *******************************************************************************/
void CXMLNode::AddChild(CXMLNode* pCNode)
{
	m_vecChildren.push_back(pCNode);
}

/*******************************************************************************
 * get name
 * Return-Value: node name
 *******************************************************************************/
std::string CXMLNode::GetName()
{
	return m_strName;
}

/*******************************************************************************
 * get value
 * Return-Value: node value
 *******************************************************************************/
std::string CXMLNode::GetValue()
{
	return m_strValue;
}

/*******************************************************************************
 * get attribute by name
 * Parameters:
 * strName: attribute name
 * Return-Value: attribute value
 *******************************************************************************/
std::string CXMLNode::GetAttribute(const std::string& strName)
{
	std::map<std::string, std::string>::iterator iterAttr = m_mapAttribute.find(strName);
	return iterAttr != m_mapAttribute.end() ? iterAttr->second : std::string();
}

/*******************************************************************************
 * get children
 * Parameters:
 * strName: node name
 *******************************************************************************/
std::vector<CXMLNode *> CXMLNode::GetChildren(const std::string& strName)
{
	std::vector<CXMLNode *> vecNode;
	for (unsigned int uiCount = 0; uiCount < m_vecChildren.size(); ++uiCount) {
		if (strName == m_vecChildren[uiCount]->GetName()) {
			vecNode.push_back(m_vecChildren[uiCount]);
		}
	}
	return vecNode;
}

void CXMLNode::Print()
{
	PrintNode(this, 1);
}

void CXMLNode::PrintNode(CXMLNode* pstNode, const unsigned int& uiLevel)
{
	for (unsigned int uiCount = 0; uiCount < uiLevel << 1; ++uiCount) {
		printf("-");
	}
	printf("%s", pstNode->GetName().c_str());
	std::vector<CXMLNode *> vecChildren = pstNode->GetChildren();
	if (vecChildren.empty()) {
		printf(" %s\n", pstNode->GetValue().c_str());
	} else {
		printf("\n");
		for (unsigned int uiCount = 0; uiCount < vecChildren.size(); ++uiCount) {
			PrintNode(vecChildren[uiCount], uiLevel + 1);
		}
	}
}


CXMLTree::CXMLTree():m_pCTree(NULL)
{
}

CXMLTree::~CXMLTree()
{
	Free();
}

/*******************************************************************************
 * create tree from file
 * Parameters:
 * pszPath: path of xml file
 * Return-Value: success return true, or else return false
 *******************************************************************************/
bool CXMLTree::Create(const char* pszPath)
{
	xmlDocPtr pstDoc = xmlParseFile(pszPath);
	if (pstDoc != NULL) {
		xmlNodePtr pstRoot = xmlDocGetRootElement(pstDoc);
		if (pstRoot != NULL) {
			ParseNode(pstRoot, (char *)(pstRoot->name));
		}
		xmlFreeDoc(pstDoc);
	} else {
		return false;
	}
	return true;
}

/*******************************************************************************
 * parse node
 * Parameters:
 * pvNode: node
 *******************************************************************************/
void CXMLTree::ParseNode(void* pvNode, const std::string& strName, CXMLNode* pCParent)
{
	xmlNodePtr pstNode = (xmlNodePtr)(pvNode);
	CXMLNode* pCNode = new CXMLNode;
	pCNode->SetName(strName);
	if (pCParent == NULL) {
		m_pCTree = new CXMLNode;
		m_pCTree->AddChild(pCNode);
	} else {
		pCParent->AddChild(pCNode);
	}

	//get name-value
	if ((pstNode->children != NULL && pstNode->children == pstNode->last) || pstNode->children == NULL) {
		char* pszCont = (char *) xmlNodeGetContent(pstNode);
		if (pszCont != NULL) {
			pCNode->SetValue(pszCont);
			xmlFree(pszCont);
		}
	}

	//get attribute
	xmlAttrPtr pstAttr = pstNode->properties;
	while (pstAttr != NULL) {
		char* pszCont = (char *)xmlGetProp(pstNode, pstAttr->name);
		if (pszCont != NULL) {
			pCNode->SetAttribute((char *)(pstAttr->name), pszCont);
			xmlFree(pszCont);
		}
		pstAttr = pstAttr->next;
	}

	//children
	xmlNodePtr pstChild = pstNode->children;
	while (pstChild != NULL) {
		if (pstChild->type == XML_ELEMENT_NODE) {
			ParseNode(pstChild, (char *)pstChild->name, pCNode);
		}
		pstChild = pstChild->next;
	}
}

/*******************************************************************************
 * get node by xpath
 * Parameters:
 * strPath: node path
 * Return-Value: if only one node return node, or else return NULL
 *******************************************************************************/
CXMLNode* CXMLTree::GetNode(const std::string& strPath)
{
	std::vector<CXMLNode *> vecNode;
	GetNode(m_pCTree, strPath, vecNode);
	return vecNode.size() == 1 ? vecNode[0] : NULL;
}

/*******************************************************************************
 * get node by name
 * Parameters:
 * strName: node path
 * vecNode: store all node
 *******************************************************************************/
bool CXMLTree::GetNode(const std::string& strPath, std::vector<CXMLNode *>& vecNode)
{
	GetNode(m_pCTree, strPath, vecNode);
	return !vecNode.empty();
}

/*******************************************************************************
 * get root node
 * Parameters:
 * Return-Value: return root node
 *******************************************************************************/
CXMLNode* CXMLTree::GetRoot()
{
	std::vector<CXMLNode *> vecNode = m_pCTree->GetChildren();
	return vecNode.size() == 1 ? vecNode[0] : NULL;
}

/*******************************************************************************
 * get node by name
 * Parameters:
 * pCNode: current node
 * strName: node path
 * vecNode: store all node
 *******************************************************************************/
void CXMLTree::GetNode(CXMLNode* pCNode, const std::string& strPath, std::vector<CXMLNode *>& vecNode)
{
	std::string strName = GetNodeName(strPath);
	if (pCNode != NULL && !strName.empty()) {
		std::vector<CXMLNode *> vecChild =  pCNode->GetChildren(strName);
		if (IsLastName(strName, strPath)) {
			for (unsigned int uiCount = 0; uiCount < vecChild.size(); ++uiCount) {
				vecNode.push_back(vecChild[uiCount]);
			}
		} else {
			for (unsigned int uiCount = 0; uiCount < vecChild.size(); ++uiCount) {
				GetNode(vecChild[uiCount], strPath.c_str() + strName.length(), vecNode);
			}
		}
	}
}

/*******************************************************************************
 * get node name from path
 * Parameters:
 * strPath: path
 * Return-Value: node name
 *******************************************************************************/
std::string CXMLTree::GetNodeName(const std::string& strPath)
{
	size_t sizeStart = strPath.find_first_not_of('/');
	if (sizeStart == std::string::npos) {
		return std::string();
	}

	size_t sizeEnd = strPath.find_first_of('/', sizeStart);
	if (sizeEnd == std::string::npos) {
		sizeEnd = strPath.length();
	}
	return strPath.substr(sizeStart, sizeEnd - sizeStart);
}

/*******************************************************************************
 * check last name
 * Parameters:
 * strName: current name
 * strPath: path
 * Return-Value: last name return true, or else return false
 *******************************************************************************/
bool CXMLTree::IsLastName(const std::string& strName, const std::string& strPath)
{
	size_t sizePos = strPath.find(strName);
	if (sizePos == std::string::npos) {
		return false;
	} else {
		sizePos += strName.length();
		while (sizePos < strPath.length()) {
			if (strPath[sizePos] != '/') {
				break;
			}
			++ sizePos;
		}
	}
	return sizePos == strPath.length();
}

/*******************************************************************************
 * free tree
 *******************************************************************************/
void CXMLTree::Free()
{
	if (m_pCTree != NULL) {
		FreeNode(m_pCTree);
	}
	m_pCTree = NULL;
}

/*******************************************************************************
 * free node
 * Parameters:
 * pCNode: node
 *******************************************************************************/
void CXMLTree::FreeNode(CXMLNode* pCNode)
{
	std::vector<CXMLNode *> vecNode = pCNode->GetChildren();
	for (unsigned int uiCount = 0; uiCount < vecNode.size(); ++uiCount) {
		FreeNode(vecNode[uiCount]);
	}
	delete pCNode;
}
