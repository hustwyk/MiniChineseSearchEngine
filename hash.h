/*********************************************************************************
*Copyright(C), 2015, @York Lynn
*FileName:	hash.h
*Author:	��ӳ�j
*Version:	V1.0
*Date:	2015.10.26
*Description:	hashֵ���ɺ�hash����
*History:
1.Date:	2015.10.26
Author:	��ӳ�j
Modification:	��Ҫ���ܵĹ���������
**********************************************************************************/

#pragma once
#include "stdafx.h"

using namespace std;

class Hash
{
public:
	Hash();
	~Hash();
	static UINT SDBMHash(CString str);
	static BOOL HashFind(CString findWord);
	static UINT HashFind2(CString findWord);

private:

};

