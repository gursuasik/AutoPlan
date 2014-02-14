// LANPlanningFrame.cpp : implementation file
//

#include "stdafx.h"
#include "CAPT.h"
#include "LANPlanningFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLANPlanningFrame

IMPLEMENT_DYNCREATE(CLANPlanningFrame, CMDIChildWnd)

CLANPlanningFrame::CLANPlanningFrame()
{
}

CLANPlanningFrame::~CLANPlanningFrame()
{
}


BEGIN_MESSAGE_MAP(CLANPlanningFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CLANPlanningFrame)
	ON_WM_MDIACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLANPlanningFrame message handlers

void CLANPlanningFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	
	// TODO: Add your message handler code here
	CMainFrame* MainFrame = (CMainFrame*) GetMDIFrame();
	const CRuntimeClass* prt = RUNTIME_CLASS(CLANPlanningFrame);
	if(pActivateWnd !=0)
	{
		if(pActivateWnd->IsKindOf(prt) && pDeactivateWnd == 0)
			ShowControlBar(&MainFrame->m_wndWLANPlanningBar,true,false);
		else if(pActivateWnd->IsKindOf(prt) && !pDeactivateWnd->IsKindOf(prt))
			ShowControlBar(&MainFrame->m_wndWLANPlanningBar,true,false);
	}
	if(pDeactivateWnd !=0)
	{
		if(pDeactivateWnd->IsKindOf(prt) && pActivateWnd == 0)
			ShowControlBar(&MainFrame->m_wndWLANPlanningBar,false,false);
		else if(pDeactivateWnd->IsKindOf(prt) && !pActivateWnd->IsKindOf(prt))
			ShowControlBar(&MainFrame->m_wndWLANPlanningBar,false,false);
	}
	
}
