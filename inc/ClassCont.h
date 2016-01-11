/*******************************************************************************
 * ClassCont.h
 *
 * Created on: 2015-10-13
 *     Author: fuliang
 *******************************************************************************/

#ifndef CLASSCONT_H_
#define CLASSCONT_H_

#include "UtlDef.h"

#include <map>
#include <string>

using namespace std;

class CClassCont
{
	public:
		CClassCont();
		virtual ~CClassCont();

        string GetFileComment(const string& strName);
        string GetMacroIfndef(const string& strName);
        string GetMacroDefine(const string& strName);
        string GetMacroEndif();
        string GetInclude(const string& strName);
        string GetStruct(const string& strName);
        string GetClassVar(const vector<pair<string, string> >& vecMem);
        string GetClassEnd();

        string SrcSet(const string& strClass, const string& strType, const string& strName);
        string SrcAdd(const string& strClass, const string& strType, const string& strName);
        string SrcGet(const string& strClass, const string& strType, const string& strName, bool bConst = false);
        string SrcStruct(const string& strClass);
        string SrcCore(const string& strClass);

        string IncSet(const string& strType, const string& strName);
        string IncAdd(const string& strType, const string& strName);
        string IncGet(const string& strType, const string& strName);
        string IncGetConst(const string& strType, const string& strName);
        string IncCore();
	private:
        string Inc(const string& strRet, const string& strName, const string& strType, const string& strPara, bool bConst = false);
        string ToName(const string& strName);
        string ToVar(const string& strType, const string& strName);
        string GetPrev(const string& strType);
        void MergeSpace(string& strCont);

        string GetDate();

        map<string, string> m_mapPrev;

};

#endif
