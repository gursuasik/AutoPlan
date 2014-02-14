// FloorBuilderFrame.cpp : implementation file
//

#include "stdafx.h"
#include "CAPT.h"

#include "MainFrm.h"
#include "FloorBuilderFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFloorBuilderFrame

IMPLEMENT_DYNCREATE(CFloorBuilderFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CFloorBuilderFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CFloorBuilderFrame)
	ON_WM_MDIACTIVATE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CFloorBuilderFrame::CFloorBuilderFrame()
{
	// TODO: add member initialization code here
	
}

CFloorBuilderFrame::~CFloorBuilderFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
// CFloorBuilderFrame message handlers

void CFloorBuilderFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	
	// TODO: Add your message handler code here
	CMainFrame* MainFrame = (CMainFrame*) GetMDIFrame();
	const CRuntimeClass* prt = RUNTIME_CLASS(CFloorBuilderFrame);
	if(pActivateWnd !=0)
	{
		if(pActivateWnd->IsKindOf(prt) && pDeactivateWnd == 0)
			ShowControlBar(&MainFrame->m_wndFloorBuilderBar,true,false);
		else if(pActivateWnd->IsKindOf(prt) && !pDeactivateWnd->IsKindOf(prt))
			ShowControlBar(&MainFrame->m_wndFloorBuilderBar,true,false);
	}
	if(pDeactivateWnd !=0)
	{
		if(pDeactivateWnd->IsKindOf(prt) && pActivateWnd == 0)
			ShowControlBar(&MainFrame->m_wndFloorBuilderBar,false,false);
		else if(pDeactivateWnd->IsKindOf(prt) && !pActivateWnd->IsKindOf(prt))
			ShowControlBar(&MainFrame->m_wndFloorBuilderBar,false,false);
	}
	
}


int CFloorBuilderFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
//	NavBar.Create(this, IDD_NAVBAR,WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, IDD_NAVBAR);
	
	return 0;
}
