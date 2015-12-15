#include "stdafx.h"

//************************************
// 方法名:	html
// 全名:		html::html
// 类型:		public 
// 返回值:	无
// 说明:		构造函数
//************************************
html::html()
{
}

//************************************
// 方法名:	~html
// 全名:		html::~html
// 类型:		public 
// 返回值:	无
// 说明:		析构函数
//************************************
html::~html()
{
}

//************************************
// 方法名:	Extract
// 全名:		html::Extract
// 类型:		public static 
// 返回值:	CString
// 参数:		CString contents  输入的html文档提取的汉字流
// 说明:		将html中的汉字提取出来
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
		//中文汉字的编码范围
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
// 方法名:	Title
// 全名:		html::Title
// 类型:		public static 
// 返回值:	CString
// 参数:		CString contents    输入的html文档提取的汉字流
// 说明:		从html文档中截取title内容
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
		//找到title或TITLE之类的提示标题的标签并进行提取
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
// 方法名:	ExtractwithSymbol
// 全名:		html::ExtractwithSymbol
// 类型:		public static 
// 返回值:	CString
// 参数:		CString contents    输入的html文档提取的汉字流
// 说明:		将html中的汉字及中文符号提取出来
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
		//中文汉字和字符的所有编码范围
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
