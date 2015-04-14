
// GameView.cpp : CGameView Ŭ������ ����
//
#pragma comment(lib, "winmm.lib")
#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Game.h"
#endif

#include "GameDoc.h"
#include "GameView.h"
#include "LevelDlg.h"
#include "RankNameDlg.h"
#include "RankDlg.h"
#include "TimeDlg.h"

#include <MMSystem.h>	// ���� ����� ���� ���
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameView

IMPLEMENT_DYNCREATE(CGameView, CView)

BEGIN_MESSAGE_MAP(CGameView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGameView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_WHITE, &CGameView::OnWhite)
	ON_COMMAND(ID_BLACK, &CGameView::OnBlack)
	ON_COMMAND(ID_USER, &CGameView::OnUser)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CGameView ����/�Ҹ�

CGameView::CGameView()
{
	/* bool */	gv_TF =gv_scoreTF 
	/* UINT */	=gv_cnt =gv_point =gv_timeUpper 
	/* int */		=gv_min =gv_levCnt = gv_tempMin =gv_tempSec =gv_nMatchCount 
	/* DWORD */	=gv_timeDV =gv_bgDV =gv_failDV =gv_successDV
					=FALSE;
	isInit = TRUE;
	gv_sec = 19;
	gv_csec = 100;
	gv_lev = _T("�ʱ�");
	gv_rank = _T("C:\\image\\EasyRanking.txt");
	gv_font = _T("HY����B");
	gv_minStr =gv_secStr =gv_csecStr =_T ("") ;
	CLevelDlg pLevel ;
	gv_bgColor =pLevel.ld_rectColor ;		// ���ȭ�� �ʱ�ȭ
}

CGameView::~CGameView()
{
}


BOOL CGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	return CView::PreCreateWindow(cs);
}

// CGameView �׸���

void CGameView::OnDraw(CDC* pDC)
{
	CGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//**** ���� *************
	CBrush brush (gv_bgColor);
	CBrush *pOldB =pDC ->SelectObject (&brush) ;
	CRect rect;
	GetClientRect(&rect);
	pDC->Rectangle(rect);
	pDC->SelectObject(pOldB); 
	//***********************

	// �������� ������ �����Լ� ȣ��
	if(pDoc->gd_bRandom) pDoc->OnRandom();

	int nCount = 0;
go:
	CDC memDC;
	CBitmap* pOldBmp;

	if(isInit){
		// Font ���� Part
		CFont myFont, *pOldFont ;
		myFont.CreateFont (40, 0, 0, 0, FW_BOLD, true, false, false, 
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, DEFAULT_PITCH, gv_font) ;
		pOldFont =pDC->SelectObject (&myFont) ;

		// Text ���� Part
		CString str =_T ("HINT") ;
		pDC->SetBkColor (gv_bgColor) ;		// ������ ����� ������ ���� 
		pDC->SetTextColor (0x00FFFFFF & ~gv_bgColor) ;		// ���� ���� ����ȭ���� �ݴ� ������
		pDC->SetTextAlign (TA_CENTER) ;		// ��� ���
		pDC->TextOutW (rect.Width () /2, rect.top +20, str) ;

		// �����ִ� ��Ʈ
		pDoc->gd_nBmpFirstID = pDoc->gd_nBmpSecondID = 0 ;		// ��Ʈ���� �̸��� �ʱ�ȭ
		pDoc->gd_bMouse = FALSE;

		for(int i=0;i<pDoc->gd_nRow;i++)
			for(int j=0;j<pDoc->gd_nCol;j++)
				pDoc->gd_bShow[i][j] = TRUE;
	}
	memDC.CreateCompatibleDC(pDC);

	for(int n=0;n<pDoc->gd_nRow;n++){
		for(int m=0;m<pDoc->gd_nCol;m++){
			// �̹��� ��� 
			int imgStartPtrX = rect.right/(pDoc->gd_nCol+2);
			int imgStartPtrY = rect.bottom/(pDoc->gd_nRow+2);
			/* �̹��� ��� */
			if(pDoc->gd_bShow[n][m]){
				pDoc->gd_bmp[n][m].LoadBitmapW(IDB_BITMAP1+pDoc->gd_nRnd[nCount]);
				pOldBmp = memDC.SelectObject(&pDoc->gd_bmp[n][m]); 
				pDC->StretchBlt(
					imgStartPtrX*(m+1), imgStartPtrY*(n+1),
					imgStartPtrX, imgStartPtrY, 
					&memDC, 0, 0, 
					pDoc->gd_bmCell.cx, pDoc->gd_bmCell.cy, SRCCOPY);
				pDoc->gd_bmp[n][m].DeleteObject();
			}
			/* Ŀ�� ��� */
			if(!pDoc->gd_bShow[n][m]){
				CBitmap bmp;
				bmp.LoadBitmapW(IDB_BITMAP1);	// Ŀ�� ���
				pOldBmp = memDC.SelectObject(&bmp);
				 
				pDC->StretchBlt(
					imgStartPtrX*(m+1), imgStartPtrY*(n+1),
					imgStartPtrX, imgStartPtrY, 
					&memDC, 0, 0, 
					pDoc->gd_bmCell.cx, pDoc->gd_bmCell.cy, SRCCOPY);
				bmp.DeleteObject();
			}
			nCount++;
		}
	}
	memDC.SelectObject(pOldBmp);
	pDoc->ResizeWindow();

	// ������ ���۵� ���������� ó��
	if(isInit){
		isInit = FALSE;

		for(int i=0;i<pDoc->gd_nRow;i++)
			for(int j=0;j<pDoc->gd_nCol;j++)
				pDoc->gd_bShow[i][j] = FALSE;

		// ���� ����̽� ����
		gv_timeDV =OpenSounds (_T ("C:\\image\\����Ҹ�.mp3")) ;	
		gv_successDV =OpenSounds (_T ("C:\\image\\�ڼ���ä.mp3")) ;
		gv_failDV =OpenSounds (_T ("C:\\image\\�������Ŀ_����.mp3")) ;	
		gv_bgDV =OpenSounds (_T ("C:\\image\\Terranigma-Light_Side_Field.mp3")) ;

		// Ÿ�ӹ� ���� ����
		gv_timeUpper = gv_min*60 + gv_sec;
		pTimeDlg ->timeCtrl.SetRange32 (0, gv_timeUpper) ;	// ����
		pTimeDlg ->timeCtrl.SetPos (gv_min*60 +gv_sec) ;		// �ʱ���ġ

		PlaySound (L"C:\\image\\��ſ�ð��ǽʽÿ�.wav", NULL, SND_SYNC) ;
		
		// Hint time
		int time;
		if(gv_lev == _T("�ʱ�")) time = 600;
		else if(gv_lev == _T("�߱�")) time = 1000;
		else time = 1800;

		pTimeDlg ->ShowWindow (SW_SHOW) ;	// ��޸��� ����
		Sleep(time);
		pDC ->TextOutW (rect.Width () /2, rect.top +20, _T ("             ")) ;
		PlaySounds (gv_bgDV) ;	// ���� ������ �����
		SetTimer (true, 1, NULL) ;
		goto go;
	}
}

// CGameView �μ�
void CGameView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}
BOOL CGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}
void CGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}
void CGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}
void CGameView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}
void CGameView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CGameView ����
#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CView::AssertValid();
}
void CGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CGameDoc* CGameView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameDoc)));
	return (CGameDoc*)m_pDocument;
}
#endif //_DEBUG

// CGameView �޽��� ó����
// ���ʹ�ư Ŭ����
void CGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CGameDoc* pDoc = GetDocument();
	CRect rect;
	GetClientRect(&rect);

	// ���� ���콺�� ���� �ε���
	pDoc->gd_nRowIndex = point.y / (rect.bottom/(pDoc->gd_nRow+2))-1;
	pDoc->gd_nColIndex = point.x / (rect.right/(pDoc->gd_nCol+2))-1;

	// ������ �ι�Ŭ��, �ι��̻� Ŭ��, ������ Ŭ��
	if(pDoc->gd_bShow[pDoc->gd_nRowIndex][pDoc->gd_nColIndex]
		|| pDoc->gd_nBmpSecondID
		|| pDoc->gd_nRowIndex > pDoc->gd_nRow - 1
		|| pDoc->gd_nColIndex > pDoc->gd_nCol - 1
		|| pDoc->gd_nRowIndex < 0 
		|| pDoc->gd_nColIndex < 0)
		return ;

	// ���콺�� ������ �ִ� �ε��� ���� �׸��� ������
	gv_TF =!gv_TF ;		// Ŭ���� �ι� �� �� ���� Ŭ���� ������Ű�� ����

	PlaySound (L"C:\\image\\ī�޶�.wav", NULL, SND_ASYNC) ;	// Ŭ�� ���� �� ���� �ѱ� �Ҹ�
	pDoc->gd_bShow[pDoc->gd_nRowIndex][pDoc->gd_nColIndex] = TRUE;

	SetRect(&rect, pDoc->gd_nRowIndex*(pDoc->gd_bmCell.cx + 1),
		pDoc->gd_nColIndex*(pDoc->gd_bmCell.cy + 1),
		pDoc->gd_nRowIndex*(pDoc->gd_bmCell.cx + 2),
		pDoc->gd_nColIndex*(pDoc->gd_bmCell.cy + 2));
	InvalidateRect(rect);

	// ���콺�� Ŭ���� ���� �ε��� �� �׸� ���̵� ����
	// ù��° Ŭ��
	if(pDoc->gd_nBmpFirstID==0){
		pDoc->gd_nBmpFirstID = pDoc->gd_nBmpID[pDoc->gd_nRowIndex][pDoc->gd_nColIndex];
		gv_nRowTempIndex = pDoc->gd_nRowIndex;
		gv_nColTempIndex = pDoc->gd_nColIndex;
		pDoc->gd_bMouse = TRUE;
	}
	// �ι�° Ŭ��
	else{
		pDoc->gd_nBmpSecondID = pDoc->gd_nBmpID[pDoc->gd_nRowIndex][pDoc->gd_nColIndex];
		pDoc->gd_bMouse = FALSE;
	}

	// Ŭ�� ī��Ʈ ���
	if (gv_TF) gv_cnt++ ;
	
	// �����׸����� �Ǵ�
	OnMatching();
	CView::OnLButtonDown(nFlags, point);
}

// ī�� ���ߴ� ����
void CGameView::OnMatching(void)
{
	CGameDoc* pDoc = GetDocument();

	// �׸��� ������
	if(pDoc->gd_nBmpFirstID == pDoc->gd_nBmpSecondID && pDoc->gd_bMouse == FALSE){
		PlaySound (L"C:\\image\\Ű����.wav", NULL, SND_ASYNC) ;		// �׸��� �¾��� �� ���� �Ҹ�
		
		// Ŭ�� �̺�Ʈ �ʱ�ȭ
		pDoc->gd_bShow[gv_nRowTempIndex][gv_nColTempIndex] 
		= pDoc->gd_bShow[pDoc->gd_nRowIndex][pDoc->gd_nColIndex] = TRUE;
		pDoc->gd_nBmpFirstID = pDoc->gd_nBmpSecondID 
		= gv_nRowTempIndex = gv_nColTempIndex = 0;

		gv_nMatchCount ++;
		gv_point+= 10 ;		// �׸��� ���߾��� �� 10�� �߰�
	}
	else if(pDoc->gd_nBmpFirstID != pDoc->gd_nBmpSecondID && pDoc->gd_bMouse == FALSE){
		// �ٸ� �׸��̾ �����ֱ���
		CDC* pDC = GetDC();
		CDC memDC;
		CBitmap bmp;

		memDC.CreateCompatibleDC(pDC);
		bmp.LoadBitmapW(IDB_BITMAP1 + pDoc->gd_nBmpSecondID);

		CRect rect;
		GetClientRect(&rect);

		CBitmap* pOldBmp = memDC.SelectObject(&bmp);
		pDC->StretchBlt(rect.right/(pDoc->gd_nCol+2)*(pDoc->gd_nColIndex + 1),
			rect.bottom/(pDoc->gd_nRow+2)*(pDoc->gd_nRowIndex + 1),
			rect.right/(pDoc->gd_nCol+2), rect.bottom/(pDoc->gd_nRow+2), 
			&memDC, 0, 0, pDoc->gd_bmCell.cx, pDoc->gd_bmCell.cy, SRCCOPY);

		bmp.DeleteObject();
		memDC.SelectObject(pOldBmp);
		// ī�� �����ִ� �ð�
		Sleep(400);

		// Ŭ�� �̺�Ʈ �ʱ�ȭ
		pDoc->gd_bShow[gv_nRowTempIndex][gv_nColTempIndex] = FALSE;
		pDoc->gd_bShow[pDoc->gd_nRowIndex][pDoc->gd_nColIndex] = FALSE;
		pDoc->gd_nBmpFirstID = pDoc->gd_nBmpSecondID = 0;
		gv_nRowTempIndex = gv_nColTempIndex = 0;
	}

	Invalidate();
	if(gv_nMatchCount == (pDoc->gd_nRow*pDoc->gd_nCol)/2) OnSuccess() ;
}

// ����������
void CGameView::OnSuccess(void)
{
	// ��ũ ��� ����
	KillTimer (true) ;	// �޼��� �ڽ��� ���� ���ص� �ð��� �帣�� �ʵ���
	int res;
	StopSounds (gv_bgDV) ;
	StopSounds (gv_timeDV) ;		// �ð��� �����ų� �����ϸ� ������ ��
	
	if(gv_sec != 0){
		PlaySounds (gv_successDV) ;
		gv_scoreTF =!gv_scoreTF ;		// ���ھ� Ÿ�̸� ����
		gv_tempMin =gv_min ; gv_tempSec =gv_sec ;

		SetTimer (true, 40, NULL) ;	// ������ ���� �ð��� ���� ����Ʈ�� ���Ѵ�.
		res =AfxMessageBox (_T ("���ϵ帳�ϴ�! ��ũ�� ��� �Ͻðڽ��ϱ�?"), MB_YESNO) ;
		
		// ��� �� ��
		if (res == IDYES) {
			CRankNameDlg dlgName ;
			dlgName.DoModal () ;

			CRankDlg *mem =new CRankDlg (dlgName.name, gv_minStr, gv_secStr, gv_csecStr, gv_cnt, gv_lev, gv_rank, gv_point) ;
			mem ->DoModal () ;
		}
	}
	else{
		PlaySounds (gv_failDV) ;
		res =AfxMessageBox (_T ("��Ÿ���׿�. �ٽ� �Ͻðڽ��ϱ�?"), MB_YESNO) ;
		gv_TF =true ;		// ������� �ٽ� ���� �ʱ� ����
		StopSounds (gv_failDV) ;		// ��ȭ���ڸ� ������ ������ �����Ѵ�.
	}
	// ����� ����
	if(gv_TF == false){		// ���� ������ gv_TF�� ���� ������ �ǵ��ƿ�
		KillTimer (true) ;		
		gv_scoreTF =!gv_scoreTF ;		// ���ھ� Ÿ�̸� ����
		StopSounds (gv_successDV) ;		// ��ȭ���ڰ� �߱��� ������ ����.
		res = AfxMessageBox(_T("�ٽ� �����Ͻðڽ��ϱ�?"), MB_YESNO);
	}

	if(res == IDYES){
		gv_cnt = gv_point = gv_min = 0 ;
		gv_csec =100 ;
		CGameDoc* pDoc = GetDocument();
		gv_sec = pDoc->gd_time;
		pDoc->gd_bRandom = TRUE; // �����ϰ� �׸��� ID����

		for(int n=0;n<pDoc->gd_nRow;n++)
			for(int m=0;m<pDoc->gd_nCol;m++)
				pDoc->gd_bShow[n][m] = FALSE;
		
		// �ƹ� �׸��� �������� ���������� �ν��ϱ� ���� �ʱ�ȭ
		pDoc->gd_nBmpFirstID = pDoc->gd_nBmpSecondID = 0 ;
		pDoc->gd_bMouse = FALSE;
		gv_nMatchCount = 0; 
		isInit = TRUE;
		Invalidate();
	}
	else{ // �ٽ� ���� ������ ����
		PlaySound (L"C:\\image\\���ᰡ������.wav", NULL, SND_SYNC) ;
		PostMessageW(WM_QUIT);
	}
}
int CGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CLevelDlg dlg;
	int res =dlg.DoModal();	// domodal�� �ҷ����Ƿ� �� �Լ��ȿ��� �ذ��ؾߵ�.
	if (res == IDCANCEL) exit(1);	// x��ư�� ������ �ٷ� �����Ѵ�.
	
	if (res == IDOK){
		// ������, �� �� ����
		gv_bgColor = dlg.ld_rectColor;
		gv_font = dlg.ld_font;

		// ���̵� (��, ��, �ð�) ����
		CGameDoc *pDlg =GetDocument () ;	// Doc �����ͷ�
		pDlg ->gd_nRow =dlg.nRow ;		// �Է�
		pDlg ->gd_nCol =dlg.nCol ;
		gv_lev =dlg.strLev ;
		gv_rank =dlg.strRank ;
		gv_sec = pDlg ->gd_time =dlg.time;

		while (gv_sec > 59){		// �ʰ� 60�̻��̸� ������ �ű��.
			++gv_min ;
			gv_sec -=60 ;
		}
	}

	// �ð� �� �⺻ ����
	pTimeDlg =new CTimeDlg;
	pTimeDlg ->color =gv_bgColor ;	// ������ �Ѱ���
	pTimeDlg ->Create (IDD_TIME) ;	// ����
	pTimeDlg ->SetParent (this) ;	// �並 �θ�� �д�.
	pTimeDlg ->timeCtrl.SetStep (-1) ;		// ���� ��
	pTimeDlg ->OnInitDialog () ;		// ������ ��, ���� ����

	return 0;
}


void CGameView::OnWhite()
{
	gv_bgColor = RGB(255, 255, 255); 
	Invalidate();

	pTimeDlg ->color =gv_bgColor ;
	pTimeDlg ->OnInitDialog () ;
}


void CGameView::OnBlack()
{
	gv_bgColor = RGB(0, 0, 0);
	Invalidate();

	pTimeDlg ->color =gv_bgColor ;
	pTimeDlg ->OnInitDialog () ;
}


void CGameView::OnUser()
{
	CColorDialog dlg;
	if(dlg.DoModal() == IDOK){
		gv_bgColor = dlg.GetColor();
		Invalidate();
	}
	pTimeDlg ->color =gv_bgColor ;
	pTimeDlg ->OnInitDialog () ;
}


void CGameView::OnDestroy()
{
	CView::OnDestroy();
	KillTimer (true) ;
}


void CGameView::OnTimer(UINT_PTR nIDEvent)
{
	// ����Ҹ� ����
	if (!gv_min && gv_sec < 10 && !gv_timeDV){	// ���� 0�̰� �ʰ� 10�� �̸��� �� �ð����� ���� ��
		StopSounds (gv_bgDV) ;
		PlaySounds (gv_timeDV) ;
	}

	CClientDC dc (this) ;
	CRect rect ;
	GetClientRect (&rect) ;
	CFont myFont, *pOldFont ;
	CString str;
	
	// Text ���� Part
	myFont.CreateFont (25, 0, 0, 0, FW_BOLD, true, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, gv_font) ;
	pOldFont =dc.SelectObject (&myFont) ;
	dc.SetBkColor (gv_bgColor) ;		// ������ ����� ������ ���� 
	dc.SetTextColor (0x00FFFFFF & ~gv_bgColor) ;		// ���� ���� ����ȭ���� �ݴ� ������

	// �ð��� ���� ��º�
	if (!gv_scoreTF) {
		if (gv_min < 10 && gv_min) gv_minStr.Format (_T(" 0%d"), gv_min) ;
		else if (!gv_min) gv_minStr.Format (_T (" 00")) ;
		else gv_minStr.Format (_T (" %d"), gv_min) ;
		
		if (gv_sec < 10 && gv_sec) gv_secStr.Format (_T("0%d"), gv_sec) ;
		else if (!gv_sec) gv_secStr.Format (_T ("00")) ;
		else gv_secStr.Format (_T ("%d"), gv_sec) ;

		if (gv_csec < 10 && gv_csec) gv_csecStr.Format (_T("0%d"), gv_csec) ;
		else if (!gv_csec) gv_csecStr.Format (_T ("00")) ;
		else gv_csecStr.Format (_T ("%d"), gv_csec) ;

		str.Format (_T (" %s : %s : %s "), gv_minStr, gv_secStr, gv_csecStr) ;
		dc.SetTextAlign (TA_RIGHT) ;
		dc.TextOutW (rect.Width () -20, rect.top +45, str) ;

		// �ʰ��
		if (--gv_csec < 0) {
			if (!gv_min && !gv_sec) OnSuccess () ;
			gv_csec =99 ;
			gv_sec-- ;
			pTimeDlg ->timeCtrl.StepIt () ;		// �ʰ� �ٶ����� ����
		}
		if (gv_sec < 0 && gv_min) {
			gv_sec =59 ;
			gv_min-- ;
		}

		// ī��Ʈ ���
		str.Format (_T (" CLICK COUNT : %u "), gv_cnt) ;
		dc.TextOutW (rect.Width () -20, rect.top +20, str) ;

		// ���� ���
		dc.SetTextAlign (TA_CENTER) ;
		str.Format (_T (" Score : %u "), gv_point) ;
		dc.TextOutW (rect.Width () /2, rect.top +25, str) ;
	}
	else {
		while (gv_tempMin-- > 0) gv_tempSec +=60 ;		// ���� ���� �ִٸ� �ʷ� �ű�
		// �ð� ���� �� ����Ʈ ����
		if (gv_tempSec > 0) {					// �ʰ� 0���� Ŭ������
			gv_point+=3 ; gv_tempSec-- ;			// ������ 3���� �ʴ� 1����
			pTimeDlg ->timeCtrl.StepIt () ;
			dc.SetTextAlign (TA_CENTER) ;
			str.Format (_T (" Score :%u "), gv_point) ;	
			dc.TextOutW (rect.Width () /2 , rect.top +25, str) ;
		}
	}
	dc.SelectObject (myFont) ;
	myFont.DeleteObject () ;
	CView::OnTimer(nIDEvent);
}


// ���带 ����ϱ� ���� �Լ�
void CGameView::PlaySounds(DWORD dv)
{
	MCI_PLAY_PARMS mciPlay ;
	// Play Part
	mciSendCommand (dv, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay) ;	// MCI_PLAY ����� �ش�
}

// �������� ����
void CGameView::StopSounds(DWORD dv)
{
	// Stop Part
	mciSendCommand (dv, MCI_CLOSE, 0, NULL) ;
}

// ���������� ����̽��� ����.
DWORD CGameView::OpenSounds(CString name)
{
	// Load Part
	MCI_OPEN_PARMS mciOpen ;		// mci���� �÷���
	DWORD dv ;		// ����̽�

	mciOpen.lpstrElementName = name ;			//��� �� ���� �װ��
	mciOpen.lpstrDeviceType = L"MPEGVideo";		// ��� �� Ÿ��

	mciSendCommand (NULL, MCI_OPEN, MCI_OPEN_ELEMENT|MCI_OPEN_TYPE,
		(DWORD)(LPVOID) &mciOpen) ;          //MCI_OPEN ����� �ش�.

	// Play Part
	dv = mciOpen.wDeviceID;        //����̽� ���̵� �޴���.
	
	return dv;
}

// âũ�Ⱑ ���� �Ǿ����� Ÿ�ӹ��� ��ġ�� ���ϱ� ���� �Լ�
void CGameView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CRect rect ;
	GetClientRect (&rect) ;

	// View�� ������ �Ѱ���
	pTimeDlg ->rectView =rect ;
	pTimeDlg ->OnInitDialog () ;
}
