/*********************************************************************************
*Copyright(C), 2015, @York Lynn
*FileName:	hash.h
*Author:	��ӳ�j
*Version:	V1.0
*Date:	2015.10.26
*Description:	�ִ��㷨�����쵹�ű���ȡ���䡣
*History:
1.Date:	2015.10.26
Author:	��ӳ�j
Modification:	��Ҫ���ܵĹ���������
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
