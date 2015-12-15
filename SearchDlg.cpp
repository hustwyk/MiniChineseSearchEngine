
// SearchDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "string"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//����ȫ�ֱ���
static int dicLength = 273888;
static int webLength = 189;
static int hashLength = 300000;
static int maxWordLength = 18;
static double percentLoading1 = 0;
static int percent1 = 0;
static double percentLoading2 = 0;
CString dicName = _T("SearchDic.txt");
CString webName_base = _T("html\\");
//ȫ��hash���ʼ��
HashNode HashTable[300000];
//�������ָ��
CSearchDlg* pDlg;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

//���ڴ���
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSearchDlg �Ի���
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
// ������:	GetDicLength
// ȫ��:		GetDicLength
// ����:		public 
// ����ֵ:	int
// ˵��:		�����ֵ������
//************************************
int GetDicLength()
{
	CFile Dic;
	int maxLength = 0;
	CString word;
	Dic.Open(dicName, CFile::modeRead);
	
	//��unicode�����ǰ���������ֽ�ȥ��
	wchar_t ch;
	Dic.Read(&ch, 2);

	for (int process = 0;process < dicLength;process++)
	{
		word.Empty();
		while (1)
		{
			Dic.Read(&ch, 2);
			//�����س���ʱ��˵���Ѿ���ȡһ����
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
// ������:	MyProgressCtrl1
// ȫ��:		MyProgressCtrl1
// ����:		public 
// ����ֵ:	UINT
// ����:		LPVOID p   �߳�ָ�����
// ˵��:		���شʵ��߳�
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

	//��unicode�����ǰ���������ֽ�ȥ��
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
		
		//���ɹ�ϣ��
		UINT hashValue = Hash::SDBMHash(word);
		UINT hashOrder = hashValue % hashLength;
		int ij;
		//ɢ�е�ַ������hash
		for ( ij = 0;HashTable[(hashOrder + ij) % hashLength].occupancy_Flag != 0;ij++);
		HashTable[(hashOrder + ij) % hashLength].occupancy_Flag = 1;
		HashTable[(hashOrder + ij) % hashLength].word = word;
		//percent1���ڱ�ʾ�Ƿ����
		percent1 = process;
		percentLoading1 = process / (dicLength - 1);
	}
	MessageBox(0,_T("�ʿ��ʼ�����"), _T("Initial"), MB_OK);
	CString num;
	num.Format(_T("%f"),percentLoading1);
	OutputDebugString(num);
	Dic.Close();
	word.ReleaseBuffer();

	/*return 0;*/
}

//************************************
// ������:	MyProgressCtrl2
// ȫ��:		MyProgressCtrl2
// ����:		public 
// ����ֵ:	UINT
// ����:		LPVOID p   �߳�ָ�����
// ˵��:		������ҳ�߳�
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
			//����ҳ���ݽ��н������������еĹؼ���Ϣ
			CString trans = html::Extract(str);
			CString title = html::Title(str);
			CString transWithSymbol = html::ExtractwithSymbol(str);
			//�Խ��������ݽ��зִʺ͹��쵹�ű�
			segment::segmentString(trans, dicName, piece, maxWordLength, title, transWithSymbol);
			
			Web.Close();
			free(ch2);
			ch2 = NULL;
			str.ReleaseBuffer();
		}
		percentLoading2 = piece / (webNum - 1);
	}
	MessageBox(0, _T("��ҳ��ʼ�����"), _T("Initial"), MB_OK);
	/*return 0;*/
}


//************************************
// ������:	HashFind
// ȫ��:		Hash::HashFind
// ����:		public static
// ����ֵ:	BOOL
// ����:		CString findWord   ����Ĺؼ�����
// ˵��:		��ϣ���ң������ж�����Ĵ��Ƿ��ڴʵ���
//************************************
BOOL Hash::HashFind(CString findWord)
{
	UINT hash = Hash::SDBMHash(findWord);
	UINT hashTemp = hash % hashLength;
	//ɢ�е�ַ�����в���
	for (int i = 0;HashTable[(hashTemp + i) % hashLength].occupancy_Flag != 0;i++)
	{
		if (HashTable[(hashTemp + i) % hashLength].word == findWord)
			return TRUE;
	}
	return FALSE;
}


//************************************
// ������:	HashFind2
// ȫ��:		Hash::HashFind2
// ����:		public static 
// ����ֵ:	UINT
// ����:		CString findWord   ����Ĺؼ�����
// ˵��:		��������ʵĹ�ϣ��ַ�����ôʲ����ڣ��򷵻�-1
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
// ������:	insertTable
// ȫ��:		segment::insertTable
// ����:		public static 
// ����ֵ:	void
// ����:		CString insertData   ������Ĵ���
// ����:		int webID   ����ҳ�ĵ���ID
// ����:		CString title    ����ҳ�ĵ��еı���
// ����:		CString about    ��Ըùؼ�������ҳ�еĶ���
// ˵��:		���쵹�ű������뵽�ʵ�������
//************************************
void segment::insertTable(CString insertData, int webID, CString title, CString about)
{
	if (Hash::HashFind(insertData))
	{
		UINT hashTemp = Hash::HashFind2(insertData);

		if (hashTemp != -1) //�жϴʵ��и�λ����û�б�ռ��
		{
			//�����λ�ñ�ռ��
			webNode** nodeTemp = &(HashTable[hashTemp].webNode);
			//�Ҹô��ڵ�λ��
			for (;*nodeTemp != NULL;nodeTemp = &((*nodeTemp)->nextnode))
			{
				if ((*nodeTemp)->webID == webID)
					break;
			}
			//���û�ҵ���˵���ôʵĽڵ���δ����
			if (*nodeTemp == NULL)
			{
				*nodeTemp = (webNode*)malloc(sizeof(webNode));
				(*nodeTemp)->freq = 0;
				(*nodeTemp)->webID = 0;
				(*nodeTemp)->Title = new CString();
				(*nodeTemp)->About = new CString();
				(*nodeTemp)->nextnode = NULL;
			}
			//��ID��Title��About���ݽ����жϺ͸���
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
// ������:	showContents
// ȫ��:		CSearchDlg::showContents
// ����:		public 
// ����ֵ:	void
// ����:		CString SearchWord   �����Ĺؼ�����
// ˵��:		��ʾҳ�����ʾ������ͬ���ֵĸ�ʽ�Լ�����ĸ�ʽ
//************************************
void CSearchDlg::showContents(CString SearchWord)
{
	//��ͬ��ʽ��������Ϣ
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
	wcscpy(cf1.szFaceName, _T("����"));

	CHARFORMAT cf2;
	ZeroMemory(&cf2, sizeof(CHARFORMAT));
	cf2.cbSize = sizeof(CHARFORMAT);
	cf2.dwMask |= CFM_SIZE;
	cf2.yHeight = 200;
	cf2.dwMask |= CFM_COLOR;
	cf2.crTextColor = RGB(51, 51, 51);
	cf2.dwMask |= CFM_FACE;
	wcscpy(cf2.szFaceName, _T("����"));

	CHARFORMAT cf3;
	ZeroMemory(&cf3, sizeof(CHARFORMAT));
	cf3.cbSize = sizeof(CHARFORMAT);
	cf3.dwMask |= CFM_SIZE;
	cf3.yHeight = 180;
	cf3.dwMask |= CFM_COLOR;
	cf3.crTextColor = RGB(153, 153, 153);
	cf3.dwMask |= CFM_FACE;
	wcscpy(cf3.szFaceName, _T("����"));

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
	wcscpy(cf4.szFaceName, _T("����"));

	//�Դ������ű���Ϣ�������
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
	//��ʾ������ʾ
	m_tipRichEdit1.SetWindowTextW(_T(""));

	CString tip1 = _T("CoogleΪ���ҵ���ؽ��Լ");
	CString tip2 = _T("��");
	CString tipnum;
	tipnum.Format(_T("%d"), j);
	CString Tip = tip1 + tipnum + tip2;

	m_tipRichEdit1.SetSelectionCharFormat(cf3);
	m_tipRichEdit1.ReplaceSel(Tip);
	
}


//************************************
// ������:	combineTable
// ȫ��:		CSearchDlg::combineTable
// ����:		public 
// ����ֵ:	void
// ����:		CString inputData    ����Ĺؼ�����
// ����:		int maxDicLength    �ֵ��д����������
// ˵��:		��������зִʲ����в����ٶԵ��ű���кϲ������غϲ���ĵ��ű�
//************************************
void CSearchDlg::combineTable(CString inputData, int maxDicLength)
{
	//������Ĺؼ��ֽ��зִ�
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

		if (Chunk->getWord1Length() > 0)//ÿ��ֻ���chunk�ĵ�һ���ʵ���Ϣ
		{
			CSearchDlg::showContents(Chunk->getWord1());
		}
	}

	//������һ���ʽ��д���
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

//MFC�Ĵ��ڳ�ʼ��
BOOL CSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	pDlg = this;
	
	//��������
	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask |= CFM_SIZE;
	cf.yHeight = 500;
	cf.dwMask |= CFM_COLOR;
	cf.crTextColor = RGB(0, 0, 0);
	cf.dwMask |= CFM_FACE;
	wcscpy(cf.szFaceName, _T("����"));
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
	wcscpy(cf3.szFaceName, _T("����"));

	//����������Ϣ
	CString author = _T("@ 2015 YorkLynn\n��ICP֤HUST1037��");
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

	//������ʾҳ��������������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSearchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//���ڱ���ɫ
		CPaintDC dc(this);
		CRect rect6;
		GetClientRect(&rect6);
		dc.FillSolidRect(rect6, RGB(255, 255, 255));

		//��������ı߿�����ػ���
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSearchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//************************************
// ������:	OnBnClickedSearch
// ȫ��:		CSearchDlg::OnBnClickedSearch
// ����:		public 
// ����ֵ:	void
// ˵��:		��ҳ��������ť���������
//************************************
void CSearchDlg::OnBnClickedSearch()
{
	CString SearchWord;
	
	if ((percentLoading1 != 1) || (percentLoading2 != 1))
	{
		MessageBox(_T("����δ��ʼ�����"), _T("Tips"), MB_OK);
	}
	else
	{
		m_searchRichEdit.GetWindowTextW(SearchWord);

		m_tipRichEdit1.ShowWindow(SW_NORMAL);

		CSearchDlg::combineTable(SearchWord, 18);

		//��ҳ�������������
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
// ������:	OnBnClickedInitialButton1
// ȫ��:		CSearchDlg::OnBnClickedInitialButton1
// ����:		public 
// ����ֵ:	void
// ˵��:		�ʵ���ذ�ť���������
//************************************
//void CSearchDlg::OnBnClickedInitialButton1()
//{
//	if (percentLoading1 == 0)
//	{
//		//���ôʵ�����߳�
//		AfxBeginThread(MyProgressCtrl1, NULL);
//	}
//}


//************************************
// ������:	OnBnClickedInitialButton2
// ȫ��:		CSearchDlg::OnBnClickedInitialButton2
// ����:		public 
// ����ֵ:	void
// ˵��:		��ҳ���ذ�ť���������
//************************************
//void CSearchDlg::OnBnClickedInitialButton2()
//{
//	if (percentLoading2 == 0)
//	{
//		//������ҳ�����߳�
//		AfxBeginThread(MyProgressCtrl2, NULL);
//	}
//}

//************************************
// ������:	OnBnClickedSearch2
// ȫ��:		CSearchDlg::OnBnClickedSearch2
// ����:		public 
// ����ֵ:	void
// ˵��:		��ʾҳ��������ť���������
//************************************
void CSearchDlg::OnBnClickedSearch2()
{
	CString SearchWord;

	if ((percentLoading1 != 1) || (percentLoading2 != 1))
	{
		MessageBox(_T("����δ��ʼ�����"), _T("Tips"), MB_OK);
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
// ������:	OnBnClickedLogoButton2
// ȫ��:		CSearchDlg::OnBnClickedLogoButton2
// ����:		public 
// ����ֵ:	void
// ˵��:		��ʾҳ��ͼ���������������������ҳ��
//************************************
void CSearchDlg::OnBnClickedLogoButton2()
{
	//��ҳ���������ʾ
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

	//��ʾҳ���������
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
// ������:	OnEnLinkRichedit23
// ȫ��:		CSearchDlg::OnEnLinkRichedit23
// ����:		public 
// ����ֵ:	void
// ����:		NMHDR * pNMHDR
// ����:		LRESULT * pResult
// ˵��:		��ʾ���泬���ӵ��������
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
