// MapFrame.cpp : implementation file
//

#include "stdafx.h"
#include "CAPT.h"
#include "MapFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapFrame

IMPLEMENT_DYNCREATE(CMapFrame, CMDIChildWnd)

CMapFrame::CMapFrame()
{
}

CMapFrame::~CMapFrame()
{
}


BEGIN_MESSAGE_MAP(CMapFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CMapFrame)
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapFrame message handlers

int CMapFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	MapBar.Create(this, IDD_MAPBAR,WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, IDD_MAPBAR);
	return 0;
}

void CMapFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	CMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	
	// TODO: Add your message handler code here
	CMainFrame* MainFrame = (CMainFrame*) GetMDIFrame();
	const CRuntimeClass* prt = RUNTIME_CLASS(CMapFrame);
	if(pActivateWnd !=0)
	{
		if(pActivateWnd->IsKindOf(prt) && pDeactivateWnd == 0)
			ShowControlBar(&MainFrame->m_wndCoverageMapBar,true,false);
		else if(pActivateWnd->IsKindOf(prt) && !pDeactivateWnd->IsKindOf(prt))
			ShowControlBar(&MainFrame->m_wndCoverageMapBar,true,false);
	}
	if(pDeactivateWnd !=0)
	{
		if(pDeactivateWnd->IsKindOf(prt) && pActivateWnd == 0)
			ShowControlBar(&MainFrame->m_wndCoverageMapBar,false,false);
		else if(pDeactivateWnd->IsKindOf(prt) && !pActivateWnd->IsKindOf(prt))
			ShowControlBar(&MainFrame->m_wndCoverageMapBar,false,false);
	}
	
}
