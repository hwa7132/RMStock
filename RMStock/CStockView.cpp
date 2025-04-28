// CStockView.cpp: 구현 파일
//

#include "pch.h"
#include "RMStock.h"
#include "CStockView.h"


// CStockView

IMPLEMENT_DYNCREATE(CStockView, CView)

CStockView::CStockView()
{

}

CStockView::~CStockView()
{
}

BEGIN_MESSAGE_MAP(CStockView, CView)
END_MESSAGE_MAP()


// CStockView 그리기

void CStockView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CStockView 진단

#ifdef _DEBUG
void CStockView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CStockView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStockView 메시지 처리기
