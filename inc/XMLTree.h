/*
 * XMLTree.h
 *
 * Created on: 2014-08-05
 *     Author: fuliang
 */

#ifndef XMLTREE_H_
#define XMLTREE_H_

#include <map>
#include <vector>
#include <string>

class CXMLNode
{
	public:
		CXMLNode();
		virtual ~CXMLNode();

		std::string GetName();
		std::string GetValue();
		std::string GetAttribute(const std::string& strName);
		std::map<std::string, std::string> GetAttribute(){return m_mapAttribute;};
		std::vector<CXMLNode *> GetChildren(){return m_vecChildren;};
		std::vector<CXMLNode *> GetChildren(const std::string& strName);
		bool HasAttribute() {return !m_mapAttribute.empty();};
		bool HasChildren() {return !m_vecChildren.empty();};

		void SetName(const std::string& strName);
		void SetValue(const std::string& strValue);
		void SetAttribute(const std::string& strName, const std::string& strValue);
		void AddChild(CXMLNode* pCNode);
		void Print();
	private:
		void PrintNode(CXMLNode* pstNode, const unsigned int& uiLevel);

		std::string                        m_strName;
		std::string                        m_strValue;
		std::map<std::string, std::string> m_mapAttribute;
		std::vector<CXMLNode *>            m_vecChildren;
};

class CXMLTree
{
	public:
		CXMLTree();
		virtual ~CXMLTree();

		bool Create(const char* pszPath);
		void Free();

		CXMLNode* GetNode(const std::string& strPath);
		bool GetNode(const std::string& strPath, std::vector<CXMLNode *>& vecNode);
		CXMLNode* GetRoot();
	private:
		void ParseNode(void* pvNode, const std::string& strName, CXMLNode* pCParent = NULL);
		void GetNode(CXMLNode* pCNode, const std::string& strPath, std::vector<CXMLNode *>& vecNode);
		std::string GetNodeName(const std::string& strPath);
		bool IsLastName(const std::string& strName, const std::string& strPath);
		void FreeNode(CXMLNode* pCNode);

		CXMLNode* m_pCTree;
};

#endif
