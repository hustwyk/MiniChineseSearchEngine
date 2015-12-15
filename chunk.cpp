#include "stdafx.h"

//************************************
// 方法名:	chunk
// 全名:		chunk::chunk
// 类型:		public 
// 返回值:	无
// 说明:		构造函数
//************************************
chunk::chunk()
{
	word1 = _T("");
	word2 = _T("");
	word3 = _T("");
}

//************************************
// 方法名:	~chunk
// 全名:		chunk::~chunk
// 类型:		public 
// 返回值:	无
// 说明:		析构函数
//************************************
chunk::~chunk()
{
}

//************************************
// 方法名:	addWord1
// 全名:		chunk::addWord1
// 类型:		public 
// 返回值:	void
// 参数:		CString word
// 说明:		添加第一个词
//************************************
void chunk::addWord1(CString word)
{
	word1 = word;
}

//************************************
// 方法名:	addWord2
// 全名:		chunk::addWord2
// 类型:		public 
// 返回值:	void
// 参数:		CString word
// 说明:		添加第二个词
//************************************
void chunk::addWord2(CString word)
{
	word2 = word;
}

//************************************
// 方法名:	addWord3
// 全名:		chunk::addWord3
// 类型:		public 
// 返回值:	void
// 参数:		CString word
// 说明:		添加第三个词
//************************************
void chunk::addWord3(CString word)
{
	word3 = word;
}

//************************************
// 方法名:	delWord1
// 全名:		chunk::delWord1
// 类型:		public 
// 返回值:	void
// 说明:		删除第一个词
//************************************
void chunk::delWord1()
{
	word1 = _T("");;
}

//************************************
// 方法名:	delWord2
// 全名:		chunk::delWord2
// 类型:		public 
// 返回值:	void
// 说明:		删除第二个词
//************************************
void chunk::delWord2()
{
	word2 = _T("");
}

//************************************
// 方法名:	delWord3
// 全名:		chunk::delWord3
// 类型:		public 
// 返回值:	void
// 说明:		删除低三个词
//************************************
void chunk::delWord3()
{
	word3 = _T("");
}

//************************************
// 方法名:	getWord1
// 全名:		chunk::getWord1
// 类型:		public 
// 返回值:	CString
// 说明:		返回第一个词
//************************************
CString chunk::getWord1()
{
	return word1;
}

//************************************
// 方法名:	getWord2
// 全名:		chunk::getWord2
// 类型:		public 
// 返回值:	CString
// 说明:		返回第二个词
//************************************
CString chunk::getWord2()
{
	return word2;
}

//************************************
// 方法名:	getWord3
// 全名:		chunk::getWord3
// 类型:		public 
// 返回值:	CString
// 说明:		返回第三个词
//************************************
CString chunk::getWord3()
{
	return word3;
}

//************************************
// 方法名:	getWord1Length
// 全名:		chunk::getWord1Length
// 类型:		public 
// 返回值:	int
// 说明:		返回第一个词长度
//************************************
int chunk::getWord1Length()
{
	return word1.GetLength();
}

//************************************
// 方法名:	getWord2Length
// 全名:		chunk::getWord2Length
// 类型:		public 
// 返回值:	int
// 说明:		返回第二个词长度
//************************************
int chunk::getWord2Length()
{
	return word2.GetLength();
}

//************************************
// 方法名:	getWord3Length
// 全名:		chunk::getWord3Length
// 类型:		public 
// 返回值:	int
// 说明:		返回第三个词长度
//************************************
int chunk::getWord3Length()
{
	return word3.GetLength();
}

//************************************
// 方法名:	getSumByteLengthof3
// 全名:		chunk::getSumByteLengthof3
// 类型:		public 
// 返回值:	int
// 说明:		返回三个词总的字节数
//************************************
int chunk::getSumByteLengthof3()
{
	return (word1.GetLength() + word2.GetLength() + word3.GetLength())*2;
}

//************************************
// 方法名:	getSumLengthof3
// 全名:		chunk::getSumLengthof3
// 类型:		public 
// 返回值:	int
// 说明:		返回三个词的总长度
//************************************
int chunk::getSumLengthof3()
{
	return (word1.GetLength() + word2.GetLength() + word3.GetLength());
}

//************************************
// 方法名:	getAvrLengthof3
// 全名:		chunk::getAvrLengthof3
// 类型:		public 
// 返回值:	double
// 说明:		返回三个词的平均长度
//************************************
double chunk::getAvrLengthof3()
{
	return (((double)word1.GetLength() + (double)word2.GetLength() + (double)word3.GetLength()) / 6.0);
}

//************************************
// 方法名:	getVarianceof3
// 全名:		chunk::getVarianceof3
// 类型:		public 
// 返回值:	double
// 说明:		返回三个词长度的方差
//************************************
double chunk::getVarianceof3()
{
	double avr_temp = getAvrLengthof3();
	return ((avr_temp-word1.GetLength())*(avr_temp - word1.GetLength()) + (avr_temp - word2.GetLength())*(avr_temp - word2.GetLength()) + (avr_temp - word3.GetLength())*(avr_temp - word3.GetLength()));
}

//************************************
// 方法名:	getSumByteLengthof2
// 全名:		chunk::getSumByteLengthof2
// 类型:		public 
// 返回值:	int
// 说明:		返回前两个词的总字节数
//************************************
int chunk::getSumByteLengthof2()
{
	return (word1.GetLength() + word2.GetLength())*2;
}

//************************************
// 方法名:	getSumLengthof2
// 全名:		chunk::getSumLengthof2
// 类型:		public 
// 返回值:	int
// 说明:		返回前两个词的总长度
//************************************
int chunk::getSumLengthof2()
{
	return (word1.GetLength() + word2.GetLength());
}

//************************************
// 方法名:	getAvrLengthof2
// 全名:		chunk::getAvrLengthof2
// 类型:		public 
// 返回值:	double
// 说明:		返回前两个词的平均长度
//************************************
double chunk::getAvrLengthof2()
{
	return (((double)word1.GetLength() + (double)word2.GetLength()) / 4.0);
}

//************************************
// 方法名:	getVarianceof2
// 全名:		chunk::getVarianceof2
// 类型:		public 
// 返回值:	double
// 说明:		返回前两个词长度的方差
//************************************
double chunk::getVarianceof2()
{
	double avr_temp = getAvrLengthof2();
	return ((avr_temp - word1.GetLength())*(avr_temp - word1.GetLength()) + (avr_temp - word2.GetLength())*(avr_temp - word2.GetLength()));
}
