
// GameView.h : CGameView Ŭ������ �������̽�
//

#pragma once
#pragma comment(lib, "winmm.lib")
#include <MMSystem.h>
#include "TimeDlg.h"

class CGameView : public CView
{
protected: // serialization������ ��������ϴ�.
	CGameView();
	DECLARE_DYNCREATE(CGameView)
	
// Ư���Դϴ�.
public:
	CGameDoc* GetDocument() const;

// �۾��Դϴ�.
public:
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	// ���� ���콺�� ��ǥ������ �׸��� ��ġ�� ����Ͽ� �����ϰ� �ִ� �ε���
	UINT gv_nRowTempIndex;
	UINT gv_nColTempIndex;

	UINT gv_cnt;	// L��ư ¦�� ������ ���� ����
	UINT gv_point;	// ��������
	UINT gv_timeUpper;	// �ð����� �ִ� ������ ���� ����

	BOOL isInit;
	BOOL gv_TF;	// L��ư Ŭ���� ¦�� ������ ���
	BOOL gv_scoreTF;	// ������ ���� ����� ���� ������

	COLORREF gv_bgColor;	// ����

	// �ð� int
	int gv_min;	// ��
	int gv_sec;	// ��
	int gv_csec;	// 1/100
	int gv_tempMin;	// �ӽ� ��
	int gv_tempSec;	// �ӽ� ��

	int gv_nMatchCount;	// ���� �׸��� ������ ���� ���� ����
	int gv_levCnt;	// ���̵� int
	
	// �ð� String
	CString gv_minStr;	// ��
	CString gv_secStr;	// ��
	CString gv_csecStr;	// 1/100��

	void OnMatching(void);
	void OnSuccess(void);
	void PlaySounds (DWORD);		// ���带 ����ϱ� ���� �Լ�
	void StopSounds(DWORD);	// �������� ����

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWhite();
	afx_msg void OnBlack();
	afx_msg void OnUser();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	CString gv_lev;	// ���̵� ��
	CString gv_rank;	// .txt�� �̸�
	CString gv_font;	// ����ü

	DWORD gv_timeDV;	// �ð������� ���� ������ ����̽�
	DWORD gv_bgDV;	// ������� ������ ����̽�
	DWORD OpenSounds(CString name);	// ���������� ����̽��� ����.
	DWORD gv_failDV;	// ���н� ���� ����̽�
	DWORD gv_successDV;	// ������ ������ ����̽�
	
	CTimeDlg *pTimeDlg;
};

#ifndef _DEBUG  // GameView.cpp�� ����� ����
inline CGameDoc* CGameView::GetDocument() const
   { return reinterpret_cast<CGameDoc*>(m_pDocument); }
#endif

