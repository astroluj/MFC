
// GameDoc.cpp : CGameDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Game.h"
#endif

#include "GameDoc.h"
#include "GameView.h"
#include "MainFrm.h"
#include "LevelDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGameDoc

IMPLEMENT_DYNCREATE(CGameDoc, CDocument)

BEGIN_MESSAGE_MAP(CGameDoc, CDocument)
END_MESSAGE_MAP()


// CGameDoc ����/�Ҹ�

CGameDoc::CGameDoc()
{
	gd_time = 19;
	gd_bmCell = CSize(125, 115);	// ��ũ�� �ʱ�ȭ
	gd_nRow = 3;	// ���� �ʱ� ��,�� ��
	gd_nCol = 4;	// ���̵� ���� ���ҽ� �ʱⰪ�� ����
}

CGameDoc::~CGameDoc()
{
}

BOOL CGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CGameDoc serialization

void CGameDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CGameDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CGameDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGameDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGameDoc ����

#ifdef _DEBUG
void CGameDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGameDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGameDoc ���


void CGameDoc::ResizeWindow(void)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();

	CREATESTRUCT st;
	CREATESTRUCT& rst = st;

	pMain->PreCreateWindow(rst);
}


void CGameDoc::OnRandom(void)
{
	gd_bRandom =false ;		// �����Լ��� �ٽ� �θ����ʱ����� �ʱ�ȭ

	srand((unsigned)time(NULL)) ;

	BOOL bInsert = TRUE; // ��Ʈ�� ���� ����
	int nGrating = gd_nRow *gd_nCol; // ������ �� ��

	for(int n=0;n<nGrating;n++){
		gd_nRnd[n] = (rand()%(nGrating/2)) + 1; // �ϴ� ���� ����
		// �ߺ�üũ
		for(int m=0;m<n;m++)
			if(gd_nRnd[n] == gd_nRnd[m]) {
				if(!bInsert){
					n--;
					bInsert = TRUE;
					break;
				}
				bInsert = FALSE;
			}
	}
	int nCount = 0;

	for(int n=0;n<gd_nRow;n++)
		for(int m=0;m<gd_nCol;m++)
			gd_nBmpID[n][m] = gd_nRnd[nCount++];
}


void CGameDoc::InitBoard(void)
{
	gd_bRandom = TRUE;
	for(int n=0;n<gd_nRow;n++)
		for(int m=0;m<gd_nCol;m++)
			gd_bShow[n][m] = FALSE;

	// �ƹ� �׸��� �������� �ʾҴٰ� �ʱ�ȭ.
	gd_nBmpFirstID = gd_nBmpSecondID = gd_bMouse =0;
	ResizeWindow();
	OnRandom();
}

