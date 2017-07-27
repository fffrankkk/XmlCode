/*******************************************************************************
 * ClassCont.cpp
 *
 * Created on: 2015-10-13
 *     Author: fuliang
 *******************************************************************************/

#include "BString.h"
#include "ClassCont.h"

#include <sstream>

#include <stdio.h>

CClassCont::CClassCont()
{
    m_mapPrev["char"] = "c";
    m_mapPrev["short"] = "s";
    m_mapPrev["int"] = "i";
    m_mapPrev["long"] = "l";
    m_mapPrev["*"] = "p";

    m_mapPrev["unsigned"] = "u";
    m_mapPrev["size_t"] = "zu";
    m_mapPrev["ssize_t"] = "zd";

    m_mapPrev["vector"] = "vec";
    m_mapPrev["string"] = "str";
    m_mapPrev["map"] = "map";
    m_mapPrev["vector<string>"] = "vec";
}

CClassCont::~CClassCont()
{

}

string CClassCont::GetFileComment(const string& strName)
{
    return \
        string("/*******************************************************************************\n") + \
        string(" * ") + strName + string("\n") + \
        string(" *\n") + \
        string(" * Created on: ") + GetDate() + string("\n") + \
        string(" *     Author: fuliang\n") + \
        string(" *******************************************************************************/\n")\
        ;
}

string CClassCont::GetInclude(const string& strName)
{
    return string("#include \"") + strName + string("\"\n");
}

string CClassCont::GetStruct(const string& strName)
{
    return \
        string("class ") + strName + string("\n") + \
        string("{\n") + \
        string("\tpublic:\n") + \
        string("\t\t") + strName + string("();\n") + \
        string("\t\tvirtual ~") + strName + string("();\n")
        ;
}

string CClassCont::IncSet(const string& strType, const string& strName)
{
    string strCont = Inc("void", \
                         string("Set") + ToName(strName), \
                         string("const ") + strType + "&", \
                         ToVar(strType, strName)\
                        );
    MergeSpace(strCont);
    return string("\t\t") + strCont;
}

string CClassCont::IncAdd(const string& strType, const string& strName)
{
    string strCont = Inc("void", \
                         string("Add") + ToName(strName), \
                         string("const ") + strType + "&", \
                         ToVar(strType, strName)\
                        );
    MergeSpace(strCont);
    return string("\t\t") + strCont;
}

string CClassCont::IncGet(const string& strType, const string& strName)
{
    string strCont = Inc(string("const ") + strType + "&", \
                         string("Get") + ToName(strName), \
                         "",\
                         ""
                        );
    MergeSpace(strCont);
    return string("\t\t") + strCont;
}

string CClassCont::IncGetConst(const string& strType, const string& strName)
{
    string strCont = Inc(string("const ") + strType + "&", \
                         string("Get") + ToName(strName), \
                         "",\
                         "",\
                         true\
                        );
    MergeSpace(strCont);
    return string("\t\t") + strCont;
}

string CClassCont::IncCore()
{
    return string("\t\tvoid Core();\n");

}

string CClassCont::GetClassVar(const vector<pair<string, string> >& vecMem)
{
    unsigned int uiMaxTypeLength = 0;
    vector<pair<string, string> > vecVar;
    for (unsigned int uiCount = 0; uiCount < vecMem.size(); ++uiCount) {
        string strType(vecMem[uiCount].first);
        MergeSpace(strType);
        if (strType.length() > uiMaxTypeLength) {
            uiMaxTypeLength = strType.length();
        }
        vecVar.push_back(make_pair(strType, vecMem[uiCount].second));
    }
    string strCont = "\tprivate:\n";
    for (unsigned int uiCount = 0; uiCount < vecVar.size(); ++uiCount) {
        char szLine[PATH_LEN] = {0};
        sprintf(szLine, "\t\t%-*s m_%s;\n", uiMaxTypeLength, vecVar[uiCount].first.c_str(), \
            ToVar(vecVar[uiCount].first, vecVar[uiCount].second).c_str());
        strCont += szLine;
    }
    return strCont;
}

string CClassCont::Inc(const string& strRet, const string& strName, const string& strType, const string& strPara, bool bConst)
{
    string strCont = string("inline ")+strRet + " " + strName + "(";
    if (!strType.empty()) {
        strCont += strType + " " + strPara;
    }
    strCont += ")";
    if (bConst) {
        strCont += " const";
    }
    strCont += ";";
    return strCont;
}

string CClassCont::ToName(const string& strName)
{
    string strRet = strName;
    strRet[0] = toupper(strName[0]);
    return strRet;
}

string CClassCont::ToVar(const string& strType, const string& strName)
{
    string strRet;
    vector<string> vecTypes;
    size_t zdStart = 0;
    for (size_t zuCount = 0; zuCount < strType.length(); ++zuCount) {
        if (strType[zuCount] == ' ' || strType[zuCount] == '*') {
            if (zuCount > zdStart) {
                vecTypes.push_back(strType.substr(zdStart, zuCount - zdStart));
            }
            zdStart = zuCount + 1;
            if (strType[zuCount] == '*') {
                vecTypes.push_back("*");
            }
        }
    }
    if (zdStart < strType.length()) {
        vecTypes.push_back(strType.substr(zdStart, strType.length() - zdStart));
    }

    for (vector<string>::iterator iterType = vecTypes.begin(); iterType != vecTypes.end(); ++iterType) {
        string strPrev = GetPrev(*iterType);
        if (strPrev == "p") {
            if (strRet.length() == 2 && strRet == "uc") {
                strRet = "pusz";
            } else if (strRet.length() == 1 && strRet == "c") {
                strRet = "psz";
            } else {
                strRet = strPrev + strRet;
            }
        } else {
            strRet += strPrev;
        }
    }
    return strRet + ToName(strName);
}

string CClassCont::GetPrev(const string& strType)
{
    map<string, string>::iterator iterPrev = m_mapPrev.find(strType);
    if (iterPrev != m_mapPrev.end()) {
        return iterPrev->second;
    }
    if (strType[0] == 'C') {
        return "C";
    }
    if (BT_EndsWith(strType, "_S")) {
        return "st";
    }
    if (BT_StartsWith(strType, "vector")) {
        return "vec";
    }
    return string();
}

void CClassCont::MergeSpace(string& strCont)
{
    size_t zuPos =  isspace(strCont[0]) != 0 ? 0 : string::npos;
    for (size_t zuCount = 1; zuCount < strCont.length(); ++zuCount) {
        if (isspace(strCont[zuCount - 1]) != 0 && isspace(strCont[zuCount]) != 0) {
            if (zuPos == string::npos) {
                zuPos = zuCount;
            }
            continue;
        } else if (zuPos != string::npos){
            strCont[zuPos ++] = strCont[zuCount];
        }
    }
    strCont = strCont.substr(0, zuPos);
}

string CClassCont::GetDate()
{
    time_t timeNow = time(NULL);
    struct tm stTm;
    localtime_r(&timeNow, &stTm);
    ostringstream ossDate;
    ossDate << 1900 + stTm.tm_year  << "-" << (stTm.tm_mon < 9 ? "0" : "") << stTm.tm_mon + 1 << "-" << \
        (stTm.tm_mday < 10 ? "0" : "") << stTm.tm_mday;
    return ossDate.str();
}

string CClassCont::GetMacroIfndef(const string& strName)
{
    string strMacro = BT_ToUpperCopy(strName);
    BT_ReplaceAll(strMacro, ".", "_");
    strMacro += "_";
    return string("#ifndef ") + strMacro + "\n";
}

string CClassCont::GetMacroDefine(const string& strName)
{
    string strMacro = BT_ToUpperCopy(strName);
    BT_ReplaceAll(strMacro, ".", "_");
    strMacro += "_";
    return string("#define ") + strMacro + "\n";
}

string CClassCont::GetMacroEndif()
{
    return "#endif\n";
}

string CClassCont::GetClassEnd()
{
    return "};\n";
}

string CClassCont::SrcSet(const string& strClass, const string& strType, const string& strName)
{
    string strCont = \
        string("/*******************************************************************************\n") + \
        string(" * set ") + BT_ToLowerCopy(strName) + string("\n") + \
        string(" * Parameters:\n") + \
        string(" * ") + ToVar(strType, strName) + string(": ") + strName + string("\n") + \
        string(" *******************************************************************************/\n")\
        ;
    string strFunLine = string("inline void ") + strClass + string("::Set") + ToName(strName) + string("(const ") + \
        strType + string("& ") + ToVar(strType, strName) + string(")\n");
    MergeSpace(strFunLine);
    string strFun = string("{\n\tm_") + ToVar(strType, strName) + string(" = ") + ToVar(strType, strName) + ";\n}\n";
    return strCont + strFunLine + strFun;
}

string CClassCont::SrcAdd(const string& strClass, const string& strType, const string& strName)
{
    string strCont = \
        string("/*******************************************************************************\n") + \
        string(" * add ") + BT_ToLowerCopy(strName) + string("\n") + \
        string(" * Parameters:\n") + \
        string(" * ") + ToVar(strType, strName) + string(": ") + strName + string("\n") + \
        string(" *******************************************************************************/\n")\
        ;
    string strFunLine = string("inline void ") + strClass + string("::Add") + ToName(strName) + string("(const ") + \
        strType + string("& ") + ToVar(strType, strName) + string(")\n");
    MergeSpace(strFunLine);
    string strFun = string("{\n\tm_vec") + ToName(strName) + string(".push_back(") + ToVar(strType, strName) + ");\n}\n";
    return strCont + strFunLine + strFun;
}

string CClassCont::SrcGet(const string& strClass, const string& strType, const string& strName, const string& strVal, bool bConst)
{
    string strCont = \
        string("/*******************************************************************************\n") + \
        string(" * get ") + BT_ToLowerCopy(strName) + string("\n") + \
        string(" * Return-Value: ") + BT_ToLowerCopy(strName) + string("\n") + \
        string(" *******************************************************************************/\n")\
        ;
    string strFunLine = string("inline const ") + strType + string("& ") + strClass + string("::Get") + \
        strName + (bConst ? string("() const\n") : string("()\n"));
        //MergeSpace(strFunLine);
    string strFun = string("{\n\treturn ") + strVal + string(";\n}\n");
    return strCont + strFunLine + strFun;
}

string CClassCont::SrcStruct(const string& strClass, const string& strBase)
{
    return \
        string("/*******************************************************************************\n") + \
        string(" * construction\n") + \
        string(" *******************************************************************************/\n") +\
        (strBase.empty() ? string("") : (strBase + "::") ) + strClass + string("::") + strClass + string("()\n{\n\n}\n\n") + \
        string("/*******************************************************************************\n") + \
        string(" * deconstruction\n") + \
        string(" *******************************************************************************/\n") + \
        (strBase.empty() ? string("") : (strBase + "::") ) + strClass + string("::~") + strClass + string("()\n{\n\n}\n");
}

string CClassCont::StrGetCommentStart()
{
    return "/*******************************************************************************";
}
string CClassCont::StrGetCommentEnd()
{
    return " *******************************************************************************/";
}

string CClassCont::SrcCore(const string& strClass)
{
    return \
        string("/*******************************************************************************\n") + \
        string(" * thread interface\n") + \
        string(" *******************************************************************************/\n") +\
        strClass + string("::Core()\n{\n}\n");
}
