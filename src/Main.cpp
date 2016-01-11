/*
 * Main.cpp
 *
 * Created on: 2015-10-14
 *     Author: fuliang
 */

#include "Main.h"
#include "Header.h"
#include "Source.h"
#include "BUtility.h"
#include "XMLParser.h"
#include "ClassPara.h"
#include "ClassCont.h"

#include <map>
#include <set>
#include <vector>
#include <algorithm>

#include <stdio.h>

CMain::CMain()
{

}

CMain::~CMain()
{

}

void CMain::Core(OPTION_S* pstOpt)
{
    CXMLParser CParser;
    BT_AUTO(vecDetail, CParser.Parse(pstOpt->m_szXMLFile));
//    PrintDetail(vecDetail);

    CHeader CInc;
    CInc.Core(vecDetail);

    CSource CSrc;
    CSrc.Core(vecDetail);
}

void CMain::PrintDetail(vector<CClassDetail *>& vecDetail)
{
    for (BT_AUTO(iterDetail, vecDetail.begin()); iterDetail != vecDetail.end(); ++iterDetail) {
        (*iterDetail)->Print();
    }
}

