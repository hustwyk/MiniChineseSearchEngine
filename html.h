/*********************************************************************************
*Copyright(C), 2015, @York Lynn
*FileName:	hash.h
*Author:	王映焜
*Version:	V1.0
*Date:	2015.10.26
*Description:	网页内容的解析
*History:
1.Date:	2015.10.26
Author:	王映焜
Modification:	主要功能的构建和完善
**********************************************************************************/

#pragma once
#include "stdafx.h"
#include "io.h"
#include "iostream"
#include "string"


using namespace std;


class html
{
public:
	html();
	~html();
	static CString Extract(CString contents);
	static CString Title(CString contents);
	static CString ExtractwithSymbol(CString contents);

private:

};

