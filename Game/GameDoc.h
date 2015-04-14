
// GameDoc.h : CGameDoc Ŭ������ �������̽�
//


#pragma once
#include "afxwin.h"


class CGameDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CGameDoc();
	DECLARE_DYNCREATE(CGameDoc)

// Ư���Դϴ�.
public:
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	CBitmap	gd_bmp[6][6];	// ��Ʈ�� ����
	CSize		gd_bmCell;		// ���� �� �׸� �ϳ��� ũ��
	
	int gd_nRow;		// ���ڼ��� ����
	int gd_nCol;
	int gd_nRnd[36];			// �������� �߻��� �׸���ġ���� ������ ����
	int gd_time;
	int gd_nRowIndex;
	int gd_nColIndex;

	bool gd_bRandom;	// ������ / ������ ���� �ľ�
	bool gd_bShow[6][6];
	bool gd_bMouse;

	void ResizeWindow(void);
	void OnRandom(void);
	void InitBoard(void);
		
	UINT gd_nBmpID[6][6];	// �׸��� ID���� �迭�� ����
	UINT gd_nBmpFirstID;	// ù��° ���� �׸��� ���̵� ��
	UINT gd_nBmpSecondID;	// �ι�° ���� �׸��� ���̵� ��
};
