// TimeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "TimeDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
// CTimeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTimeDlg, CDialogEx)

CTimeDlg::CTimeDlg (CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimeDlg::IDD, pParent)
{

}

CTimeDlg::~CTimeDlg()
{
}

void CTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_TIME, timeCtrl);
}


BEGIN_MESSAGE_MAP(CTimeDlg, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CTimeDlg �޽��� ó�����Դϴ�.


BOOL CTimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CRect rectTime ;
	GetClientRect (&rectTime) ;		// �ڽ��� ũ�⸦ �޴´�.

	// View�� ��ġ�� ���� ������� ��ġ�� ���´�.
	SetWindowPos (NULL, 
		rectView.Width () -rectTime.Width (), 
		(rectView.Height () -rectTime.Height ()) /2,
		rectView.Width (), 
		(rectView.Height () -rectTime.Height ()) /2 +rectTime.Height (), 
		SWP_NOSIZE) ;
	
	// �� ó��
	timeCtrl.SetBarColor (0x00FFFFFF & ~color) ;	// ���� ��
	//timeCtrl.SetBkColor (color) ;		// ���� ����
	SetBackgroundColor (color) ;		// ���̾˷α� ����
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTimeDlg::OnClose()
{
	DestroyWindow () ;
	CDialogEx::OnClose();
}
