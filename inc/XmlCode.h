/*
 * XmlCode.h
 *
 * Created on: 2015-10-14
 *     Author: fuliang
 */

#ifndef XMLCODE_H
#define XMLCODE_H

#include "UtlDef.h"

#include <string>
#include <iostream>

#include <string.h>


#define INC_FILE "Config.h"
#define SRC_FILE "Config.cpp"

using namespace std;

/* option */
typedef struct tagOption
{
    int  m_iHelp;
	char m_szXMLFile[PATH_LEN];                             //configure file path
}OPTION_S;

/* member detail */
typedef struct tagMemDetail
{
    char m_szName[PATH_LEN];
    bool m_bMulti;
}MEMDETAIL_S;

/* class detail */
typedef struct tagClsDetail
{
    MEMDETAIL_S* m_pstMem;
    unsigned int m_uiMem;
    char         m_szName[PATH_LEN];
    bool         m_bMulti;

    void AddMem(const string& strName, const bool& bMulti) {
        unsigned int uiCount = 0;
        while (uiCount < m_uiMem && strcmp(m_pstMem[uiCount].m_szName, strName.c_str()) != 0) {
            ++ uiCount;
        }

        if (uiCount < m_uiMem && !m_pstMem[uiCount].m_bMulti && bMulti) {
            m_pstMem[uiCount].m_bMulti = true;
        } else if (uiCount == m_uiMem) {
            m_pstMem = (MEMDETAIL_S*) realloc(m_pstMem, sizeof(MEMDETAIL_S) * (m_uiMem + 1));
            strcpy(m_pstMem[m_uiMem].m_szName, strName.c_str());
            m_pstMem[m_uiMem].m_bMulti = bMulti;
            ++ m_uiMem;
        }
    }

    void Print() {
        cout << m_szName << "\t" << m_bMulti << endl;
        for (unsigned int uiCount = 0; uiCount < m_uiMem; ++uiCount) {
            cout << "\t" << m_pstMem[uiCount].m_szName << "\t" << m_pstMem[uiCount].m_bMulti << endl;
        }
    }
}CLSDETAIL_S;

#endif
