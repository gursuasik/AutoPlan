// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "CAPT.h"

#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_MDIACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	
/*	// TODO: Add your message handler code here
	CMainFrame* MainFrame = (CMainFrame*) GetMDIFrame();
	const CRuntimeClass* prt = RUNTIME_CLASS(CChildFrame);
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
*/		
}
