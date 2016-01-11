/*
 * Dir.h
 *
 * Created on: 2012-06-13
 *     Author: fuliang
 */

#ifndef DIR_H_
#define DIR_H_

#include <dirent.h>
#include <vector>
#include <string>

class CDir
{
	public:
		CDir();
		virtual ~CDir();

		bool Open(const char* pszDir);
		void Close();
		
		bool Read(std::vector<std::string>& CFileName);
		
		static bool Exist(const char* pszDir);
		static bool IsDir(const char* pszPath);
		static void Remove(const char* pszDir);
		static bool Mkdir(const char* pszDir, const int& iMode = 0666);
	private:
		DIR* m_pstDir;
};

#endif
