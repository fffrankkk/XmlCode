/*******************************************************************************
 * UtlDef.h
 *
 * Created on: 2015-07-27
 *     Author: fuliang
 *******************************************************************************/

#ifndef UTLDEF_H_
#define UTLDEF_H_

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

/* macro define */

/* length of ipv4 */
#define HOST_LEN 16

/* length of path*/
#define PATH_LEN 256

/* check string empty */
#define STR_EMPTY(str) ((*(str)) == 0)

/* check pointer NULL */
#define PTR_NULL(ptr) ((ptr) == NULL)

/* check number 0 */
#define ZERO(num) (num == 0)

/* check file exist */
#define FILE_EXIST(file) (access(file, F_OK) == 0)

/* output date:"2015-08-27 09:57:30 132" to FILE* fp */
#define DATETIME_OUT(fp)                                              \
        do {                                                          \
            struct timeval stTime = {0, 0};                           \
            gettimeofday(&stTime, NULL);                              \
            time_t timeNow = stTime.tv_sec;                           \
            struct tm* pstTm = localtime(&timeNow);                   \
            fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d %ld ",         \
                pstTm->tm_year +1900, pstTm->tm_mon + 1,              \
                pstTm->tm_mday, pstTm->tm_hour, pstTm->tm_min,        \
                pstTm->tm_sec, stTime.tv_usec);                       \
        } while (0)

/* output as error */
#define ERROR_OUT(format, args...)                                    \
        do {                                                          \
                DATETIME_OUT(stderr);                                 \
                fprintf(stderr, "[ERROR] %s:%d ", __FILE__, __LINE__);\
                fprintf(stderr, format, ##args);                      \
                fprintf(stderr, "\n");                                \
        } while (0)

/* output as debug */
#define DEBUG_OUT(format, args...)                                    \
        do {                                                          \
                DATETIME_OUT(stdout);                                 \
                fprintf(stdout, "[DEBUG] %s:%d ", __FILE__, __LINE__);\
                fprintf(stdout, format, ##args);                      \
                fprintf(stdout, "\n");                                \
        } while (0)

/* delete a pointer and set NULL */
#define DELETE(pC)                                                    \
        do {                                                          \
                if (!PTR_NULL(pC)) {                                  \
                    delete (pC);                                      \
                    (pC) = NULL;                                      \
                }                                                     \
        } while (0)

/* delete a array and set NULL */
#define DELETE_ALL(pCArr)                                             \
        do {                                                          \
                if (!PTR_NULL(pCArr)) {                               \
                    delete [] (pCArr);                                \
                    (pCArr) = NULL;                                   \
                }                                                     \
        } while (0)

/* free a pointer and set NULL */
#define FREE(pst)                                                     \
        do {                                                          \
                if (!PTR_NULL(pst)) {                                 \
                    free((pst));                                      \
                    (pst) = NULL;                                     \
                }                                                     \
        } while (0)
/* free a struct pointer and a member of it */
#define FREE_WITH_MEM_1(pst, mem)                                     \
        do {                                                          \
            if (!PTR_NULL(pst)) {                                     \
                FREE((pst)->(mem));                                   \
            }                                                         \
            FREE(pst);                                                \
        } while (0)

/* structure define */

/* net address  */
struct NETADDR_S
{
	unsigned short m_usPort;                                // port of address
	char           m_szHost[HOST_LEN];                      // ip of address (ipv4)
};

/* base data */
struct BASEDATA_S
{
    unsigned char* m_puszData;                              // data space address
    unsigned long  m_ulLength;                              // length of space
};

/* buffer */
struct BUFFER_S
{
	unsigned char* m_puszData;                              // buffer space address
	unsigned long  m_ulSize;                                // size of buffer
	unsigned long  m_ulUse;                                 // use of buffer
};

#endif
