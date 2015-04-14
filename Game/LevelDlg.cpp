// LevelDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "LevelDlg.h"
#include "GameDoc.h"
#include "GameView.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CLevelDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CLevelDlg, CDialog)

CLevelDlg::CLevelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLevelDlg::IDD, pParent)
{
	nRow = nCol = time = 0;
	strLev = _T("�ʱ�");
	strRank = ld_font = _T("");
}

CLevelDlg::~CLevelDlg()
{
}

void CLevelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_FONT, ld_font);
	DDX_Control(pDX, IDC_COMBO_FONT, ld_cFont);
}


BEGIN_MESSAGE_MAP(CLevelDlg, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_EASY, &CLevelDlg::OnBnClickedButtonEasy)
	ON_BN_CLICKED(IDC_BUTTON_NORMAL, &CLevelDlg::OnBnClickedButtonNormal)
	ON_BN_CLICKED(IDC_BUTTON_HARD, &CLevelDlg::OnBnClickedButtonHard)
	ON_CBN_SELCHANGE(IDC_COMBO_FONT, &CLevelDlg::OnCbnSelchangeComboFont)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CLevelDlg::OnBnClickedButtonColor)
END_MESSAGE_MAP()


// CLevelDlg �޽��� ó�����Դϴ�.

// �ʱ� ����
void CLevelDlg::OnBnClickedButtonEasy()
{
	nRow =3 ; nCol =4 ; time = 19;
	strLev =_T ("�ʱ�") ;
	strRank =_T ("C:\\image\\EasyRanking.txt") ;
	CDialog ::OnOK () ;
}

// �߱� ����
void CLevelDlg::OnBnClickedButtonNormal()
{
	nRow =4 ; nCol =5 ; time = 49 ;
	strLev =_T ("�߱�") ;
	strRank =_T ("C:\\image\\NormalRanking.txt") ;
	CDialog ::OnOK () ;
}

// ��� ����
void CLevelDlg::OnBnClickedButtonHard()
{
	nRow =5 ; nCol =6 ; time = 99 ; 
	strLev =_T ("���") ;
	strRank =_T ("C:\\image\\HardRanking.txt") ;
	CDialog ::OnOK () ;
}

// �۲� �޺��ڽ� 
void CLevelDlg::OnCbnSelchangeComboFont()
{
	int index = ld_cFont.GetCurSel();
	ld_cFont.GetLBText(index, ld_font);
}

// �ʱⰪ
BOOL CLevelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_COLOR);
	pStatic->GetWindowRect(&ld_rect);
	ScreenToClient(&ld_rect);
	
	// ����Ʈ�ڽ��� �ʱⰪ ����
	ld_cFont.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

// ������Ʈ�ѿ� ��ĥ
void CLevelDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CBrush newBrush, *pOldBrush;
	newBrush.CreateSolidBrush(ld_rectColor);
	pOldBrush = dc.SelectObject(&newBrush);
	dc.Rectangle(&ld_rect);
	dc.SelectObject(pOldBrush);
	newBrush.DeleteObject();
}

// ���� Ŭ���̺�Ʈ
void CLevelDlg::OnBnClickedButtonColor()
{
	CColorDialog dlg;
	// ������ ��ȭ���� ����
	dlg.DoModal();
	ld_rectColor = dlg.GetColor();
	InvalidateRect(&ld_rect);
}


void CLevelDlg::OnCancel()
{
	CDialog::OnCancel();
}
