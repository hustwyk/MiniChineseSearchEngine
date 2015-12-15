#include "stdafx.h"
#include "string"
#include "iostream"
#include "fstream"
#include "hash.h"

//************************************
// 方法名:	Hash
// 全名:		Hash::Hash
// 类型:		public 
// 返回值:	无
// 说明:		构造函数
//************************************
Hash::Hash()
{
}

//************************************
// 方法名:	~Hash
// 全名:		Hash::~Hash
// 类型:		public 
// 返回值:	无
// 说明:		析构函数
//************************************
Hash::~Hash()
{
}

//************************************
// 方法名:	SDBMHash
// 全名:		Hash::SDBMHash
// 类型:		public static 
// 返回值:	UINT
// 参数:		CString str  输入的中文词条
// 说明:		采用SDBM算法的hash值生成算法
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