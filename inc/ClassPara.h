/*******************************************************************************
 * ClassPara.h
 *
 * Created on: 2015-10-13
 *     Author: fuliang
 *******************************************************************************/

#ifndef CLASSPARA_H_
#define CLASSPARA_H_

#include "UtlDef.h"

#include <vector>
#include <string>

using namespace std;

struct CLASS_S
{
    char m_szName[PATH_LEN];
    char m_szMember[PATH_LEN];
};

class CClassPara
{
	public:
		CClassPara();
		virtual ~CClassPara();

		void Parse(const CLASS_S* pstOpt);
		vector<pair<string, string> >::iterator Begin();
		vector<pair<string, string> >::iterator End();

		const vector<pair<string, string> >& GetMember();

		string GetClassName() {return string("C") + m_strName;};
		string GetIncName() {return m_strName + ".h";};
		string GetSrcName() {return m_strName + ".cpp";};
		string GetIncDir();
		string GetSrcDir();
		string GetName() const {return m_strParaName;};
	private:

        string                        m_strName;
        string                        m_strParaName;
        vector<pair<string, string> > m_vecMember;
};

#endif
