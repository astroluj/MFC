#pragma once
#include "afxwin.h"
#include "afx.h"
#include "afxcmn.h"


// CRankDlg ��ȭ �����Դϴ�.

class CRankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDlg)

public:
	CRankDlg(CString, CString, CString, CString, UINT, CString, CString, UINT, CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRankDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:	
	// ���̾�α� ó��
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	
	// ������ ����/�ҷ�����
	void AutoSave(void);
	void AutoLoad(void);

	CString member;	// �̸�
	CString nMin;	// ��
	CString nSec;	// ��
	CString nCsec;	// 1/100��
	UINT nCnt;		// Ŭ�� ��
	UINT nRank;	// ��ũ
	
	CListCtrl rankList;	// ����Ʈ ��Ʈ�� ����
	CString strLev;	// ���̵� ����
	CString rankName;	// ���̵����� ����� ��ũ.txt�� �̸�
	UINT nPoint;	// ���ھ� ����
	
	/************ ��ŷ ó�� ************/
	void SortRank(CString rankName);
	void SwapRank(int val1, int val2);
	int CompareRank(int * val1, int * val2, int, int, int);
	void NaturalMergeSort(int top, int bottom);	// ������ �ٲ��� �ٲ� ������� �� ����
	void QuickSort(int first, int last);	// �� ��Ʈ
	void SwapItem(int val1, int val2);	// ����Ʈ ��Ʈ���� �������� ��ȯ
	/********************************/

	/********** Ŭ�� �̺�Ʈ **********/
	afx_msg void OnBnClickedButtonEasy();
	afx_msg void OnBnClickedButtonNormal();
	afx_msg void OnBnClickedButtonHard();
	afx_msg void OnBnClickedButtonDelall();
	/*****************************/

	// �귯�� �ð��� ��Ÿ���� ���� �Լ�
	void TimePoint(void);
};
