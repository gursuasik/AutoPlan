#if !defined(AFX_FLOORBUILDERFRAME_H__D93A61CA_ACEA_4010_A7D0_CE0BA4E0A3AA__INCLUDED_)
#define AFX_FLOORBUILDERFRAME_H__D93A61CA_ACEA_4010_A7D0_CE0BA4E0A3AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FloorBuilderFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFloorBuilderFrame frame

class CFloorBuilderFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CFloorBuilderFrame)
protected:
	CFloorBuilderFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CDialogBar NavBar;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFloorBuilderFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFloorBuilderFrame();

	// Generated message map functions
	//{{AFX_MSG(CFloorBuilderFrame)
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOORBUILDERFRAME_H__D93A61CA_ACEA_4010_A7D0_CE0BA4E0A3AA__INCLUDED_)
