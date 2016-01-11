/*******************************************************************************
 * ClassDetail.h
 *
 * Created on: 2015-10-25
 *     Author: fuliang
 *******************************************************************************/

#ifndef CLASSDETAIL_H_
#define CLASSDETAIL_H_

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

        void Print();
	private:
        string                  m_strName;
        string                  m_strType;
        vector<CClassMember *>  m_vecMem;
};

#endif
