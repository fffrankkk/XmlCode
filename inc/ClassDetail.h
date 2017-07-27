/*******************************************************************************
 * ClassDetail.h
 *
 * Created on: 2015-10-25
 *     Author: fuliang
 *******************************************************************************/

#ifndef CLASSDETAIL_H_
#define CLASSDETAIL_H_

#include <map>
#include <vector>
#include <string>

using namespace std;

class CClassMember
{
    public:
        CClassMember();
        virtual ~CClassMember();

        void SetName(const string& strName);
        void SetType(const string& strType);  // a, c, c+
        void SetAttrName(const string& strAttrName);

        string GetName();
        string GetType();
        string GetAttrName();
        void Print();
    private:
        string       m_strName;
        string       m_strType;
        string       m_strAttrName;
};

class CClassDetail
{
	public:
		CClassDetail();
		virtual ~CClassDetail();

        void SetName(const string& strName);
        string GetName();
        void AddAttribute(const string& strName, const string& strAttr);
        void AddMember(const string& strName, const string& strType);
        void SetType(const string& strType);     // s, m
        string GetType();
        vector<CClassMember *>& GetMember();
        CClassDetail* GetChild(const string& strName);
        vector<CClassDetail *> GetChildren();
        void AddChild(const string& strName, CClassDetail* pCClass) {m_mapChildren[strName] = pCClass;};

        void Print();
        vector<string> GenerateDeclare(const int& iLevel = 0);
        vector<string> GenerateGet(const string& strBase = "");
        vector<string> GenerateConstruct(const string& strBase = "");
        vector<string> GenerateParse(const string& strBase = "");
	private:
        string                     m_strName;
        string                     m_strType;
        vector<CClassMember *>     m_vecMem;
        vector<CClassMember *>     m_vecAttr;
        map<string, CClassDetail*> m_mapChildren;
};

#endif
