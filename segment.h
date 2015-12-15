/*********************************************************************************
*Copyright(C), 2015, @York Lynn
*FileName:	hash.h
*Author:	王映焜
*Version:	V1.0
*Date:	2015.10.26
*Description:	分词算法，构造倒排表，提取段落。
*History:
1.Date:	2015.10.26
Author:	王映焜
Modification:	主要功能的构建和完善
**********************************************************************************/

#pragma once
#include "stdafx.h"

using namespace std;


class segment
{
public:
	segment();
	~segment();
	static void segmentString(CString html, LPCTSTR dicName, int webID, int maxDicLength, CString title, CString transWithSymbol);
	static void insertTable(CString insertData, int webID, CString title, CString about);
	static CString sectionAbout(CString transWithSymbol, CString insertData);

private:

};
