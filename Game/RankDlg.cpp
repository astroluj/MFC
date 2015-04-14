// RankDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Game.h"
#include "RankDlg.h"
#include "afxdialogex.h"


// CRankDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRankDlg, CDialogEx)

CRankDlg::CRankDlg(CString str, CString m, CString s, CString c, UINT cnt, CString lev, CString rank, UINT point, CWnd* pParent /*=NULL*/)
	: CDialogEx(CRankDlg::IDD, pParent)
{
	member =str ; nMin =m ; nSec =s, nCsec =c, nCnt =cnt ; strLev =lev ; rankName =rank ; nPoint =point ;
	TimePoint () ;	// �����ڷ� �ʱ�ȭ �԰� ���ÿ� �ð����
}

CRankDlg::~CRankDlg()
{
}

void CRankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RANKLIST, rankList);
	DDX_Control(pDX, IDC_RANKLIST, rankList);
}


BEGIN_MESSAGE_MAP(CRankDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_EASY, &CRankDlg::OnBnClickedButtonEasy)
	ON_BN_CLICKED(IDC_BUTTON_NORMAL, &CRankDlg::OnBnClickedButtonNormal)
	ON_BN_CLICKED(IDC_BUTTON_HARD, &CRankDlg::OnBnClickedButtonHard)
	ON_BN_CLICKED(IDC_BUTTON_DELALL, &CRankDlg::OnBnClickedButtonDelall)
END_MESSAGE_MAP()


// CRankDlg �޽��� ó�����Դϴ�.

BOOL CRankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect gv_rect ;
	rankList.GetClientRect (&gv_rect) ;	// ����Ʈ ��Ʈ���� ������ ����

	// ������ ����
	rankList.InsertColumn (0, _T ("�� ��"), LVCFMT_CENTER, 70) ;		
	rankList.InsertColumn (1, _T ("�� ��"), LVCFMT_CENTER, 70) ;	
	rankList.InsertColumn (2, _T ("�� ��"), LVCFMT_CENTER, 70) ;
	rankList.InsertColumn (3, _T ("�� ��"), LVCFMT_CENTER, 100) ;
	rankList.InsertColumn (4, _T ("Ŭ�� ��"), LVCFMT_CENTER, 70) ;
	rankList.InsertColumn (5, _T ("���̵�"), LVCFMT_CENTER, gv_rect.Width () -380) ;
	
	// ���� ��� �ҷ���
	AutoLoad () ;

	// ���� �߰� �� ��ũ ���
	CString str ;
	str.Format (_T ("%u"), nRank) ;
	int cnt =rankList.InsertItem (rankList.GetItemCount (), str) ;	// ����
	rankList.SetItemText (cnt, 1, member) ;		// �̸�
	str.Format (_T ("%u"), nPoint) ;	
	rankList.SetItemText (cnt, 2, str) ;		// ����
	rankList.SetItemText (cnt, 3, nMin +_T(":")+nSec+_T(":") +nCsec) ;		// �ð�
	str.Format (_T ("%u"), nCnt) ;		
	rankList.SetItemText (cnt, 4, str) ;		// Ŭ�� ��
	rankList.SetItemText (cnt, 5, strLev) ;		// ���̵�

	SortRank (rankName) ;		// �ۼ��� ����Ʈ�� �����Ѵ�.

	int nFind =rankList.GetItemCount (), idx ;

	for (idx =0 ; idx < nFind ; idx++) {
		if (rankList.GetItemText (idx, 1) == member &&
			_ttoi (rankList.GetItemText (idx, 2)) == nPoint &&
			_ttoi (rankList.GetItemText (idx, 4)) == nCnt) break ;
	}

	rankList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	rankList.SetItemState (idx, LVIS_FOCUSED | LVIS_SELECTED, 0x000F) ;

	return TRUE;  // return TRUE unless you set the focus to a control
}

// â�� ������ �ڵ����� ������
void CRankDlg::AutoSave(void)
{	
	CStdioFile file (rankName, 
		CFile::shareDenyNone /* �ٸ� ���μ����� ���� ������ �����ϰ� �Ѵ� */
		/* ������ �������� ������ txt ������ �����ϰ�, ó�� type�� binary �̴�.
			������ �����ϸ� ���� ����. */
		|CStdioFile ::modeCreate 
		|CStdioFile ::modeNoTruncate 
		|CStdioFile ::modeWrite 
		|CStdioFile ::typeBinary) ;	

	// �����͸� ����
	for (int i =0 ; i < rankList.GetItemCount () ; i++)
		for (int j =0 ; j < 6 ; j++) 
			file.WriteString (rankList.GetItemText (i, j) +"\n") ;	

	file.Close () ;
} 

// â�� ������ �ڵ����� �ҷ���
void CRankDlg::AutoLoad(void)
{
	// Ranking.txt�� �б��������� ����
	CFile file (rankName, 
		CFile::shareDenyNone 
		|CFile ::modeNoTruncate 
		|CFile ::modeCreate 
		|CFile ::modeRead) ;	
	
	CString str ;

	CArchive *ar =new CArchive (&file, CArchive ::load) ;	
	
	bool TF =true ;		// �� �پ� �������� boolean ����
	int col =1, row =-1 ;	

	// �����͸� �д´�.
	while (ar ->ReadString (str)) {
		// �� ���� ��� �о�����
		if (col == 6) {		
			TF =!TF ;		
			col =1 ;
		}

		// ���� �Է¹޴´�.
		if (TF) {	
			row =rankList.GetItemCount () ;
			rankList.InsertItem (row, str) ;
			TF =!TF ;
		}
		// ���� �ϳ��� �����Ѵ�.
		else rankList.SetItemText (row, col++, str) ;	
	}
	// ��ũ ó��
	if (row < 0)  nRank =1 ;		// row�� -1�̸� ù �����̹Ƿ� 1/
	else nRank =row +2 ;		// row�� -1�� �ƴϸ� ������ �����Ƿ� �پ�����ī��Ʈ�� ������ 2�� ����


	ar ->Close () ; 
	file.Close () ;
}

// â�� ������ �����͸� �����Ѵ�
void CRankDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	AutoSave () ;
}

// ��ũ����
void CRankDlg::SortRank(CString rankName)
{
	int row =rankList.GetItemCount () ;
	int pt1, pt2, cnt1, cnt2 ;

	// ������ Ŭ������ �������� �����Ѵ�
	for (int i =0 ; i < row -1 ; i++)
		for (int j =i +1 ; j < row ; j++) {

			if(CompareRank (&pt1, &pt2, 2, i, j)) SwapRank(i, j);		
			
			if (pt1 == pt2) 
				if(CompareRank (&cnt1, &cnt2, 4, i, j)) SwapRank(i, j);
		}
	// ����
	NaturalMergeSort (0, row) ;
}

// ��ũ������ȯ
void CRankDlg::SwapRank(int val1, int val2)
{
	CString temp =rankList.GetItemText (val2, 0) ;

	rankList.SetItemText (val2, 0, rankList.GetItemText (val1, 0)) ;
	rankList.SetItemText (val1, 0, temp) ;
}

// ���� ������ ���� ���� ������ �´���
// return 1 -- ��ũ ����ġ
// return 0 -- ��ũ ��ġ
int CRankDlg::CompareRank(int * val1, int * val2, int col, int i, int j)
{
	int rank1 =_ttoi (rankList.GetItemText (i, 0)), rank2 =_ttoi (rankList.GetItemText (j, 0)) ;

	*val1 =_ttoi (rankList.GetItemText (i, col)) ; 
	*val2 =_ttoi (rankList.GetItemText (j, col)) ;

	// ������ ����
	if (col == 2  && (*val1 < *val2 && rank1 < rank2)) return 1;

	// Ŭ�� ���� ����
	else if (col == 4 && (*val1 < *val2 && rank1 > rank2)) return 1;
	
	return 0;
}

// ������ �ٲ��� �ٲ� ������� �� ���� �ڿ���������
void CRankDlg::NaturalMergeSort(int top, int bottom)
{
	int i, j, val1, val2 ;	

	// top ���� ������� ���� �Ǿ��ִ°� ���� Ž��
	for (i =top +1 ; i < bottom ; i++) {
		val1 =_ttoi (rankList.GetItemText (i -1, 0)) ;
		val2 =_ttoi (rankList.GetItemText (i, 0)) ;
		if (val1 > val2) break ;
	}

	if (i >= bottom && !top) return ;		// ���� top�� 0�̰� i�� bottom�� ���� �ʴٸ� ������ �Ǿ��ִ� ���̹Ƿ� return

	// Ž�� �Ŀ� �� �ٽ� ������� ���� �Ǿ��ִ� ������ Ž��
	for (j =i +1 ; j < bottom ; j++) {
		val1 =_ttoi (rankList.GetItemText (j -1, 0)) ;
		val2 =_ttoi (rankList.GetItemText (j, 0)) ;
		if (val1 > val2) break ;
	}

	// ���긮��Ʈ�� �ϳ��� Ž�� ���� ���� ���
	if (j <= bottom) QuickSort (top, j -1) ;	// 2���� Ž���� ���� ����Ʈ�� �ϳ��� ���� ����

	if (j < bottom) NaturalMergeSort (j, bottom) ;	// Ž���� List�� ������ ���� �ʾҴٸ� top�� ���� ��Ų ���� ����Ʈ�� ���� Element�� �ش�.
	else NaturalMergeSort (0, bottom) ;		// ���� Ž���� List�� ������ �ߴٸ� top�� 0���� �ʱ�ȭ ���� �ٽ� ����
}

// �� ��Ʈ
void CRankDlg::QuickSort(int first, int last)
{
    int pivot, left, right ;

     if (first < last) {
         pivot =(last +first) /2 ; 
		 left =first ; right =last ;
         while (left < right) {
			 while (_ttoi (rankList.GetItemText (left, 0)) <= _ttoi (rankList.GetItemText (pivot, 0)) && left < last) left++ ;
             while (_ttoi (rankList.GetItemText (right, 0)) > _ttoi (rankList.GetItemText (pivot, 0))) right-- ;
             if (left < right) SwapItem (left, right) ;	// ��ȯ 
         }
		 SwapItem (pivot, right) ;
     
         QuickSort (first, right -1) ;
         QuickSort (right +1, last) ;
    }
}

// ����Ʈ ��Ʈ���� �������� ��ȯ
void CRankDlg::SwapItem(int val1, int val2)
{
	// val1���� ����Ÿ�� temp�� �ְ�
	CString temp[] ={ rankList.GetItemText (val1, 0), rankList.GetItemText (val1, 1), 
		rankList.GetItemText (val1, 2), rankList.GetItemText (val1, 3),
		rankList.GetItemText (val1, 4) } ;

	// val1�࿡ val2�� ���� �ִ´�.
	for (int i =0 ; i < 5 ; i++) 
		rankList.SetItemText (val1, i, rankList.GetItemText (val2, i)) ;

	// val2�࿡ val1�� ���� �ִ´�.
	for (int i =0 ; i < 5 ; i++)
		rankList.SetItemText (val2, i, temp[i]) ;	
}

// Easy ��ư Ŭ�� �̺�Ʈ
void CRankDlg::OnBnClickedButtonEasy()
{
	AutoSave () ;		// ���� ����� ����
	rankName =_T ("C:\\image\\EasyRanking.txt") ;	// ���ϸ� ����
	rankList.DeleteAllItems () ;		// ����� ����
	AutoLoad () ;		// ���� ��� �ҷ�����
}

// Normal ��ư Ŭ�� �̺�Ʈ
void CRankDlg::OnBnClickedButtonNormal()
{
	AutoSave () ;		
	rankName =_T ("C:\\image\\NormalRanking.txt") ;	
	rankList.DeleteAllItems () ;	
	AutoLoad () ;		
}

// Hard ��ư Ŭ�� �̺�Ʈ
void CRankDlg::OnBnClickedButtonHard()
{
	AutoSave () ;	 
	rankName =_T ("C:\\image\\HardRanking.txt") ;	 
	rankList.DeleteAllItems () ; 
	AutoLoad () ;		 
}

// �ʱ�ȭ ��ư Ŭ��
void CRankDlg::OnBnClickedButtonDelall()
{
	// �켱 ����Ʈ ��Ʈ�ѿ� �ִ� ���� ����, 
	// �ش� ����Ʈ ��Ʈ���� �����Ͱ� �ִ� file�� �̸��� ���� ����
	// �ش� ������ �ʱ�ȭ �Ѵ�.
	rankList.DeleteAllItems () ;	
	FILE *fp;
	CFile file (rankName, 
		CFile::shareDenyNone 
		| CFile ::modeCreate 
		| CFile ::modeNoTruncate 
		| CFile ::modeRead) ;	
	strLev = file.GetFileName();

	// ���� ���� �ʱ�ȭ
	if(strLev == _T("EasyRanking.txt"))
		fp = fopen("c:\\image\\EasyRanking.txt",  "w");
	else if(strLev == _T("NormalRanking.txt"))
		fp = fopen("c:\\image\\NormalRanking.txt",  "w");
	else 
		fp = fopen("c:\\image\\HardRanking.txt",  "w");
}

// �귯�� �ð��� ��Ÿ���� ���� �Լ�
void CRankDlg::TimePoint(void)
{
	// ����϶� �ð� ���
	if (rankName == _T ("C:\\image\\HardRanking.txt")) {
		nMin.Format (_T ("0%d"), 1 -_ttoi (nMin)) ;
		if ((39 -_ttoi (nSec)) > 10) nSec.Format (_T ("%d"), 39 -_ttoi (nSec)) ;
		else nSec.Format (_T ("0%d"), 39 -_ttoi (nSec)) ;

		if ((100 -_ttoi (nCsec)) > 10) nCsec.Format (_T ("%d"), 100 -_ttoi (nCsec)) ;
		else nCsec.Format (_T ("0%d"), 100 -_ttoi (nCsec)) ;
	}

	// �߱��϶� �ð� ���
	if (rankName == _T ("C:\\image\\NoramlRanking.txt")) {
		if ((49 -_ttoi (nSec)) > 10) nSec.Format (_T ("%d"), 49 -_ttoi (nSec)) ;
		else nSec.Format (_T ("0%d"), 49 -_ttoi (nSec)) ;

		if ((100 -_ttoi (nCsec)) > 10) nCsec.Format (_T ("%d"), 100 -_ttoi (nCsec)) ;
		else nCsec.Format (_T ("0%d"), 100 -_ttoi (nCsec)) ;
	}

	// �ʱ��϶� �ð� ���
	if (rankName == _T ("C:\\image\\EasyRanking.txt")) {
		if((19 -_ttoi (nSec)) > 10) nSec.Format (_T ("%d"), 19 -_ttoi (nSec)) ;
		else nSec.Format (_T ("0%d"), 19 -_ttoi (nSec)) ;

		if ((100 -_ttoi (nCsec)) > 10) nCsec.Format (_T ("%d"), 100 -_ttoi (nCsec)) ;
		else nCsec.Format (_T ("0%d"), 100 -_ttoi (nCsec)) ;
	}
}
