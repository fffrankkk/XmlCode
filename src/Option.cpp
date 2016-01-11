/*
 * Option.cpp
 *
 * Created on: 2013-01-09
 *     Author: fuliang
 */

#include "Option.h"
#include <string.h>

COption::COption():m_uiOptNum(0)
{
	memset(&m_stLongOpt, 0, sizeof(struct option) * OPT_MAXNUM);
}

COption::~COption()
{
	m_uiOptNum = 0;
}

/*******************************************************************************
 * set long options
 * Parameters:
 * pszName: the name of the long option
 * iArg: no_argument (or 0), required_argument (or 1), optional_argument  (or 2)
 * piFlag: specifies how results are returned for a long option
 * val: the value to return
 *******************************************************************************/
void COption::SetLongOpt(const char* pszName, const int& iArg, int* piFlag, const int& iVal)
{
	if (m_uiOptNum < OPT_MAXNUM) {
		m_stLongOpt[m_uiOptNum].name = pszName;
		m_stLongOpt[m_uiOptNum].has_arg = iArg;
		m_stLongOpt[m_uiOptNum].flag = piFlag;
		m_stLongOpt[m_uiOptNum].val = iVal;
		++m_uiOptNum;
	}
}

/*******************************************************************************
 * parse option
 * Parameters:
 * iArgc: argc
 * ppArgv: argv
 * CRst: parse result
 *******************************************************************************/
void COption::Parse(const int& iArgc, char* pszArgv[], RST_C& CRst)
{
	char szShortOpt[OPT_MAXNUM << 1] = {0};
	for (unsigned int uiCount = 0; uiCount < m_uiOptNum; ++uiCount) {
		szShortOpt[strlen(szShortOpt)] = m_stLongOpt[uiCount].val;
		if(m_stLongOpt[uiCount].has_arg != no_argument) {
			szShortOpt[strlen(szShortOpt)] = ':';
		}	
	}
	int iChar = -1;
	while ((iChar = getopt_long(iArgc, pszArgv, szShortOpt, m_stLongOpt, NULL)) != -1) {
		if (iChar == '?') {
			continue;
		}
		CRst.push_back(std::make_pair(iChar, std::string(optarg != NULL ? optarg : "")));
	}
}
