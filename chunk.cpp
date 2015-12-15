#include "stdafx.h"

//************************************
// ������:	chunk
// ȫ��:		chunk::chunk
// ����:		public 
// ����ֵ:	��
// ˵��:		���캯��
//************************************
chunk::chunk()
{
	word1 = _T("");
	word2 = _T("");
	word3 = _T("");
}

//************************************
// ������:	~chunk
// ȫ��:		chunk::~chunk
// ����:		public 
// ����ֵ:	��
// ˵��:		��������
//************************************
chunk::~chunk()
{
}

//************************************
// ������:	addWord1
// ȫ��:		chunk::addWord1
// ����:		public 
// ����ֵ:	void
// ����:		CString word
// ˵��:		��ӵ�һ����
//************************************
void chunk::addWord1(CString word)
{
	word1 = word;
}

//************************************
// ������:	addWord2
// ȫ��:		chunk::addWord2
// ����:		public 
// ����ֵ:	void
// ����:		CString word
// ˵��:		��ӵڶ�����
//************************************
void chunk::addWord2(CString word)
{
	word2 = word;
}

//************************************
// ������:	addWord3
// ȫ��:		chunk::addWord3
// ����:		public 
// ����ֵ:	void
// ����:		CString word
// ˵��:		��ӵ�������
//************************************
void chunk::addWord3(CString word)
{
	word3 = word;
}

//************************************
// ������:	delWord1
// ȫ��:		chunk::delWord1
// ����:		public 
// ����ֵ:	void
// ˵��:		ɾ����һ����
//************************************
void chunk::delWord1()
{
	word1 = _T("");;
}

//************************************
// ������:	delWord2
// ȫ��:		chunk::delWord2
// ����:		public 
// ����ֵ:	void
// ˵��:		ɾ���ڶ�����
//************************************
void chunk::delWord2()
{
	word2 = _T("");
}

//************************************
// ������:	delWord3
// ȫ��:		chunk::delWord3
// ����:		public 
// ����ֵ:	void
// ˵��:		ɾ����������
//************************************
void chunk::delWord3()
{
	word3 = _T("");
}

//************************************
// ������:	getWord1
// ȫ��:		chunk::getWord1
// ����:		public 
// ����ֵ:	CString
// ˵��:		���ص�һ����
//************************************
CString chunk::getWord1()
{
	return word1;
}

//************************************
// ������:	getWord2
// ȫ��:		chunk::getWord2
// ����:		public 
// ����ֵ:	CString
// ˵��:		���صڶ�����
//************************************
CString chunk::getWord2()
{
	return word2;
}

//************************************
// ������:	getWord3
// ȫ��:		chunk::getWord3
// ����:		public 
// ����ֵ:	CString
// ˵��:		���ص�������
//************************************
CString chunk::getWord3()
{
	return word3;
}

//************************************
// ������:	getWord1Length
// ȫ��:		chunk::getWord1Length
// ����:		public 
// ����ֵ:	int
// ˵��:		���ص�һ���ʳ���
//************************************
int chunk::getWord1Length()
{
	return word1.GetLength();
}

//************************************
// ������:	getWord2Length
// ȫ��:		chunk::getWord2Length
// ����:		public 
// ����ֵ:	int
// ˵��:		���صڶ����ʳ���
//************************************
int chunk::getWord2Length()
{
	return word2.GetLength();
}

//************************************
// ������:	getWord3Length
// ȫ��:		chunk::getWord3Length
// ����:		public 
// ����ֵ:	int
// ˵��:		���ص������ʳ���
//************************************
int chunk::getWord3Length()
{
	return word3.GetLength();
}

//************************************
// ������:	getSumByteLengthof3
// ȫ��:		chunk::getSumByteLengthof3
// ����:		public 
// ����ֵ:	int
// ˵��:		�����������ܵ��ֽ���
//************************************
int chunk::getSumByteLengthof3()
{
	return (word1.GetLength() + word2.GetLength() + word3.GetLength())*2;
}

//************************************
// ������:	getSumLengthof3
// ȫ��:		chunk::getSumLengthof3
// ����:		public 
// ����ֵ:	int
// ˵��:		���������ʵ��ܳ���
//************************************
int chunk::getSumLengthof3()
{
	return (word1.GetLength() + word2.GetLength() + word3.GetLength());
}

//************************************
// ������:	getAvrLengthof3
// ȫ��:		chunk::getAvrLengthof3
// ����:		public 
// ����ֵ:	double
// ˵��:		���������ʵ�ƽ������
//************************************
double chunk::getAvrLengthof3()
{
	return (((double)word1.GetLength() + (double)word2.GetLength() + (double)word3.GetLength()) / 6.0);
}

//************************************
// ������:	getVarianceof3
// ȫ��:		chunk::getVarianceof3
// ����:		public 
// ����ֵ:	double
// ˵��:		���������ʳ��ȵķ���
//************************************
double chunk::getVarianceof3()
{
	double avr_temp = getAvrLengthof3();
	return ((avr_temp-word1.GetLength())*(avr_temp - word1.GetLength()) + (avr_temp - word2.GetLength())*(avr_temp - word2.GetLength()) + (avr_temp - word3.GetLength())*(avr_temp - word3.GetLength()));
}

//************************************
// ������:	getSumByteLengthof2
// ȫ��:		chunk::getSumByteLengthof2
// ����:		public 
// ����ֵ:	int
// ˵��:		����ǰ�����ʵ����ֽ���
//************************************
int chunk::getSumByteLengthof2()
{
	return (word1.GetLength() + word2.GetLength())*2;
}

//************************************
// ������:	getSumLengthof2
// ȫ��:		chunk::getSumLengthof2
// ����:		public 
// ����ֵ:	int
// ˵��:		����ǰ�����ʵ��ܳ���
//************************************
int chunk::getSumLengthof2()
{
	return (word1.GetLength() + word2.GetLength());
}

//************************************
// ������:	getAvrLengthof2
// ȫ��:		chunk::getAvrLengthof2
// ����:		public 
// ����ֵ:	double
// ˵��:		����ǰ�����ʵ�ƽ������
//************************************
double chunk::getAvrLengthof2()
{
	return (((double)word1.GetLength() + (double)word2.GetLength()) / 4.0);
}

//************************************
// ������:	getVarianceof2
// ȫ��:		chunk::getVarianceof2
// ����:		public 
// ����ֵ:	double
// ˵��:		����ǰ�����ʳ��ȵķ���
//************************************
double chunk::getVarianceof2()
{
	double avr_temp = getAvrLengthof2();
	return ((avr_temp - word1.GetLength())*(avr_temp - word1.GetLength()) + (avr_temp - word2.GetLength())*(avr_temp - word2.GetLength()));
}
