/*
 * Utility.cpp
 *
 * Created on: 2015-10-14
 *     Author: fuliang
 */

#include "Utility.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/resource.h>

namespace NUtility
{

/*******************************************************************************
 * print help information
 * Parameters:
 * pszApp: app name
 *******************************************************************************/
void PrintHelp(const char* pszApp)
{
	printf("Useage: %s [OPTION...] [...]\n", pszApp);
	printf("\t -x xml\n");
	printf("\t -h help information\n");
}

/*******************************************************************************
 * daemonize
 *******************************************************************************/
void Daemonize()
{
	if (fork() != 0) {
		exit(0);
	}
	setsid();
	int iFd = -1;
	if ((iFd = open("/dev/null", O_RDWR, 0)) != -1) {
		dup2(iFd, STDIN_FILENO);
		dup2(iFd, STDOUT_FILENO);
		dup2(iFd, STDERR_FILENO);
		if (iFd > STDERR_FILENO) {
			close(iFd);
		}
	}
}

/*******************************************************************************
 * enable core file
 *******************************************************************************/
void EnableCoreFile()
{
	struct rlimit stLimit = {0, 0};
	if (getrlimit(RLIMIT_CORE, &stLimit) == 0) {
		stLimit.rlim_cur = RLIM_INFINITY;
		setrlimit(RLIMIT_CORE, &stLimit);
	}
}

/*******************************************************************************
 * ignore signal
 * Parameters:
 * iSigNum: signal number to ignore
 *******************************************************************************/
void IgnoreSignal(const int& iSigNum)
{
	signal(iSigNum, SIG_IGN);
}

std::string First2Up(const std::string& strText)
{
    std::string strRet = strText;
    strRet[0] = toupper(strRet[0]);
    return strRet;
}

}//end namespace NUtility
