#pragma once
#include "afxcmn.h"
#include "atltypes.h"


// CTimeDlg ��ȭ �����Դϴ�.

class CTimeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTimeDlg)

public:
	CTimeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTimeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ���α׷��� ����
	CProgressCtrl timeCtrl;
	virtual BOOL OnInitDialog();
	COLORREF color;	// view�� ������ ���� ����
	CRect rectView;	// View�� ũ�⸦ ���� ����
	afx_msg void OnClose();
};
