
#pragma once
#include "afxwin.h"
#include "atltypes.h"


// CLevelDlg ��ȭ �����Դϴ�.

class CLevelDlg : public CDialog
{
	DECLARE_DYNAMIC(CLevelDlg)

public:
	CLevelDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLevelDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_LEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int nRow;
	int nCol;
	int time;

	afx_msg void OnBnClickedButtonEasy();
	afx_msg void OnBnClickedButtonNormal();
	afx_msg void OnBnClickedButtonHard();
	afx_msg void OnCbnSelchangeComboFont();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonColor();
	virtual BOOL OnInitDialog();

	CString strLev;	// ��ŷ�� ������ txt���ϸ�
	CString strRank;	// ��θ� ������ ���ϸ�
	CString ld_font;

	CComboBox ld_cFont;
	CRect ld_rect;
	COLORREF ld_rectColor;
	virtual void OnCancel();
};
