/*******************************************************************************
 * Source.h
 *
 * Created on: 2015-10-26
 *     Author: fuliang
 *******************************************************************************/

#ifndef SOURCE_H_
#define SOURCE_H_

#include "ClassDetail.h"

#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class CSource
{
	public:
		CSource();
		virtual ~CSource();

        void Core(vector<CClassDetail *>& vecDetail);
	private:
        void WriteVectorC(CClassDetail* pCDetail);
        void WriteC(CClassDetail* pCDetail);
        void WriteString(CClassDetail* pCDetail);
        void WriteVectorString(CClassDetail* pCDetail);
        void WriteCommit2Commit(vector<CClassDetail *>& vecDetail);
        map<string, vector<string> > GetNameWithAttribute(CClassDetail* pCDetail);

        ofstream Cout;
};

#endif
