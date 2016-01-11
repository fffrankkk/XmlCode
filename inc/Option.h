/*
 * Option.h
 *
 * Created on: 2013-01-09
 *     Author: fuliang
 */

#ifndef OPTION_H_
#define OPTION_H_

#include <map>
#include <vector>
#include <string>
#include <getopt.h>

#define OPT_MAXNUM 32


class COption
{
	public:
		typedef std::vector<std::pair<int, std::string> >                 RST_C;
		typedef std::vector<std::pair<int, std::string> >::iterator       RST_ITERATOR_C;
		typedef std::vector<std::pair<int, std::string> >::const_iterator RST_CONST_ITERATOR_C;
	public:
		COption();
		virtual ~COption();

		void SetLongOpt(const char* pszName, const int& iArg, int* piFlag, const int& iVal);
		void Parse(const int& iArgc, char* pszArgv[], RST_C& CRst);
	private:
		struct option m_stLongOpt[OPT_MAXNUM];
		unsigned int  m_uiOptNum;
};

#endif
