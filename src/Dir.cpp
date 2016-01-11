/*
 * Dir.cpp
 * 
 * Created on: 2012-06-13
 *     Author: fuliang
 */

#include "Dir.h"
#include "stdio.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

CDir::CDir():m_pstDir(NULL)
{
}

CDir::~CDir()
{
	if(m_pstDir != NULL) {
		closedir(m_pstDir);
		m_pstDir = NULL;
	}
}

/*
 * open directory
 * Parameters:directory path
 * Return-Value:success return true, or else return false
 */
bool CDir::Open(const char* pszDir)
{
	m_pstDir = opendir(pszDir);
	return m_pstDir != NULL;
}

/*
 * close directory
 */
void CDir::Close()
{
	if(m_pstDir != NULL) {
		closedir(m_pstDir);
		m_pstDir = NULL;
	}
}

/*
 * read directory
 * Parameters:store file name
 * Return-Value:success return true, or else return false;
 */
bool CDir::Read(std::vector<std::string>& CFileName)
{
	struct dirent stEntry;
	struct dirent* pstResult = NULL;
	int iRet = readdir_r(m_pstDir, &stEntry, &pstResult);
	while (pstResult != NULL) {
		if (iRet != 0) {
			return false;
		}
		if (strcmp(stEntry.d_name, ".") != 0 && strcmp(stEntry.d_name, "..") != 0) {
			CFileName.push_back(std::string(stEntry.d_name));
		}
		iRet = readdir_r(m_pstDir, &stEntry, &pstResult);
	}
	return true;
}

/*
 * check file exist
 * Parameters:directory path
 * Return-Value:exist return true, or else return false
 */
bool CDir::Exist(const char* pszDir)
{
	return access(pszDir, F_OK) == 0;
}

/*
 * check directory
 * Parameters:path
 * Return-Value:directory return true, or else return false
 */
bool CDir::IsDir(const char* pszPath)
{
	struct stat stStat;
    memset(&stStat, 0, sizeof(struct stat));
	stat(pszPath, &stStat);
	return S_ISDIR(stStat.st_mode);
}


/*
 * remove directory
 * Parameters:path
 */
void CDir::Remove(const char* pszDir)
{
	//check directory
	if (IsDir(pszDir)) {
		CDir CDirReader;
	    if (!CDirReader.Open(pszDir)) {
	        return;
		}

		std::vector<std::string> CFileName;
		CDirReader.Read(CFileName);
		for (unsigned int uiCount = 0; uiCount < CFileName.size(); ++uiCount){
			CFileName[uiCount] = "/" + CFileName[uiCount];
			CFileName[uiCount] = pszDir + CFileName[uiCount];
			Remove(CFileName[uiCount].c_str());
	    }
		CDirReader.Close();
	}
	remove(pszDir);
}

bool CDir::Mkdir(const char* pszDir, const int& iMode)
{
	return mkdir(pszDir, iMode);
}
