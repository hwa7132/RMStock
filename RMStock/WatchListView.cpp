#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "RMStock.h"
#endif

#include "RMStockDoc.h"
#include "WatchListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWatchListView

IMPLEMENT_DYNCREATE(CWatchListView, CStockView)

BEGIN_MESSAGE_MAP(CWatchListView, CStockView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CStockView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CStockView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWatchListView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CWatchListView 생성/소멸

CWatchListView::CWatchListView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CWatchListView::~CWatchListView()
{
}

BOOL CWatchListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CStockView::PreCreateWindow(cs);
}

// CWatchListView 그리기

void CWatchListView::OnDraw(CDC* /*pDC*/)
{
	CRMStockDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CWatchListView 인쇄


void CWatchListView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWatchListView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CWatchListView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CWatchListView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CWatchListView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWatchListView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWatchListView 진단

#ifdef _DEBUG
void CWatchListView::AssertValid() const
{
	CStockView::AssertValid();
}

void CWatchListView::Dump(CDumpContext& dc) const
{
	CStockView::Dump(dc);
}

CRMStockDoc* CWatchListView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRMStockDoc)));
	return (CRMStockDoc*)m_pDocument;
}
#endif //_DEBUG


// CWatchListView 메시지 처리기


int CWatchListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStockView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_MainDlg.Create(CWatchListViewDlg::IDD, this);

	return 0;
}


void CWatchListView::OnSize(UINT nType, int cx, int cy)
{
	CStockView::OnSize(nType, cx, cy);

	if (m_MainDlg.GetSafeHwnd())
	{
		m_MainDlg.MoveWindow(0, 0, cx, cy);
	}
}

void CWatchListView::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	m_MainDlg.OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
}