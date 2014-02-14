// LANPTView.cpp : implementation file
//

#include "stdafx.h"
#include "CAPT.h"
#include "LANPTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLANPTView

IMPLEMENT_DYNCREATE(CLANPTView, CScrollView)

CLANPTView::CLANPTView()
{
	Tool = ID_TOOLS_SELECT;
	Draggable = false;
	Select =true;
	Captured = false;
}

CLANPTView::~CLANPTView()
{
}


BEGIN_MESSAGE_MAP(CLANPTView, CScrollView)
	//{{AFX_MSG_MAP(CLANPTView)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDW_FLOOR, OnFloorChange)
	ON_CBN_SELCHANGE(IDW_SCALE, OnScaleChange)
	ON_COMMAND_RANGE(ID_TOOLS_SELECT, ID_TOOLS_ACCESSPOINT, OnTool)
	ON_UPDATE_COMMAND_UI_RANGE(ID_TOOLS_SELECT, ID_TOOLS_ACCESSPOINT, OnUpdateTool)
	ON_COMMAND(ID_TOOLS_COVERAGEMAP, OnMap)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLANPTView drawing

void CLANPTView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CLANPTDoc* pDoc = GetDocument();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = pDoc->CampusSize.x*pDoc->Scale;
	sizeTotal.cy = pDoc->CampusSize.y*pDoc->Scale;
	SetScrollSizes(MM_LOMETRIC, sizeTotal);
	ResetFloorCombo();
	ResetScaleCombo();
}

void CLANPTView::OnDraw(CDC* pDC)
{
	CLANPTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code here
// Paint Background
	CSize InnerRectPos = GetScrollPosition();
	CSize InnerRectSize = GetTotalSize();
	pDC->FillSolidRect(InnerRectPos.cx, InnerRectPos.cy, InnerRectSize.cx, -InnerRectSize.cy, RGB(255,255,255));
// Draw Grid
	if(pDoc->ShowGrid == 1)	DrawGrid(pDC);
	pDoc->TheBuilding.Draw(pDC, pDoc->Scale);
	pDoc->TheBuilding.DrawLAN(pDC,pDoc->Scale);
}

/////////////////////////////////////////////////////////////////////////////
// CLANPTView diagnostics

#ifdef _DEBUG
void CLANPTView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CLANPTView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CLANPTDoc* CLANPTView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLANPTDoc)));
	return (CLANPTDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLANPTView message handlers

void CLANPTView::ResetFloorCombo(void)
{
	CMainFrame* ParentFrame = (CMainFrame*) ((CMDIChildWnd*) GetParentFrame())->GetMDIFrame();
	ParentFrame->m_wndWLANPlanningBar.m_ComboFloor.ResetContent();
	CLANPTDoc* pDoc = GetDocument();
	int SelNo, i, n;
	char names[200][16];
	n = pDoc->TheBuilding.GetFloorCount();
	SelNo = pDoc->TheBuilding.GetSelected();
	pDoc->TheBuilding.GetFloorNames(names);
	for(i = 0; i < n; i++) 
		ParentFrame->m_wndWLANPlanningBar.m_ComboFloor.AddString(names[i]);
	ParentFrame->m_wndWLANPlanningBar.m_ComboFloor.SetCurSel(SelNo);

}

void CLANPTView::OnFloorChange(void)
{
	CMainFrame* ParentFrame = (CMainFrame*) ((CMDIChildWnd*) GetParentFrame())->GetMDIFrame();
	int SelNo = ParentFrame->m_wndWLANPlanningBar.m_ComboFloor.GetCurSel();
	CLANPTDoc* pDoc = GetDocument();
	pDoc->TheBuilding.SetSelected(SelNo);
	Invalidate(TRUE);
}

void CLANPTView::ResetScaleCombo(void)
{
	CMainFrame* ParentFrame = (CMainFrame*) ((CMDIChildWnd*) GetParentFrame())->GetMDIFrame();
	ParentFrame->m_wndWLANPlanningBar.m_ComboScale.ResetContent();
	CLANPTDoc* pDoc = GetDocument();
	int i;
	char names[5][6] = {{'1','/','2','5'}, {'1','/','5','0'}, {'1','/','1','0','0'}, {'1','/','2','0','0'}, {'1','/','4','0','0'}} ;

	for(i = 0; i < 5; i++) 
		ParentFrame->m_wndWLANPlanningBar.m_ComboScale.AddString(names[i]);
	ParentFrame->m_wndWLANPlanningBar.m_ComboScale.SetCurSel(2);

}

void CLANPTView::OnScaleChange(void)
{
	CLANPTDoc* pDoc = GetDocument();
	CMainFrame* ParentFrame = (CMainFrame*) ((CMDIChildWnd*) GetParentFrame())->GetMDIFrame();
	int SelNo = ParentFrame->m_wndWLANPlanningBar.m_ComboScale.GetCurSel();
	
	switch(SelNo)
	{
	case 4:
		pDoc->Scale = 25;
		break;
	case 3:
		pDoc->Scale = 50;
		break;
	case 2:
		pDoc->Scale = 100;
		break;
	case 1:
		pDoc->Scale = 200;
		break;
	case 0:
		pDoc->Scale = 400;
		break;
	};

	CSize sizeTotal;
	sizeTotal.cx = pDoc->CampusSize.x*pDoc->Scale;
	sizeTotal.cy = pDoc->CampusSize.y*pDoc->Scale;
	SetScrollSizes(MM_LOMETRIC, sizeTotal);

	Invalidate(TRUE);
}

void CLANPTView::DrawGrid(CDC *pDC)
{
	ASSERT(pDC !=NULL);
	CLANPTDoc* pDoc = GetDocument();
	int i, j;
	int x= pDoc->CampusSize.x*pDoc->Scale, y = pDoc->CampusSize.y*pDoc->Scale;
	int dx = pDoc->GridSize*pDoc->Scale, dy = pDoc->GridSize*pDoc->Scale;
	for(i=0; i<= x; i+=dx)
		for(j=0; j<= y; j+=dy)
			pDC->SetPixel(i,-j,RGB(0,0,0));

}

Point2d CLANPTView::Convert(CPoint point)
{
	CLANPTDoc* pDoc = GetDocument();
	return Point2d((double) point.x/pDoc->Scale, (double) point.y/pDoc->Scale);
}

CPoint CLANPTView::Convert(Point2d point)
{
	CLANPTDoc* pDoc = GetDocument();
	return CPoint(point.x*pDoc->Scale, point.y*pDoc->Scale);
}

void CLANPTView::OnTool(UINT nID)
{
	Tool = nID;
}

void CLANPTView::OnUpdateTool(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == Tool);
}

void CLANPTView::OnMap(UINT nID)
{
	CLANPTDoc* pDoc = GetDocument();
	CMetaFileDC MetaFile;
	MetaFile.Create();
	MetaFile.SetMapMode(MM_LOMETRIC);
//	HMETAFILE HMetaFile = pDoc->TheBuilding.GenerateCoverageMap(&MetaFile, pDoc->Scale, pDoc->CampusSize);
//	((CCAPTApp*) AfxGetApp())->NewMapFile(HMetaFile, pDoc->Scale, pDoc->CampusSize);
}

BOOL CLANPTView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush bri( RGB(128,128,128) );
	FillOutsideRect( pDC, &bri );
	return TRUE;
	
	return CScrollView::OnEraseBkgnd(pDC);
}

void CLANPTView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CLANPTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	Point2d point1;
	Captured = true;

	switch(Tool)
	{
	case ID_TOOLS_SELECT:
		pDoc->TheBuilding.SetSelectedAP(Convert(point), pDoc->Scale);
		if(pDoc->TheBuilding.SelectedAP)
		{
//			point1 = Point2d(pDoc->TheBuilding.SelectedAP->Position.x, pDoc->TheBuilding.SelectedAP->Position.y);
//			if((point1.x - point.x)*(point1.x - point.x) + (point1.y - point.y)*(point1.y - point.y)< 900)
//			{
				Draggable = true;
				LastPosition = point;
//			}
		}
		else Draggable = false;
		Invalidate(FALSE);
			
		break;
	
	case ID_TOOLS_ACCESSPOINT:

		pDoc->TheBuilding.AddAccessPoint();
		pDoc->TheBuilding.SetAPPosition(Convert(point), 0.8);
AfxMessageBox("AP Added");
		pDoc->TheBuilding.GenerateImageTree(pDoc->TheBuilding.SelectedAP);
AfxMessageBox("Image Tree Generated");
		pDoc->TheBuilding.SelectedAP = 0;
//		SendMessage(WM_COMMAND, ID_TOOLS_SELECT);
		
		Invalidate(FALSE);

		break;
		
	}	
	
	
	CScrollView::OnLButtonDown(nFlags, point);
}

void CLANPTView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CLANPTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);
	switch(Tool)
	{
	case ID_TOOLS_SELECT:
		if(Captured && Draggable)
		{
			pDoc->TheBuilding.SelectedAP->Position = Convert(point);
			if(abs(point.x - LastPosition.x) < 5 || abs(point.y - LastPosition.y) < 5) Select =false;
//			Invalidate(FALSE);
		}	
		break;
	
	case ID_TOOLS_ACCESSPOINT:

		break;
		
	}	
	
	CScrollView::OnMouseMove(nFlags, point);
}

void CLANPTView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CLANPTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	switch(Tool)
	{
	case ID_TOOLS_SELECT:
		if(Captured && Draggable)
		{
			pDoc->TheBuilding.SelectedAP->Position = Convert(point);
			if(!Select) pDoc->TheBuilding.SelectedAP->Selected = false;
			Invalidate();
		}
		break;
	
	case ID_TOOLS_ACCESSPOINT:
		SendMessage(WM_COMMAND, ID_TOOLS_SELECT);

		break;
		
	}

	Captured = false;
	Select = true;
	
	CScrollView::OnLButtonUp(nFlags, point);
}

void CLANPTView::OnViewGrid() 
{
	// TODO: Add your command handler code here
	CLANPTDoc* pDoc = GetDocument();
	if(pDoc->ShowGrid == 1) pDoc->ShowGrid = 0;
	else pDoc->ShowGrid = 1;
	Invalidate();
	
}

void CLANPTView::OnUpdateViewGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CLANPTDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->ShowGrid == 1);	
}


void CLANPTView::OnEditClear() 
{
	// TODO: Add your command handler code here
	CLANPTDoc* pDoc = GetDocument();
//	pDoc->TheBuilding.RemoveAP();
	Invalidate();

}
