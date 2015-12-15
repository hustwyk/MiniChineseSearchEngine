/*********************************************************************************
*Copyright(C), 2015, @York Lynn
*FileName:	hash.h
*Author:	王映焜
*Version:	V1.0
*Date:	2015.10.26
*Description:	hash值生成和hash查找
*History:
1.Date:	2015.10.26
Author:	王映焜
Modification:	主要功能的构建和完善
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

