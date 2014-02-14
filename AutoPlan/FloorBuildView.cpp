// FloorBuildView.cpp : implementation file
//

#include "stdafx.h"
#include "CAPT.h"
#include "FloorBuildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFloorBuildView

IMPLEMENT_DYNCREATE(CFloorBuildView, CScrollView)

CFloorBuildView::CFloorBuildView()
{
	Snaps = 4;
	Tool = ID_TOOLS_SELECT;
	Captured = FALSE;
	Step = 0;
	WallPen = new CPen(PS_SOLID, 10, RGB(128,128,128));
	ElementPen = new CPen(PS_SOLID, 1, RGB(64,64,64));
	StudPen = new CPen(PS_SOLID, 14, RGB(64,64,64));
	RoomIndex = 0;
}

CFloorBuildView::~CFloorBuildView()
{
	delete WallPen;
	delete ElementPen;
	delete StudPen;
}


BEGIN_MESSAGE_MAP(CFloorBuildView, CScrollView)
	//{{AFX_MSG_MAP(CFloorBuildView)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDW_FLOOR, OnFloorChange)
	ON_CBN_SELCHANGE(IDW_SCALE, OnScaleChange)
	ON_COMMAND(ID_TOOLS_INSERTFLOOR, OnInsertFloor)
	ON_COMMAND(ID_TOOLS_REMOVEFLOOR, OnRemoveFloor)
	ON_COMMAND(ID_TOOLS_FLOORPROPERTIES, OnFloorProperties)
	ON_COMMAND_RANGE(ID_TOOLS_SNAPTOCORNER, ID_TOOLS_SNAPTOGRID, OnSnap)
	ON_UPDATE_COMMAND_UI_RANGE(ID_TOOLS_SNAPTOCORNER, ID_TOOLS_SNAPTOGRID, OnUpdateSnap)
	ON_COMMAND_RANGE(ID_TOOLS_WALL, ID_TOOLS_SELECT, OnTool)
	ON_UPDATE_COMMAND_UI_RANGE(ID_TOOLS_WALL, ID_TOOLS_SELECT, OnUpdateTool)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloorBuildView drawing

void CFloorBuildView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = pDoc->CampusSize.x*pDoc->Scale;
	sizeTotal.cy = pDoc->CampusSize.y*pDoc->Scale;
	SetScrollSizes(MM_LOMETRIC, sizeTotal);
	ResetFloorCombo();
	ResetScaleCombo();
}

void CFloorBuildView::OnDraw(CDC* pDC)
{
	CFloorBuildDoc* pDoc = GetDocument();
	// TODO: add draw code here
// Paint Background
	CSize InnerRectPos = GetScrollPosition();
	CSize InnerRectSize = GetTotalSize();
	pDC->FillSolidRect(InnerRectPos.cx, InnerRectPos.cy, InnerRectSize.cx, -InnerRectSize.cy, RGB(255,255,255));
// Draw Grid
	if(pDoc->ShowGrid == 1)	DrawGrid(pDC);
	pDoc->TheBuilding.Draw(pDC, pDoc->Scale);
	pDoc->TheBuilding.DrawPlan(pDC, pDoc->Scale);
}

/////////////////////////////////////////////////////////////////////////////
// CFloorBuildView diagnostics

#ifdef _DEBUG
void CFloorBuildView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFloorBuildView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFloorBuildDoc* CFloorBuildView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFloorBuildDoc)));
	return (CFloorBuildDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFloorBuildView message handlers

void CFloorBuildView::DrawGrid(CDC *pDC)
{
	ASSERT(pDC !=NULL);
	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();
	int i, j;
	int x= pDoc->CampusSize.x*pDoc->Scale, y = pDoc->CampusSize.y*pDoc->Scale;
	int dx = pDoc->GridSize*pDoc->Scale, dy = pDoc->GridSize*pDoc->Scale;
	for(i=0; i<= x; i+=dx)
		for(j=0; j<= y; j+=dy)
			pDC->SetPixel(i,-j,RGB(0,0,0));

}

Point2d CFloorBuildView::Convert(CPoint point)
{
	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();
	return Point2d((double) point.x/pDoc->Scale, (double) point.y/pDoc->Scale);
}

CPoint CFloorBuildView::Convert(Point2d point)
{
	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();
	return CPoint(point.x*pDoc->Scale, point.y*pDoc->Scale);
}

Point2d CFloorBuildView::Snap(CPoint point, bool ExcludeCurrent)
{
	int x, y;
	bool Snaped = false;
	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();
	Point2d temp, temp2d, closest;
	UINT MaskedSnap;
	x = point.x;
	y = point.y;

	MaskedSnap = Snaps;
	MaskedSnap&= 4;
	if(MaskedSnap != 0)
	{
		double xd, yd;
		double d = pDoc->Scale*pDoc->GridSize;
		if(x - ((int) (x/d))*d < d/2) xd = ((int) (x/d))*d;
		else xd = ((int) (x/d) + 1)*d;
		if(y - ((int) (y/d))*d > -d/2) yd = ((int) (y/d))*d;
		else yd = ((int) (y/d) - 1)*d;
		closest = Point2d(xd,yd);
		Snaped = true;
	}

	MaskedSnap = Snaps;
	MaskedSnap&= 2;
	if(MaskedSnap != 0)
	{
		temp2d = pDoc->TheBuilding.Snap(Convert(point), false, false, ExcludeCurrent);
		temp = pDoc->Scale*temp2d;
		if((temp.x - x)*(temp.x - x) + (temp.y - y)*(temp.y - y) < (closest.x - x)*(closest.x - x) + (closest.y - y)*(closest.y - y))
			closest = temp;
		Snaped = true;
	}
	
	MaskedSnap = Snaps;
	MaskedSnap&= 1;
	if(MaskedSnap != 0)
	{
	}

	if(!Snaped || (closest.x - x)*(closest.x - x) + (closest.y - y)*(closest.y - y) > 10000)
		return Convert(point);
	return closest/pDoc->Scale;
}

void CFloorBuildView::ResetFloorCombo(void)
{
	CMainFrame* ParentFrame = (CMainFrame*) ((CMDIChildWnd*) GetParentFrame())->GetMDIFrame();
	ParentFrame->m_wndFloorBuilderBar.m_ComboFloor.ResetContent();
	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();
	int SelNo, i, n;
	char names[200][16];
	n = pDoc->TheBuilding.GetFloorCount();
	SelNo = pDoc->TheBuilding.GetSelected();
	pDoc->TheBuilding.GetFloorNames(names);
	for(i = 0; i < n; i++) 
		ParentFrame->m_wndFloorBuilderBar.m_ComboFloor.AddString(names[i]);
	ParentFrame->m_wndFloorBuilderBar.m_ComboFloor.SetCurSel(SelNo);

}

void CFloorBuildView::OnFloorChange(void)
{
	CMainFrame* ParentFrame = (CMainFrame*) ((CMDIChildWnd*) GetParentFrame())->GetMDIFrame();
	int SelNo = ParentFrame->m_wndFloorBuilderBar.m_ComboFloor.GetCurSel();
	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();
	pDoc->TheBuilding.SetSelected(SelNo);
	Invalidate(TRUE);
}

void CFloorBuildView::OnInsertFloor(UINT nID)
{
	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();
	char name[] = "Floor", no[4];
	int count = pDoc->TheBuilding.GetFloorCount();
	itoa(++count,no,10);
	strcat(name,no);
	pDoc->TheBuilding.AddFloor(name);
	ResetFloorCombo();
	Invalidate(TRUE);
}

void CFloorBuildView::OnRemoveFloor(UINT nID)
{
	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();
	pDoc->TheBuilding.RemoveFloor();
	ResetFloorCombo();
	Invalidate(TRUE);
}

void CFloorBuildView::OnFloorProperties(UINT nID)
{
	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();
	pDoc->TheBuilding.DetermineRooms();
//	AfxMessageBox("Mark 1");
	pDoc->TheBuilding.DeterminePlanElements();
//	AfxMessageBox("Mark 2");
	pDoc->TheBuilding.DeterminePlanConnections();
//	AfxMessageBox("Mark 2");
	Step = 1;
	Invalidate(TRUE);
}

void CFloorBuildView::ResetScaleCombo(void)
{
	CMainFrame* ParentFrame = (CMainFrame*) ((CMDIChildWnd*) GetParentFrame())->GetMDIFrame();
	ParentFrame->m_wndFloorBuilderBar.m_ComboScale.ResetContent();
	CFloorBuildDoc* pDoc = GetDocument();
	int i;
	char names[5][6] = {{'1','/','2','5'}, {'1','/','5','0'}, {'1','/','1','0','0'}} ;

	for(i = 0; i < 3; i++) 
		ParentFrame->m_wndFloorBuilderBar.m_ComboScale.AddString(names[i]);
	ParentFrame->m_wndFloorBuilderBar.m_ComboScale.SetCurSel(1);

}

void CFloorBuildView::OnScaleChange(void)
{
	CFloorBuildDoc* pDoc = GetDocument();
	CMainFrame* ParentFrame = (CMainFrame*) ((CMDIChildWnd*) GetParentFrame())->GetMDIFrame();
	int SelNo = ParentFrame->m_wndFloorBuilderBar.m_ComboScale.GetCurSel();
	
	switch(SelNo)
	{
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

void CFloorBuildView::OnSnap(UINT nID)
{
	Snaps^= (UINT) pow(2, nID - ID_TOOLS_SNAPTOCORNER);
}

void CFloorBuildView::OnUpdateSnap(CCmdUI* pCmdUI)
{
	UINT MaskedSnap = Snaps;
	MaskedSnap&= (UINT) pow(2, pCmdUI->m_nID - ID_TOOLS_SNAPTOCORNER);
	pCmdUI->SetCheck(MaskedSnap != 0);
}

void CFloorBuildView::OnTool(UINT nID)
{
	Tool = nID;
}

void CFloorBuildView::OnUpdateTool(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == Tool);
}

BOOL CFloorBuildView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	return CScrollView::OnEraseBkgnd(pDC);
	CBrush bri( RGB(128,128,128) );
	FillOutsideRect( pDC, &bri );
	return TRUE;
	
	return CScrollView::OnEraseBkgnd(pDC);
}

void CFloorBuildView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();
	Captured = true;
	SetCapture();

	switch(Tool)
	{
	case ID_TOOLS_SELECT:
		FirstPoint = Snap(point);

		break;
	
	case ID_TOOLS_WALL:
		FirstPoint = Snap(point);
		pDoc->TheBuilding.AddWall();
		pDoc->TheBuilding.SetWall(FirstPoint,FirstPoint);
		TrialWall = pDoc->TheBuilding.GetSelectedWallCopy();

		break;
	
	case ID_TOOLS_DOOR:
		FirstPoint = pDoc->TheBuilding.Snap(Convert(point), false, true);
		TrialWall = pDoc->TheBuilding.GetSelectedWallCopy();
		pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
		pDoc->TheBuilding.AddDoor();
		pDoc->TheBuilding.SetDoor(FirstPoint,FirstPoint);
		pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
		TrialWallElement = pDoc->TheBuilding.GetSelectedElementCopy();
		TrialWall->AddPatch(TrialWallElement);

		break;
	
	case ID_TOOLS_WINDOW:
		FirstPoint = pDoc->TheBuilding.Snap(Convert(point), false, true);
		TrialWall = pDoc->TheBuilding.GetSelectedWallCopy();
		pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
		pDoc->TheBuilding.AddWindow();
		pDoc->TheBuilding.SetWindow(FirstPoint,FirstPoint);
		pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
		TrialWallElement = pDoc->TheBuilding.GetSelectedElementCopy();
		TrialWall->AddPatch(TrialWallElement);

		break;

	case ID_TOOLS_STUD:
		FirstPoint = pDoc->TheBuilding.Snap(Convert(point), false, true);
		TrialWall = pDoc->TheBuilding.GetSelectedWallCopy();
		pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
		pDoc->TheBuilding.AddStud();
		pDoc->TheBuilding.SetStud(FirstPoint,FirstPoint);
		pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
		TrialWallElement = pDoc->TheBuilding.GetSelectedElementCopy();
		TrialWall->AddPatch(TrialWallElement);

		break;
	
	case ID_TOOLS_JOIST:

		break;

	}	
	TemporaryPoint = FirstPoint;

	CScrollView::OnLButtonDown(nFlags, point);
}

void CFloorBuildView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);

	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();

	switch(Tool)
	{
	case ID_TOOLS_SELECT:
		if(Captured)
		{
//			OverDrawSelectRect(&dc, Convert(FirstPoint), point);
//			OverDrawSelectRect(&dc, Convert(FirstPoint), Convert(TemporaryPoint));
		}
		break;

	case ID_TOOLS_WALL:
		if(Captured)
		{
			DrawMode = dc.SetROP2(R2_NOTXORPEN);
			TrialWall->Draw(&dc,pDoc->Scale,WallPen, ElementPen, StudPen);
			TrialWall->SetPosition(FirstPoint, Snap(point, true));
			TrialWall->Draw(&dc,pDoc->Scale,WallPen, ElementPen, StudPen);
		}

		break;

	case ID_TOOLS_DOOR:
		if(Captured)
		{
			DrawMode = dc.SetROP2(R2_NOTXORPEN);
			TrialWall->Draw(&dc,pDoc->Scale,WallPen, ElementPen, StudPen);
			TrialWallElement->SetPosition(FirstPoint, pDoc->TheBuilding.Snap(Convert(point), true));
			TrialWall->Draw(&dc,pDoc->Scale,WallPen, ElementPen, StudPen);
		}

		break;

	case ID_TOOLS_WINDOW:
		if(Captured)
		{
			DrawMode = dc.SetROP2(R2_NOTXORPEN);
			TrialWall->Draw(&dc,pDoc->Scale,WallPen, ElementPen, StudPen);
			TrialWallElement->SetPosition(FirstPoint, pDoc->TheBuilding.Snap(Convert(point), true));
			TrialWall->Draw(&dc,pDoc->Scale,WallPen, ElementPen, StudPen);
		}

		break;

	case ID_TOOLS_STUD:
		if(Captured)
		{
			DrawMode = dc.SetROP2(R2_NOTXORPEN);
			TrialWall->Draw(&dc,pDoc->Scale,WallPen, ElementPen, StudPen);
			TrialWallElement->SetPosition(FirstPoint, pDoc->TheBuilding.Snap(Convert(point), true));
			TrialWall->Draw(&dc,pDoc->Scale,WallPen, ElementPen, StudPen);
		}

		break;

	}
	TemporaryPoint = Snap(point);

	
	CScrollView::OnMouseMove(nFlags, point);
}

void CFloorBuildView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.DPtoLP(&point);


	CFloorBuildDoc* pDoc = (CFloorBuildDoc*) GetDocument();

	switch(Tool)
	{
	case ID_TOOLS_SELECT:
		if(Captured)
		{
//			OverDrawSelectRect(&dc, Convert(FirstPoint), point);
//			OverDrawSelectRect(&dc, Convert(FirstPoint), Convert(TemporaryPoint));
		}
		break;

	case ID_TOOLS_WALL:
		if(Captured)
		{
			pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
			pDoc->TheBuilding.SetWall(FirstPoint,Snap(point, true));
			pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
			dc.SetROP2(DrawMode);
		}
		Invalidate(TRUE);
		break;

	case ID_TOOLS_DOOR:
		if(Captured)
		{
			pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
			pDoc->TheBuilding.SetDoor(FirstPoint, pDoc->TheBuilding.Snap(Convert(point), true));
			pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
			dc.SetROP2(DrawMode);
		}
		Invalidate(TRUE);

		break;

	case ID_TOOLS_WINDOW:
		if(Captured)
		{
			pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
			pDoc->TheBuilding.SetWindow(FirstPoint, pDoc->TheBuilding.Snap(Convert(point), true));
			pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
			dc.SetROP2(DrawMode);
		}
		Invalidate(TRUE);

		break;

	case ID_TOOLS_STUD:
		if(Captured)
		{
			pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
			pDoc->TheBuilding.SetStud(FirstPoint, pDoc->TheBuilding.Snap(Convert(point), true));
			pDoc->TheBuilding.DrawWall(&dc, pDoc->Scale, TRUE);
			dc.SetROP2(DrawMode);
		}
		Invalidate(TRUE);
		break;

	}
	Captured = false;
	ReleaseCapture();
	CScrollView::OnLButtonUp(nFlags, point);
}

void CFloorBuildView::OnViewGrid() 
{
	// TODO: Add your command handler code here
	CFloorBuildDoc* pDoc = GetDocument();
	if(pDoc->ShowGrid == 1) pDoc->ShowGrid = 0;
	else pDoc->ShowGrid = 1;
	Invalidate();
	
}

void CFloorBuildView::OnUpdateViewGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CFloorBuildDoc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->ShowGrid == 1);	
	
}
