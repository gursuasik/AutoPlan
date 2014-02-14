#if !defined(AFX_MAPFRAME_H__89F791F0_4637_48C6_9B1C_0C5C0E17994D__INCLUDED_)
#define AFX_MAPFRAME_H__89F791F0_4637_48C6_9B1C_0C5C0E17994D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapFrame frame

class CMapFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMapFrame)
protected:
	CMapFrame();           // protected constructor used by dynamic creation

// Attributes
public:
	CDialogBar MapBar;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMapFrame();

	// Generated message map functions
	//{{AFX_MSG(CMapFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPFRAME_H__89F791F0_4637_48C6_9B1C_0C5C0E17994D__INCLUDED_)
