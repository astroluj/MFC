#pragma once


// CRankNameDlg ��ȭ �����Դϴ�.

class CRankNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRankNameDlg)

public:
	CRankNameDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRankNameDlg();
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RANKNAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString name;
	virtual BOOL OnInitDialog();
};
