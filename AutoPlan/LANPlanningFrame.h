#if !defined(AFX_LANPLANNINGFRAME_H__94C176C1_E93D_437D_AC46_BEAF0C5B8FE5__INCLUDED_)
#define AFX_LANPLANNINGFRAME_H__94C176C1_E93D_437D_AC46_BEAF0C5B8FE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LANPlanningFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLANPlanningFrame frame

class CLANPlanningFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CLANPlanningFrame)
protected:
	CLANPlanningFrame();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLANPlanningFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLANPlanningFrame();

	// Generated message map functions
	//{{AFX_MSG(CLANPlanningFrame)
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANPLANNINGFRAME_H__94C176C1_E93D_437D_AC46_BEAF0C5B8FE5__INCLUDED_)
