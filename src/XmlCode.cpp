/*
 * XmlCodecpp
 *
 * Created on: 2015-10-14
 *     Author: fuliang
 */

#include "Main.h"
#include "Option.h"
#include "XmlCode.h"
#include "Utility.h"

#include <stdio.h>
#include <signal.h>
#include <string.h>

#define DEF_CONFIG "../conf/XmlCode.xml"

int main(int argc, char* argv[])
{
	OPTION_S stOpt = {0, {0}};

	//parse command
	COption COpt;
	COpt.SetLongOpt("xml", 1, NULL, 'x');
	COpt.SetLongOpt("help", 0, NULL, 'h');
	COption::RST_C CRst;
	COpt.Parse(argc, argv, CRst);

	if (!CRst.empty()) {
		for (COption::RST_ITERATOR_C iterOpt = CRst.begin(); iterOpt != CRst.end(); ++iterOpt) {
			switch (iterOpt->first) {
				case 'x':
					strcpy(stOpt.m_szXMLFile, iterOpt->second.c_str());
					break;
                case 'h':
                    stOpt.m_iHelp = 1;
				default:
					break;
			}
		}
	}

	if (stOpt.m_iHelp > 0 || STR_EMPTY(stOpt.m_szXMLFile)) {
		NUtility::PrintHelp(argv[0]);
        return 0;
	}

	//system run
	CMain CSys;
	CSys.Core(&stOpt);
	return 0;
}
