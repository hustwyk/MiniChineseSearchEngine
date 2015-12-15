/*********************************************************************************
*Copyright(C), 2015, @York Lynn
*FileName:	hash.h
*Author:	��ӳ�j
*Version:	V1.0
*Date:	2015.10.26
*Description:	�����ں͸�ģ��֮��ĵ��á�
*History:
1.Date:	2015.10.26
Author:	��ӳ�j
Modification:	��Ҫ���ܵĹ���������
**********************************************************************************/


#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSearchDlg �Ի���
class CSearchDlg : public CDialogEx
{
// ����
public:
	CSearchDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEARCH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void initial();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedInitialButton1();
	afx_msg void OnBnClickedInitialButton2();
	CRichEditCtrl m_searchRichEdit;
	CRichEditCtrl m_searchRichEdit2;
	CButton m_searchButton1;
	CButton m_searchButton2;
	CRichEditCtrl m_searchRichEdit3;
	CButton m_iniButton1;
	CButton m_iniButton2;
	afx_msg void OnBnClickedSearch2();
	CButton m_logoButton1;
	CButton m_logoButton2;
	CButton m_buttonLoading;
	afx_msg void OnBnClickedLogoButton2();
	afx_msg void OnBnClickedLogoButton1();
	CRichEditCtrl m_tipRichEdit1;
	CRichEditCtrl m_tipRichEdit2;

	void combineTable(CString inputData, int maxDicLength);
	void showContents(CString SearchWord);
	afx_msg void OnEnLinkRichedit23(NMHDR *pNMHDR, LRESULT *pResult);
	
};

struct webNode
{
	int webID = 0;
	CString *Title = NULL;
	CString *About = NULL;
	int freq = 0;
	struct webNode * nextnode = NULL;
};


struct HashNode
{
	CString word = _T("");
	int occupancy_Flag = 0;
	struct webNode * webNode = NULL;
};