/*
 * Utility.h
 *
 * Created on: 2015-10-14
 *     Author: fuliang
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <string>

namespace NUtility
{
	void PrintHelp(const char* pszApp);
	void Daemonize();
	void EnableCoreFile();
	void IgnoreSignal(const int& iSigNum);

	std::string First2Up(const std::string& strText);
}

#endif
