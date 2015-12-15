
// SearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "string"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//声明全局变量
static int dicLength = 273888;
static int webLength = 189;
static int hashLength = 300000;
static int maxWordLength = 18;
static double percentLoading1 = 0;
static int percent1 = 0;
static double percentLoading2 = 0;
CString dicName = _T("SearchDic.txt");
CString webName_base = _T("html\\");
//全局hash表初始化
HashNode HashTable[300000];
//界面类的指针
CSearchDlg* pDlg;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

//关于窗口
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSearchDlg 对话框
CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEARCH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_searchRichEdit);
	DDX_Control(pDX, IDC_RICHEDIT22, m_searchRichEdit2);
	DDX_Control(pDX, IDSEARCH, m_searchButton1);
	DDX_Control(pDX, IDSEARCH2, m_searchButton2);
	DDX_Control(pDX, IDC_RICHEDIT23, m_searchRichEdit3);
	DDX_Control(pDX, IDC_INITIAL_BUTTON1, m_iniButton1);
	DDX_Control(pDX, IDC_INITIAL_BUTTON2, m_iniButton2);
	DDX_Control(pDX, IDC_LOGO_BUTTON1, m_logoButton1);
	DDX_Control(pDX, IDC_LOGO_BUTTON2, m_logoButton2);
	DDX_Control(pDX, IDC_TIP_RICHEDIT2, m_tipRichEdit1);
	DDX_Control(pDX, IDC_TIP_RICHEDIT22, m_tipRichEdit2);
	DDX_Control(pDX, IDC_BUTTONLOADING, m_buttonLoading);
}

BEGIN_MESSAGE_MAP(CSearchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDSEARCH, &CSearchDlg::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_INITIAL_BUTTON1, &CSearchDlg::OnBnClickedInitialButton1)
	ON_BN_CLICKED(IDC_INITIAL_BUTTON2, &CSearchDlg::OnBnClickedInitialButton2)
	ON_BN_CLICKED(IDSEARCH2, &CSearchDlg::OnBnClickedSearch2)
	ON_BN_CLICKED(IDC_LOGO_BUTTON2, &CSearchDlg::OnBnClickedLogoButton2)
	ON_BN_CLICKED(IDC_LOGO_BUTTON1, &CSearchDlg::OnBnClickedLogoButton1)
	ON_NOTIFY(EN_LINK, IDC_RICHEDIT23, &CSearchDlg::OnEnLinkRichedit23)
END_MESSAGE_MAP()



//************************************
// 方法名:	GetDicLength
// 全名:		GetDicLength
// 类型:		public 
// 返回值:	int
// 说明:		返回字典词条数
//************************************
int GetDicLength()
{
	CFile Dic;
	int maxLength = 0;
	CString word;
	Dic.Open(dicName, CFile::modeRead);
	
	//将unicode编码的前两个无用字节去掉
	wchar_t ch;
	Dic.Read(&ch, 2);

	for (int process = 0;process < dicLength;process++)
	{
		word.Empty();
		while (1)
		{
			Dic.Read(&ch, 2);
			//读到回车的时候说明已经读取一个词
			if (ch != '\n')
				word.AppendChar(ch);
			else break;
		}
		if ((word.GetLength())>maxLength)
			maxLength = word.GetLength();
	}
	return maxLength;
}
 
//************************************
// 方法名:	MyProgressCtrl1
// 全名:		MyProgressCtrl1
// 类型:		public 
// 返回值:	UINT
// 参数:		LPVOID p   线程指针参数
// 说明:		加载词典线程
//************************************
void DictionaryLoading()
{
	CString strPercent;
	int percent = 0;
	int percenttemp = 0;
	int process = 0;
	CString word;
	CFile Dic;
	Dic.Open(dicName,CFile::modeRead);

	//将unicode编码的前两个无用字节去掉
	wchar_t ch;
	Dic.Read(&ch, 2);

	for (;process < dicLength;process++)
	{
		word.Empty();
		while (1)
		{
			Dic.Read(&ch, 2);
			
			if (ch != '\n')
				word.AppendChar(ch);
			else break;
		}
		
		//生成哈希表
		UINT hashValue = Hash::SDBMHash(word);
		UINT hashOrder = hashValue % hashLength;
		int ij;
		//散列地址法进行hash
		for ( ij = 0;HashTable[(hashOrder + ij) % hashLength].occupancy_Flag != 0;ij++);
		HashTable[(hashOrder + ij) % hashLength].occupancy_Flag = 1;
		HashTable[(hashOrder + ij) % hashLength].word = word;
		//percent1用于标示是否完成
		percent1 = process;
		percentLoading1 = process / (dicLength - 1);
	}
	MessageBox(0,_T("词库初始化完毕"), _T("Initial"), MB_OK);
	CString num;
	num.Format(_T("%f"),percentLoading1);
	OutputDebugString(num);
	Dic.Close();
	word.ReleaseBuffer();

	/*return 0;*/
}

//************************************
// 方法名:	MyProgressCtrl2
// 全名:		MyProgressCtrl2
// 类型:		public 
// 返回值:	UINT
// 参数:		LPVOID p   线程指针参数
// 说明:		加载网页线程
//************************************
void WebContentLoading()
{
	int percent = 0;
	int piece = 0;
	CString str;
	CFile Web;
	int webNum = webLength;

	wchar_t ch;
	
	for (;piece < webNum;piece++)
	{
		CString num;
		num.Format(_T("%d"), piece);
		CString webName = webName_base + num + _T(".html");

		if (Web.Open(webName, CFile::modeRead))
		{
			Web.Read(&ch, 2);
			str.Empty();
			int i = Web.GetLength() - 2;
			wchar_t *ch2;
			ch2 = (wchar_t*)malloc((i / 2 + 1)*sizeof(wchar_t));
			
			Web.Read(ch2, i);
			ch2[i / 2] = '\0';
			str.Format(_T("%s"), ch2);
			//对网页内容进行解析，分离其中的关键信息
			CString trans = html::Extract(str);
			CString title = html::Title(str);
			CString transWithSymbol = html::ExtractwithSymbol(str);
			//对解析的内容进行分词和构造倒排表
			segment::segmentString(trans, dicName, piece, maxWordLength, title, transWithSymbol);
			
			Web.Close();
			free(ch2);
			ch2 = NULL;
			str.ReleaseBuffer();
		}
		percentLoading2 = piece / (webNum - 1);
	}
	MessageBox(0, _T("网页初始化完毕"), _T("Initial"), MB_OK);
	/*return 0;*/
}


//************************************
// 方法名:	HashFind
// 全名:		Hash::HashFind
// 类型:		public static
// 返回值:	BOOL
// 参数:		CString findWord   输入的关键词条
// 说明:		哈希查找，用来判断输入的词是否在词典中
//************************************
BOOL Hash::HashFind(CString findWord)
{
	UINT hash = Hash::SDBMHash(findWord);
	UINT hashTemp = hash % hashLength;
	//散列地址法进行查找
	for (int i = 0;HashTable[(hashTemp + i) % hashLength].occupancy_Flag != 0;i++)
	{
		if (HashTable[(hashTemp + i) % hashLength].word == findWord)
			return TRUE;
	}
	return FALSE;
}


//************************************
// 方法名:	HashFind2
// 全名:		Hash::HashFind2
// 类型:		public static 
// 返回值:	UINT
// 参数:		CString findWord   输入的关键词条
// 说明:		返回输入词的哈希地址，若该词不存在，则返回-1
//************************************
UINT Hash::HashFind2(CString findWord)
{
	UINT hash = Hash::SDBMHash(findWord);
	UINT hashTemp = hash % hashLength;

	for (int i = 0;HashTable[(hashTemp + i) % hashLength].occupancy_Flag != 0;i++)
	{
		if (HashTable[(hashTemp + i) % hashLength].word == findWord)
			return ((hashTemp + i) % hashLength);
	}
	return -1;
}

//************************************
// 方法名:	insertTable
// 全名:		segment::insertTable
// 类型:		public static 
// 返回值:	void
// 参数:		CString insertData   待插入的词条
// 参数:		int webID   该网页文档的ID
// 参数:		CString title    该网页文档中的标题
// 参数:		CString about    针对该关键词在网页中的段落
// 说明:		构造倒排表，并插入到词典链表中
//************************************
void segment::insertTable(CString insertData, int webID, CString title, CString about)
{
	if (Hash::HashFind(insertData))
	{
		UINT hashTemp = Hash::HashFind2(insertData);

		if (hashTemp != -1) //判断词典中该位置有没有被占用
		{
			//如果该位置被占用
			webNode** nodeTemp = &(HashTable[hashTemp].webNode);
			//找该词在的位置
			for (;*nodeTemp != NULL;nodeTemp = &((*nodeTemp)->nextnode))
			{
				if ((*nodeTemp)->webID == webID)
					break;
			}
			//如果没找到，说明该词的节点尚未创建
			if (*nodeTemp == NULL)
			{
				*nodeTemp = (webNode*)malloc(sizeof(webNode));
				(*nodeTemp)->freq = 0;
				(*nodeTemp)->webID = 0;
				(*nodeTemp)->Title = new CString();
				(*nodeTemp)->About = new CString();
				(*nodeTemp)->nextnode = NULL;
			}
			//对ID、Title、About内容进行判断和更新
			if ((*nodeTemp)->webID != webID)
				(*nodeTemp)->webID = webID;
			if (*((*nodeTemp)->Title) != title)
				*((*nodeTemp)->Title) = title;
			if (*((*nodeTemp)->About) != about)
				*((*nodeTemp)->About) = about;

			(*nodeTemp)->freq++;
		}
	}
}


//************************************
// 方法名:	showContents
// 全名:		CSearchDlg::showContents
// 类型:		public 
// 返回值:	void
// 参数:		CString SearchWord   搜索的关键词条
// 说明:		显示页面的显示处理，不同文字的格式以及输出的格式
//************************************
void CSearchDlg::showContents(CString SearchWord)
{
	//不同格式的字体信息
	CHARFORMAT cf1;
	ZeroMemory(&cf1, sizeof(CHARFORMAT));
	cf1.cbSize = sizeof(CHARFORMAT);
	cf1.dwMask |= CFM_SIZE;
	cf1.yHeight = 250;
	cf1.dwMask |= CFM_COLOR;
	cf1.crTextColor = RGB(0, 0, 204);
	cf1.dwMask |= CFM_FACE;
	cf1.dwMask |= CFM_LINK;
	cf1.dwEffects |= CFE_LINK;
	wcscpy(cf1.szFaceName, _T("黑体"));

	CHARFORMAT cf2;
	ZeroMemory(&cf2, sizeof(CHARFORMAT));
	cf2.cbSize = sizeof(CHARFORMAT);
	cf2.dwMask |= CFM_SIZE;
	cf2.yHeight = 200;
	cf2.dwMask |= CFM_COLOR;
	cf2.crTextColor = RGB(51, 51, 51);
	cf2.dwMask |= CFM_FACE;
	wcscpy(cf2.szFaceName, _T("宋体"));

	CHARFORMAT cf3;
	ZeroMemory(&cf3, sizeof(CHARFORMAT));
	cf3.cbSize = sizeof(CHARFORMAT);
	cf3.dwMask |= CFM_SIZE;
	cf3.yHeight = 180;
	cf3.dwMask |= CFM_COLOR;
	cf3.crTextColor = RGB(153, 153, 153);
	cf3.dwMask |= CFM_FACE;
	wcscpy(cf3.szFaceName, _T("宋体"));

	CHARFORMAT cf4;
	ZeroMemory(&cf4, sizeof(CHARFORMAT));
	cf4.cbSize = sizeof(CHARFORMAT);
	cf4.dwMask |= CFM_SIZE;
	cf4.yHeight = 1;
	cf4.dwMask |= CFM_COLOR;
	cf4.crTextColor = RGB(255, 255, 255);
	cf4.dwMask |= CFM_FACE;
	cf4.dwMask |= CFM_LINK;
	cf4.dwEffects |= CFE_LINK;
	wcscpy(cf4.szFaceName, _T("黑体"));

	//对词条倒排表信息进行输出
	int i = Hash::HashFind2(SearchWord);
	
	webNode** Temp = &(HashTable[i].webNode);

	m_searchRichEdit3.SetWindowTextW(_T(""));
	int j;
	for (j = 0;*Temp != NULL; j++)
	{
		if ((*Temp)->nextnode != NULL)
		{
			CString enter = _T("\n");

			CString title = (*(*Temp)->Title);

			CString webID;
			int num = (*Temp)->webID;
			webID.Format(_T("%d"), num);

			m_searchRichEdit3.SetEventMask(ENM_LINK);
			m_searchRichEdit3.SetSelectionCharFormat(cf4);
			m_searchRichEdit3.ReplaceSel(webID);
			m_searchRichEdit3.SetSelectionCharFormat(cf1);
			m_searchRichEdit3.ReplaceSel(title);
			m_searchRichEdit3.ReplaceSel(enter);

			CString about = (*(*Temp)->About);

			m_searchRichEdit3.SetSelectionCharFormat(cf2);
			m_searchRichEdit3.ReplaceSel(about);
			m_searchRichEdit3.ReplaceSel(enter);
			m_searchRichEdit3.ReplaceSel(enter);

			Temp = &((*Temp)->nextnode);
		}
		else break;
	}
	//显示查找提示
	m_tipRichEdit1.SetWindowTextW(_T(""));

	CString tip1 = _T("Coogle为您找到相关结果约");
	CString tip2 = _T("个");
	CString tipnum;
	tipnum.Format(_T("%d"), j);
	CString Tip = tip1 + tipnum + tip2;

	m_tipRichEdit1.SetSelectionCharFormat(cf3);
	m_tipRichEdit1.ReplaceSel(Tip);
	
}


//************************************
// 方法名:	combineTable
// 全名:		CSearchDlg::combineTable
// 类型:		public 
// 返回值:	void
// 参数:		CString inputData    输入的关键词条
// 参数:		int maxDicLength    字典中词条的最长长度
// 说明:		对输入进行分词并进行查找再对倒排表进行合并，返回合并后的倒排表
//************************************
void CSearchDlg::combineTable(CString inputData, int maxDicLength)
{
	//对输入的关键字进行分词
	int htmlLength = inputData.GetLength();
	int htmlByte = 0;

	while (htmlByte < htmlLength - maxDicLength)
	{
		chunk *Chunk = new chunk();
		chunk *Chunk_temp = new chunk();
		for (int i = 1;i <= maxDicLength;i++)
		{
			CString word1_temp = inputData.Mid(htmlByte, i);
			if (word1_temp.GetLength() < i)
				break;
			else
			{
				if ((Hash::HashFind(word1_temp)) || (word1_temp.GetLength() == 1))
					Chunk_temp->addWord1(word1_temp);
				else break;
				for (int j = 1;j <= maxDicLength;j++)
				{
					CString word2_temp = inputData.Mid((htmlByte + i), j);
					if (word2_temp.GetLength() < j)
						break;
					else
					{
						if ((Hash::HashFind(word2_temp)) || (word2_temp.GetLength() == 1))
							Chunk_temp->addWord2(word2_temp);
						else break;
						for (int k = 1;k <= maxDicLength;k++)
						{
							CString word3_temp = inputData.Mid((htmlByte + i + j), k);
							if (word3_temp.GetLength() < k)
								break;
							else
							{
								if ((Hash::HashFind(word3_temp)) || (word3_temp.GetLength() == 1))
								{
									Chunk_temp->addWord3(word3_temp);
									if (Chunk_temp->getSumLengthof3() > Chunk->getSumLengthof3())
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
										if (Chunk_temp->getAvrLengthof3() > Chunk->getAvrLengthof3())
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
											if (Chunk_temp->getVarianceof3() < Chunk->getVarianceof3())
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

		if (Chunk->getWord1Length() > 0)//每次只输出chunk的第一个词的信息
		{
			CSearchDlg::showContents(Chunk->getWord1());
		}
	}

	//针对最后一个词进行处理
	CString lastword = inputData.Mid(htmlByte, (htmlLength - htmlByte));
	for (int m = 0;m < htmlLength - htmlByte;)
	{
		for (int n = htmlLength - htmlByte;n > 0;n--)
		{
			if (Hash::HashFind(lastword.Mid(m, n)))
			{
				CSearchDlg::showContents(lastword.Mid(m, n));
				m += lastword.Mid(m, n).GetLength();
				break;
			}
			else
			{
				if (n == 1)
				{
					CSearchDlg::showContents(lastword.Mid(m, n));
					m += lastword.Mid(m, n).GetLength();
					break;
				}
			}
		}
	}
}

//MFC的窗口初始化
BOOL CSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	pDlg = this;
	
	//设置字体
	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask |= CFM_SIZE;
	cf.yHeight = 500;
	cf.dwMask |= CFM_COLOR;
	cf.crTextColor = RGB(0, 0, 0);
	cf.dwMask |= CFM_FACE;
	wcscpy(cf.szFaceName, _T("黑体"));
	m_searchRichEdit.SetWordCharFormat(cf);
	m_searchRichEdit2.SetWordCharFormat(cf);

	CHARFORMAT cf3;
	ZeroMemory(&cf3, sizeof(CHARFORMAT));
	cf3.cbSize = sizeof(CHARFORMAT);
	cf3.dwMask |= CFM_SIZE;
	cf3.yHeight = 180;
	cf3.dwMask |= CFM_COLOR;
	cf3.crTextColor = RGB(153, 153, 153);
	cf3.dwMask |= CFM_FACE;
	wcscpy(cf3.szFaceName, _T("宋体"));

	//作者声明信息
	CString author = _T("@ 2015 YorkLynn\n鄂ICP证HUST1037号");
	m_tipRichEdit2.SetSelectionCharFormat(cf3);
	m_tipRichEdit2.ReplaceSel(author);

	HBITMAP   hBitmap;
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP));
	m_searchButton1.SetBitmap(hBitmap);
	m_searchButton2.SetBitmap(hBitmap);

	HBITMAP   hBitmapLogo1;
	hBitmapLogo1 = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP1));
	m_logoButton1.SetBitmap(hBitmapLogo1);

	HBITMAP   hBitmapLogo2;
	hBitmapLogo2 = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP2));
	m_logoButton2.SetBitmap(hBitmapLogo2);

	HBITMAP hBitmapLoading;
	hBitmapLoading = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3));
	m_buttonLoading.SetBitmap(hBitmapLoading);

	//所有显示页面的组件进行隐藏
	m_searchRichEdit2.ShowWindow(SW_HIDE);
	m_searchButton2.ShowWindow(SW_HIDE);
	m_searchRichEdit3.ShowWindow(SW_HIDE);
	m_logoButton2.ShowWindow(SW_HIDE);
	m_tipRichEdit1.ShowWindow(SW_HIDE);
	m_iniButton1.ShowWindow(SW_HIDE);
	m_iniButton2.ShowWindow(SW_HIDE);
	m_searchRichEdit.ShowWindow(SW_HIDE);
	m_searchButton1.ShowWindow(SW_HIDE);
	m_logoButton1.ShowWindow(SW_HIDE);
	m_tipRichEdit2.ShowWindow(SW_HIDE);
	
	CSearchDlg::initial();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSearchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//窗口背景色
		CPaintDC dc(this);
		CRect rect6;
		GetClientRect(&rect6);
		dc.FillSolidRect(rect6, RGB(255, 255, 255));

		//对搜索框的边框进行重绘制
		if (m_searchRichEdit.IsWindowVisible())
		{
			CRect rect1;
			m_searchRichEdit.GetWindowRect(rect1);
			ScreenToClient(rect1);
			rect1.bottom += 1;
			rect1.top -= 1;
			rect1.left -= 1;
			rect1.right += 1;
			dc.FillSolidRect(rect1, RGB(0, 122, 204));

		}
		if (m_searchRichEdit2.IsWindowVisible())
		{
			CRect rect2;
			m_searchRichEdit2.GetWindowRect(rect2);
			ScreenToClient(rect2);
			rect2.bottom += 1;
			rect2.top -= 1;
			rect2.left -= 1;
			rect2.right += 1;
			dc.FillSolidRect(rect2, RGB(0, 122, 204));
		}
		if (m_searchButton1.IsWindowVisible())
		{
			CRect rect3;
			m_searchButton1.GetWindowRect(rect3);
			ScreenToClient(rect3);
			rect3.bottom += 1;
			rect3.top -= 1;
			rect3.left -= 1;
			rect3.right += 1;
			dc.FillSolidRect(rect3, RGB(0, 122, 204));
		}
		if (m_searchButton2.IsWindowVisible())
		{
			CRect rect4;
			m_searchButton2.GetWindowRect(rect4);
			ScreenToClient(rect4);
			rect4.bottom += 1;
			rect4.top -= 1;
			rect4.left -= 1;
			rect4.right += 1;
			dc.FillSolidRect(rect4, RGB(0, 122, 204));
		}
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//************************************
// 方法名:	OnBnClickedSearch
// 全名:		CSearchDlg::OnBnClickedSearch
// 类型:		public 
// 返回值:	void
// 说明:		主页面搜索按钮点击处理函数
//************************************
void CSearchDlg::OnBnClickedSearch()
{
	CString SearchWord;
	
	if ((percentLoading1 != 1) || (percentLoading2 != 1))
	{
		MessageBox(_T("程序未初始化完毕"), _T("Tips"), MB_OK);
	}
	else
	{
		m_searchRichEdit.GetWindowTextW(SearchWord);

		m_tipRichEdit1.ShowWindow(SW_NORMAL);

		CSearchDlg::combineTable(SearchWord, 18);

		//主页面组件进行隐藏
		m_iniButton1.ShowWindow(SW_HIDE);
		m_iniButton2.ShowWindow(SW_HIDE);
		m_searchRichEdit.ShowWindow(SW_HIDE);
		m_searchButton1.ShowWindow(SW_HIDE);
		m_logoButton1.ShowWindow(SW_HIDE);
		m_tipRichEdit2.ShowWindow(SW_HIDE);

		CRect rect;
		m_searchRichEdit.GetWindowRect(rect);
		ScreenToClient(rect);
		rect.bottom += 1;
		rect.top -= 1;
		rect.left -= 1;
		rect.right += 1;
		InvalidateRect(rect);

		CRect rect2;
		m_searchButton1.GetWindowRect(rect2);
		ScreenToClient(rect2);
		rect2.bottom += 1;
		rect2.top -= 1;
		rect2.left -= 1;
		rect2.right += 1;
		InvalidateRect(rect2);

		m_searchRichEdit2.ShowWindow(SW_NORMAL);
		m_searchButton2.ShowWindow(SW_NORMAL);
		m_searchRichEdit3.ShowWindow(SW_NORMAL);
		m_logoButton2.ShowWindow(SW_NORMAL);

		CRect rect3;
		m_searchRichEdit2.GetWindowRect(rect3);
		ScreenToClient(rect3);
		rect3.bottom += 1;
		rect3.top -= 1;
		rect3.left -= 1;
		rect3.right += 1;
		InvalidateRect(rect3);

		CRect rect4;
		m_searchButton2.GetWindowRect(rect4);
		ScreenToClient(rect4);
		rect4.bottom += 1;
		rect4.top -= 1;
		rect4.left -= 1;
		rect4.right += 1;
		InvalidateRect(rect4);
	}
	SearchWord.ReleaseBuffer();
}

void CSearchDlg::initial()
{
	/*AfxBeginThread(MyProgressCtrl1, NULL);
	AfxBeginThread(MyProgressCtrl2, NULL);*/
	DictionaryLoading();
	WebContentLoading();
		m_buttonLoading.ShowWindow(SW_HIDE);
		m_searchRichEdit.ShowWindow(SW_NORMAL);
		m_searchButton1.ShowWindow(SW_NORMAL);
		m_logoButton1.ShowWindow(SW_NORMAL);
		m_tipRichEdit2.ShowWindow(SW_NORMAL);
}


//************************************
// 方法名:	OnBnClickedInitialButton1
// 全名:		CSearchDlg::OnBnClickedInitialButton1
// 类型:		public 
// 返回值:	void
// 说明:		词典加载按钮点击处理函数
//************************************
//void CSearchDlg::OnBnClickedInitialButton1()
//{
//	if (percentLoading1 == 0)
//	{
//		//启用词典加载线程
//		AfxBeginThread(MyProgressCtrl1, NULL);
//	}
//}


//************************************
// 方法名:	OnBnClickedInitialButton2
// 全名:		CSearchDlg::OnBnClickedInitialButton2
// 类型:		public 
// 返回值:	void
// 说明:		网页加载按钮点击处理函数
//************************************
//void CSearchDlg::OnBnClickedInitialButton2()
//{
//	if (percentLoading2 == 0)
//	{
//		//启用网页加载线程
//		AfxBeginThread(MyProgressCtrl2, NULL);
//	}
//}

//************************************
// 方法名:	OnBnClickedSearch2
// 全名:		CSearchDlg::OnBnClickedSearch2
// 类型:		public 
// 返回值:	void
// 说明:		显示页面搜索按钮点击处理函数
//************************************
void CSearchDlg::OnBnClickedSearch2()
{
	CString SearchWord;

	if ((percentLoading1 != 1) || (percentLoading2 != 1))
	{
		MessageBox(_T("程序未初始化完毕"), _T("Tips"), MB_OK);
	}
	else
	{
		m_searchRichEdit2.GetWindowTextW(SearchWord);

		m_tipRichEdit1.ShowWindow(SW_NORMAL);

		CSearchDlg::combineTable(SearchWord, 18);
	}
	SearchWord.ReleaseBuffer();
}


//************************************
// 方法名:	OnBnClickedLogoButton2
// 全名:		CSearchDlg::OnBnClickedLogoButton2
// 类型:		public 
// 返回值:	void
// 说明:		显示页面图标点击处理函数，点击返回主页面
//************************************
void CSearchDlg::OnBnClickedLogoButton2()
{
	//主页面组件的显示
	m_searchRichEdit.ShowWindow(SW_NORMAL);
	m_searchButton1.ShowWindow(SW_NORMAL);
	m_logoButton1.ShowWindow(SW_NORMAL);
	m_tipRichEdit2.ShowWindow(SW_NORMAL);

	CRect rect;
	m_searchRichEdit.GetWindowRect(rect);
	ScreenToClient(rect);
	rect.bottom += 1;
	rect.top -= 1;
	rect.left -= 1;
	rect.right += 1;
	InvalidateRect(rect);

	CRect rect2;
	m_searchButton1.GetWindowRect(rect2);
	ScreenToClient(rect2);
	rect2.bottom += 1;
	rect2.top -= 1;
	rect2.left -= 1;
	rect2.right += 1;
	InvalidateRect(rect2);

	//显示页面组件隐藏
	m_searchRichEdit2.ShowWindow(SW_HIDE);
	m_searchButton2.ShowWindow(SW_HIDE);
	m_searchRichEdit3.ShowWindow(SW_HIDE);
	m_logoButton2.ShowWindow(SW_HIDE);
	m_tipRichEdit1.ShowWindow(SW_HIDE);

	CRect rect3;
	m_searchRichEdit2.GetWindowRect(rect3);
	ScreenToClient(rect3);
	rect3.bottom += 1;
	rect3.top -= 1;
	rect3.left -= 1;
	rect3.right += 1;
	InvalidateRect(rect3);

	CRect rect4;
	m_searchButton2.GetWindowRect(rect4);
	ScreenToClient(rect4);
	rect4.bottom += 1;
	rect4.top -= 1;
	rect4.left -= 1;
	rect4.right += 1;
	InvalidateRect(rect4);
}


void CSearchDlg::OnBnClickedLogoButton1()
{
	
}


//************************************
// 方法名:	OnEnLinkRichedit23
// 全名:		CSearchDlg::OnEnLinkRichedit23
// 类型:		public 
// 返回值:	void
// 参数:		NMHDR * pNMHDR
// 参数:		LRESULT * pResult
// 说明:		显示界面超链接点击处理函数
//************************************
void CSearchDlg::OnEnLinkRichedit23(NMHDR *pNMHDR, LRESULT *pResult)
{
	ENLINK *pEnLink = reinterpret_cast<ENLINK *>(pNMHDR);
	
	if (pEnLink->msg == WM_LBUTTONUP)
	{
		m_searchRichEdit3.SetSel(pEnLink->chrg);
		CString SelText = m_searchRichEdit3.GetSelText();
		OutputDebugString(SelText);
		int webID;
		swscanf(SelText, L"%d", &webID);
		CString num;
		num.Format(_T("%d"), webID);
		CString webName = webName_base + num + _T(".html");
		ShellExecute(NULL, L"open", webName, NULL, NULL, SW_SHOWNORMAL);
		
	}
	*pResult = 0;
}
