/*******************************************************************************
 * Header.h
 *
 * Created on: 2015-10-25
 *     Author: fuliang
 *******************************************************************************/

#ifndef HEADER_H_
#define HEADER_H_

#include "ClassPara.h"
#include "ClassDetail.h"

#include <vector>
#include <fstream>

using namespace std;

class CHeader
{
	public:
		CHeader();
		virtual ~CHeader();

        void Core(vector<CClassDetail *>& vecDetail);
	private:
        void WriteCommit2Include(bool bVector);
        bool NeedVector(vector<CClassDetail *>& vecDetail);
        void GetPara(vector<CClassPara>& vecPara, CClassPara& CCfgPara, vector<CClassDetail *>& vecDetail);
        void ClassDeclare(CClassPara& CPara, bool bSet = true);
        void ClassDefine(CClassPara& CPara, bool bSet = true);

        ofstream Cout;
};

#endif
