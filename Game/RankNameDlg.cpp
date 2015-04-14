// RankName.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "RankNameDlg.h"
#include "afxdialogex.h"


// CRankNameDlgDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRankNameDlg, CDialogEx)

CRankNameDlg::CRankNameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRankNameDlg::IDD, pParent)
	, name(_T(""))
{

}

CRankNameDlg::~CRankNameDlg()
{
}

void CRankNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, name);
}


BEGIN_MESSAGE_MAP(CRankNameDlg, CDialogEx)
END_MESSAGE_MAP()


BOOL CRankNameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem (IDC_NAME) ->SetFocus () ;	// �̸� �Է�â�� ��Ŀ��
	return TRUE;  // return TRUE unless you set the focus to a control
}
