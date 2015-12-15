/*********************************************************************************
*Copyright(C), 2015, @York Lynn
*FileName:	chunk.h  
*Author:	王映焜 
*Version:	V1.0
*Date:	2015.10.26 
*Description:	主要用于分词中的chunk的一系列操作
*History:
1.Date:	2015.10.26
Author:	王映焜
Modification:	主要功能的构建和完善
**********************************************************************************/

#pragma once
#include "stdafx.h"

using namespace std;


class chunk
{
public:
	chunk();
	~chunk();
	void addWord1(CString word);
	void addWord2(CString word);
	void addWord3(CString word);
	void delWord1();
	void delWord2();
	void delWord3();
	CString getWord1();
	CString getWord2();
	CString getWord3();
	int getWord1Length();
	int getWord2Length();
	int getWord3Length();
	int getSumByteLengthof3();
	int getSumLengthof3();
	double getAvrLengthof3();
	double getVarianceof3();
	int getSumByteLengthof2();
	int getSumLengthof2();
	double getAvrLengthof2();
	double getVarianceof2();
private:
	CString word1;
	CString word2;
	CString word3;
};