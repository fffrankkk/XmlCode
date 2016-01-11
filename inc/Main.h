/*
 * Main.h
 *
 * Created on: 2015-10-14
 *     Author: fuliang
 */

#ifndef MAIN_H_
#define MAIN_H_


#include "XmlCode.h"
#include "XMLTree.h"

#include "ClassPara.h"
#include "ClassDetail.h"

#include <vector>
#include <string>
#include <fstream>

using namespace std;

class CMain
{
	public:
		CMain();
		virtual ~CMain();

		void Core(OPTION_S* pstOpt);
	private:
        void PrintDetail(vector<CClassDetail *>& vecDetail);
};

#endif
