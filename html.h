/*********************************************************************************
*Copyright(C), 2015, @York Lynn
*FileName:	hash.h
*Author:	��ӳ�j
*Version:	V1.0
*Date:	2015.10.26
*Description:	��ҳ���ݵĽ���
*History:
1.Date:	2015.10.26
Author:	��ӳ�j
Modification:	��Ҫ���ܵĹ���������
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

