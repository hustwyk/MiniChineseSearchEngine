#include "stdafx.h"

//************************************
// ������:	html
// ȫ��:		html::html
// ����:		public 
// ����ֵ:	��
// ˵��:		���캯��
//************************************
html::html()
{
}

//************************************
// ������:	~html
// ȫ��:		html::~html
// ����:		public 
// ����ֵ:	��
// ˵��:		��������
//************************************
html::~html()
{
}

//************************************
// ������:	Extract
// ȫ��:		html::Extract
// ����:		public static 
// ����ֵ:	CString
// ����:		CString contents  �����html�ĵ���ȡ�ĺ�����
// ˵��:		��html�еĺ�����ȡ����
//************************************
CString html::Extract(CString contents)
{
	int contentsLength = contents.GetLength();
	int countTemp = 0;
	CString contentBuf;

	while (countTemp < contentsLength)
	{
		wchar_t ch;
		ch = contents[countTemp];
		//���ĺ��ֵı��뷶Χ
		if ((ch>0x4e00) && (ch < 0x9fa5))
		{
			CString byte;
			byte.Format(_T("%c"), ch);
			contentBuf += byte;
		}
		countTemp++;
	}
	return contentBuf;
}

//************************************
// ������:	Title
// ȫ��:		html::Title
// ����:		public static 
// ����ֵ:	CString
// ����:		CString contents    �����html�ĵ���ȡ�ĺ�����
// ˵��:		��html�ĵ��н�ȡtitle����
//************************************
CString html::Title(CString contents)
{
	int contentsLength = contents.GetLength();
	int countTemp = 0;
	int titleFlag = 0;
	CString title;

	while (countTemp < contentsLength)
	{
		title = _T("");
		wchar_t ch;
		ch = contents[countTemp];
		//�ҵ�title��TITLE֮�����ʾ����ı�ǩ��������ȡ
		if (((ch == 'T') || (ch == 't')) && ((contents[countTemp + 1] == 'I') || (contents[countTemp + 1] == 'i')) && ((contents[countTemp + 2] == 'T') || (contents[countTemp + 2] == 't')) && ((contents[countTemp + 3] == 'L') || (contents[countTemp + 3] == 'l')) && ((contents[countTemp + 4] == 'E') || (contents[countTemp + 4] == 'e')))
		{
			for (int i = 6;contents[countTemp + i] != '<';i++)
			{
				CString byte2;
				byte2.Format(_T("%c"), contents[countTemp + i]);
				title += byte2;
			}
			break;
		}
		countTemp++;
	}

	return title;
}

//************************************
// ������:	ExtractwithSymbol
// ȫ��:		html::ExtractwithSymbol
// ����:		public static 
// ����ֵ:	CString
// ����:		CString contents    �����html�ĵ���ȡ�ĺ�����
// ˵��:		��html�еĺ��ּ����ķ�����ȡ����
//************************************
CString html::ExtractwithSymbol(CString contents)
{
	int contentsLength = contents.GetLength();
	int countTemp = 0;
	CString contentBufwithSymbol;

	while (countTemp < contentsLength)
	{
		wchar_t ch;
		ch = contents[countTemp];
		//���ĺ��ֺ��ַ������б��뷶Χ
		if ((ch>0x4e00) && (ch < 0x9fa5)||(ch == 0x3002) || (ch == 0xFF1F) || (ch == 0xFF01) || (ch == 0xFF0C) || (ch == 0x3001) || (ch == 0xFF1B) || (ch == 0xFF1A) || (ch == 0x201C) || (ch == 0x201D) || (ch == 0xFF08) || (ch == 0xFF09) || (ch == 0x2026) || (ch == 0x300A) || (ch == 0x300B))
		{
			CString byte;
			byte.Format(_T("%c"), ch);
			contentBufwithSymbol += byte;
		}
		countTemp++;
	}
	return contentBufwithSymbol;
}
