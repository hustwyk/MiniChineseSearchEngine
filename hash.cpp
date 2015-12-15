#include "stdafx.h"
#include "string"
#include "iostream"
#include "fstream"
#include "hash.h"

//************************************
// ������:	Hash
// ȫ��:		Hash::Hash
// ����:		public 
// ����ֵ:	��
// ˵��:		���캯��
//************************************
Hash::Hash()
{
}

//************************************
// ������:	~Hash
// ȫ��:		Hash::~Hash
// ����:		public 
// ����ֵ:	��
// ˵��:		��������
//************************************
Hash::~Hash()
{
}

//************************************
// ������:	SDBMHash
// ȫ��:		Hash::SDBMHash
// ����:		public static 
// ����ֵ:	UINT
// ����:		CString str  ��������Ĵ���
// ˵��:		����SDBM�㷨��hashֵ�����㷨
//************************************
UINT Hash::SDBMHash(CString str)
{
	UINT hash = 0;
	for (int i = 0;i < str.GetLength();i++)
	{
		hash = str[i] + (hash << 6) + (hash << 16) - hash;
	}
	return (hash & 0x7FFFFFFF);
}