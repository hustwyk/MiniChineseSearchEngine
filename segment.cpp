#include "stdafx.h"

static int dicLength = 273888;

//************************************
// 方法名:	segment
// 全名:		segment::segment
// 类型:		public 
// 返回值:	无
// 说明:		构造函数
//************************************
segment::segment()
{
}

//************************************
// 方法名:	~segment
// 全名:		segment::~segment
// 类型:		public 
// 返回值:	无
// 说明:		析构函数
//************************************
segment::~segment()
{
}

//************************************
// 方法名:	segmentString
// 全名:		segment::segmentString
// 类型:		public static 
// 返回值:	void
// 参数:		CString html   html文档汉字流
// 参数:		LPCTSTR dicName    词典名
// 参数:		int webID   网页文档ID
// 参数:		int maxDicLength    词典中词条最大长度
// 参数:		CString title    网页文档标题
// 参数:		CString transWithSymbol    网页中文汉字字符流
// 说明:		对输入的网页流进行分词并调用构造倒排表
//************************************
void segment::segmentString(CString html, LPCTSTR dicName, int webID, int maxDicLength, CString title, CString transWithSymbol)
{
	//采用MMSEG算法进行分词处理
	int htmlLength = html.GetLength();
	int htmlByte = 0;

	while (htmlByte < htmlLength - maxDicLength)//减去最大长度，保证文档最后一个词单独处理
	{
		chunk *Chunk = new chunk();
		chunk *Chunk_temp = new chunk();
		for (int i = 1;i <= maxDicLength;i++)
		{
			CString word1_temp = html.Mid(htmlByte,i);
			if (word1_temp.GetLength() < i)
				break;
			else
			{
				if ((Hash::HashFind(word1_temp)) || (word1_temp.GetLength() == 1))
					Chunk_temp->addWord1(word1_temp); //添加第一个词条
				else break;
				for (int j = 1;j <= maxDicLength;j++)
				{
					CString word2_temp = html.Mid((htmlByte + i), j);
					if (word2_temp.GetLength() < j)
						break;
					else
					{
						if ((Hash::HashFind(word2_temp)) || (word2_temp.GetLength() == 1))
							Chunk_temp->addWord2(word2_temp);//添加第二个词条
						else break;
						for (int k = 1;k <= maxDicLength;k++)
						{
							CString word3_temp = html.Mid((htmlByte + i + j), k);
							if (word3_temp.GetLength() < k)
								break;
							else
							{
								if ((Hash::HashFind(word3_temp)) || (word3_temp.GetLength() == 1))
								{
									Chunk_temp->addWord3(word3_temp);//进行条件判断并添加第三个词条
									if (Chunk_temp->getSumLengthof3() > Chunk->getSumLengthof3())//最长长度条件判断
									{
										Chunk->addWord1(Chunk_temp->getWord1());
										Chunk->addWord2(Chunk_temp->getWord2());
										Chunk->addWord3(Chunk_temp->getWord3());
										break;
									}
									else if (Chunk_temp->getSumLengthof3() < Chunk->getSumLengthof3())
										break;
									else if (Chunk_temp->getSumLengthof3() == Chunk->getSumLengthof3())
									{
										if (Chunk_temp->getAvrLengthof3() > Chunk->getAvrLengthof3())//平均长度条件判断
										{
											Chunk->addWord1(Chunk_temp->getWord1());
											Chunk->addWord2(Chunk_temp->getWord2());
											Chunk->addWord3(Chunk_temp->getWord3());
											break;
										}
										else if (Chunk_temp->getAvrLengthof3() < Chunk->getAvrLengthof3())
											break;
										else if (Chunk_temp->getAvrLengthof3() == Chunk->getAvrLengthof3())
										{
											if (Chunk_temp->getVarianceof3() < Chunk->getVarianceof3())//最小方差条件判断
											{
												Chunk->addWord1(Chunk_temp->getWord1());
												Chunk->addWord2(Chunk_temp->getWord2());
												Chunk->addWord3(Chunk_temp->getWord3());
												break;
											}
											else break;
										}
									}
								}
								else break;
							}
						}
						//只有两个词的时候判断条件和以上类似
						if ((Chunk_temp->getWord1Length() > 0) && (Chunk_temp->getWord2Length() > 0) && (Chunk_temp->getWord3Length() <= 0))
						{
							if (Chunk_temp->getSumLengthof2() > Chunk->getSumLengthof2())
							{
								Chunk->addWord1(Chunk_temp->getWord1());
								Chunk->addWord2(Chunk_temp->getWord2());
								break;
							}
							else if (Chunk_temp->getSumLengthof2() < Chunk->getSumLengthof2())
								break;
							else if (Chunk_temp->getSumLengthof2() == Chunk->getSumLengthof2())
							{
								if (Chunk_temp->getAvrLengthof2() > Chunk->getAvrLengthof2())
								{
									Chunk->addWord1(Chunk_temp->getWord1());
									Chunk->addWord2(Chunk_temp->getWord2());
									break;
								}
								else if (Chunk_temp->getAvrLengthof2() < Chunk->getAvrLengthof2())
									break;
								else if (Chunk_temp->getAvrLengthof2() == Chunk->getAvrLengthof2())
								{
									if (Chunk_temp->getVarianceof2() < Chunk->getVarianceof2())
									{
										Chunk->addWord1(Chunk_temp->getWord1());
										Chunk->addWord2(Chunk_temp->getWord2());
										break;
									}
									else break;
								}
							}
						}
						if ((Chunk_temp->getWord1Length() > 0) && (Chunk_temp->getWord2Length() <= 0) && (Chunk_temp->getWord3Length() <= 0))
						{
							Chunk->addWord1(Chunk_temp->getWord1());
							break;
						}
					}
				}
			}
		}
		
		htmlByte += Chunk->getWord1Length();

		if (Chunk->getWord1Length() > 0)
		{
			CString about = sectionAbout(transWithSymbol, Chunk->getWord1());
			insertTable(Chunk->getWord1(), webID, title, about);
		}
		
	}
	//对最后一个词进行单独处理
	CString lastword = html.Mid(htmlByte, (htmlLength - htmlByte));
	for (int m = 0;m < htmlLength - htmlByte;)
	{
		for (int n = htmlLength - htmlByte;n > 0;n--)
		{
			if (Hash::HashFind(lastword.Mid(m, n)))
			{
				CString about = sectionAbout(transWithSymbol, lastword.Mid(m, n));
				insertTable(lastword.Mid(m, n), webID, title, about);
				
				m += lastword.Mid(m, n).GetLength();
				break;
			}
			else
			{
				if (n == 1)
				{
					CString about = sectionAbout(transWithSymbol, lastword.Mid(m, n));
					insertTable(lastword.Mid(m, n), webID, title, about);
					m += lastword.Mid(m, n).GetLength();
					break;
				}
			}
		}
	}
	
}


//************************************
// 方法名:	sectionAbout
// 全名:		segment::sectionAbout
// 类型:		public static 
// 返回值:	CString
// 参数:		CString transWithSymbol   网页文档中文汉字字符流
// 参数:		CString insertData    待处理的词条
// 说明:		从网页中截取到关键词所在的段落并返回
//************************************
CString segment::sectionAbout(CString transWithSymbol, CString insertData)
{
	int transLength = transWithSymbol.GetLength();
	int insertLength = insertData.GetLength();

	CString about = _T("");
	int flag = 0;

	for (int i = 0;i < transLength;i++)
	{
		if (transWithSymbol[i] == insertData[0])
		{
			flag = 1;
			for (int j = 1;j < insertLength;j++)
			{
				if (transWithSymbol[i + j] != insertData[j])
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				if (i > 10)
				{
					int p = insertLength + 50;
					if ((i+p) < transLength)
						about = transWithSymbol.Mid(i - 10, 10+p);
					else 
						about = transWithSymbol.Mid(i - 10, 10+transLength-i);
					
				}
				else
				{
					int p = insertLength + 50;
					if ((i + p) < transLength)
						about = transWithSymbol.Mid(0, i + p);
					else
						about = transWithSymbol.Mid(0, transLength - i);
					
				}
				return about;
			}
		}
		else about = _T("");
	}
	return about;
}

