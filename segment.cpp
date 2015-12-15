#include "stdafx.h"

static int dicLength = 273888;

//************************************
// ������:	segment
// ȫ��:		segment::segment
// ����:		public 
// ����ֵ:	��
// ˵��:		���캯��
//************************************
segment::segment()
{
}

//************************************
// ������:	~segment
// ȫ��:		segment::~segment
// ����:		public 
// ����ֵ:	��
// ˵��:		��������
//************************************
segment::~segment()
{
}

//************************************
// ������:	segmentString
// ȫ��:		segment::segmentString
// ����:		public static 
// ����ֵ:	void
// ����:		CString html   html�ĵ�������
// ����:		LPCTSTR dicName    �ʵ���
// ����:		int webID   ��ҳ�ĵ�ID
// ����:		int maxDicLength    �ʵ��д�����󳤶�
// ����:		CString title    ��ҳ�ĵ�����
// ����:		CString transWithSymbol    ��ҳ���ĺ����ַ���
// ˵��:		���������ҳ�����зִʲ����ù��쵹�ű�
//************************************
void segment::segmentString(CString html, LPCTSTR dicName, int webID, int maxDicLength, CString title, CString transWithSymbol)
{
	//����MMSEG�㷨���зִʴ���
	int htmlLength = html.GetLength();
	int htmlByte = 0;

	while (htmlByte < htmlLength - maxDicLength)//��ȥ��󳤶ȣ���֤�ĵ����һ���ʵ�������
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
					Chunk_temp->addWord1(word1_temp); //��ӵ�һ������
				else break;
				for (int j = 1;j <= maxDicLength;j++)
				{
					CString word2_temp = html.Mid((htmlByte + i), j);
					if (word2_temp.GetLength() < j)
						break;
					else
					{
						if ((Hash::HashFind(word2_temp)) || (word2_temp.GetLength() == 1))
							Chunk_temp->addWord2(word2_temp);//��ӵڶ�������
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
									Chunk_temp->addWord3(word3_temp);//���������жϲ���ӵ���������
									if (Chunk_temp->getSumLengthof3() > Chunk->getSumLengthof3())//����������ж�
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
										if (Chunk_temp->getAvrLengthof3() > Chunk->getAvrLengthof3())//ƽ�����������ж�
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
											if (Chunk_temp->getVarianceof3() < Chunk->getVarianceof3())//��С���������ж�
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
						//ֻ�������ʵ�ʱ���ж���������������
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
	//�����һ���ʽ��е�������
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
// ������:	sectionAbout
// ȫ��:		segment::sectionAbout
// ����:		public static 
// ����ֵ:	CString
// ����:		CString transWithSymbol   ��ҳ�ĵ����ĺ����ַ���
// ����:		CString insertData    ������Ĵ���
// ˵��:		����ҳ�н�ȡ���ؼ������ڵĶ��䲢����
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

