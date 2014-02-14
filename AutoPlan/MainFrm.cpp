// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CAPT.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
	m_bShowFloorBuilderBar = FALSE;
	m_bShowWLANPlanningBar = FALSE;	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
// Standart Toolbar Generation
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

// Statusbar Generation
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	CRect rect;
	const int nDropHeight = 100;
// FloorBuilderBar Generation
	if (!m_wndFloorBuilderBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndFloorBuilderBar.LoadBitmap(IDB_FLOORBUILDER) ||
		!m_wndFloorBuilderBar.SetButtons(FloorBuilderTools, sizeof(FloorBuilderTools)/sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndFloorBuilderBar.SetButtonInfo(0, IDW_FLOOR, TBBS_SEPARATOR, 72);
	m_wndFloorBuilderBar.GetItemRect(0, &rect);
	rect.top = 0;
	rect.bottom = rect.top + nDropHeight;
	if (!m_wndFloorBuilderBar.m_ComboFloor.Create(
			CBS_DROPDOWNLIST | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | WS_HSCROLL,
			rect, &m_wndFloorBuilderBar, IDW_FLOOR))
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}

	m_wndFloorBuilderBar.SetButtonInfo(14, IDW_SCALE, TBBS_SEPARATOR, 72);
	m_wndFloorBuilderBar.GetItemRect(14, &rect);
	rect.top = 0;
	rect.bottom = rect.top + nDropHeight;
	if (!m_wndFloorBuilderBar.m_ComboScale.Create(
			CBS_DROPDOWNLIST | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | WS_HSCROLL,
			rect, &m_wndFloorBuilderBar, IDW_SCALE))
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}
/*
// WLANPlanningBar Generation
	if (!m_wndWLANPlanningBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndWLANPlanningBar.LoadBitmap(IDB_WLANPLANNING) ||
		!m_wndWLANPlanningBar.SetButtons(WLANPlanningTools, sizeof(WLANPlanningTools)/sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndWLANPlanningBar.SetButtonInfo(0, IDW_FLOOR, TBBS_SEPARATOR, 72);
	m_wndWLANPlanningBar.GetItemRect(0, &rect);
	rect.top = 0;
	rect.bottom = rect.top + nDropHeight;
	if (!m_wndWLANPlanningBar.m_ComboFloor.Create(
			CBS_DROPDOWNLIST | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | WS_HSCROLL,
			rect, &m_wndWLANPlanningBar, IDW_FLOOR))
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}
	
	m_wndWLANPlanningBar.SetButtonInfo(6, IDW_SCALE, TBBS_SEPARATOR, 72);
	m_wndWLANPlanningBar.GetItemRect(6, &rect);
	rect.top = 0;
	rect.bottom = rect.top + nDropHeight;
	if (!m_wndWLANPlanningBar.m_ComboScale.Create(
			CBS_DROPDOWNLIST | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | WS_HSCROLL,
			rect, &m_wndWLANPlanningBar, IDW_SCALE))
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}

// CoverageMapBar Generation
	if (!m_wndCoverageMapBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndCoverageMapBar.LoadBitmap(IDB_COVERAGEMAP) ||
		!m_wndCoverageMapBar.SetButtons(MapTools, sizeof(MapTools)/sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndCoverageMapBar.SetButtonInfo(0, IDW_SCALE, TBBS_SEPARATOR, 72);
	m_wndCoverageMapBar.GetItemRect(0, &rect);
	rect.top = 0;
	rect.bottom = rect.top + nDropHeight;
	if (!m_wndCoverageMapBar.m_ComboScale.Create(
			CBS_DROPDOWNLIST | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | WS_HSCROLL,
			rect, &m_wndCoverageMapBar, IDW_SCALE))
	{
		TRACE0("Failed to create combo-box\n");
		return FALSE;
	}
*/	
// TODO: Delete these three lines if you don't want the toolbar to
//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFloorBuilderBar.EnableDocking(CBRS_ALIGN_ANY);
//	m_wndWLANPlanningBar.EnableDocking(CBRS_ALIGN_ANY);
//	m_wndCoverageMapBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndFloorBuilderBar);
//	DockControlBar(&m_wndWLANPlanningBar);
//	DockControlBar(&m_wndCoverageMapBar);
	ShowControlBar(&m_wndFloorBuilderBar,m_bShowFloorBuilderBar,false);
//	ShowControlBar(&m_wndWLANPlanningBar,m_bShowWLANPlanningBar,false);
//	ShowControlBar(&m_wndCoverageMapBar,FALSE,false);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

