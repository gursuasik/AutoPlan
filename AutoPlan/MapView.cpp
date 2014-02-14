// MapView.cpp : implementation file
//

#include "stdafx.h"
#include "CAPT.h"
#include "MapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapView

IMPLEMENT_DYNCREATE(CMapView, CScrollView)

CMapView::CMapView()
{
}

CMapView::~CMapView()
{
}


BEGIN_MESSAGE_MAP(CMapView, CScrollView)
	//{{AFX_MSG_MAP(CMapView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapView drawing

void CMapView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CMapDoc* pDoc = GetDocument();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = pDoc->CampusSize.x*pDoc->Scale;
	sizeTotal.cy = pDoc->CampusSize.y*pDoc->Scale;
	SetScrollSizes(MM_LOMETRIC, sizeTotal);
}

void CMapView::OnDraw(CDC* pDC)
{
	CMapDoc* pDoc = GetDocument();
	// TODO: add draw code here
	pDC->PlayMetaFile(pDoc->HMetaFile);
}

/////////////////////////////////////////////////////////////////////////////
// CMapView diagnostics

#ifdef _DEBUG
void CMapView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMapView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMapDoc* CMapView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapDoc)));
	return (CMapDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapView message handlers

BOOL CMapView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush bri( RGB(128,128,128) );
	FillOutsideRect( pDC, &bri );
	return TRUE;

	return CScrollView::OnEraseBkgnd(pDC);
}
/*
void CMapView::DrawLegend(void)
{

}
*/