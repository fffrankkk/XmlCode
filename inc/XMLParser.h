/*******************************************************************************
 * XMLParser.h
 *
 * Created on: 2015-10-25
 *     Author: fuliang
 *******************************************************************************/

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include "XMLTree.h"
#include "ClassDetail.h"

#include <map>
#include <vector>
#include <string>

using namespace std;

class CXMLParser
{
	public:
		CXMLParser();
		virtual ~CXMLParser();

        vector<CClassDetail *> Parse(const char* pszFile);
	private:
        void ParseNode(CXMLNode* pCNode, CClassDetail* pCDetail);
        void ParseAttribute(CXMLNode* pCNode, CClassDetail* pCDetail);
        void ParseChildren(CXMLNode* pCNode, CClassDetail* pCDetail);
};

#endif
