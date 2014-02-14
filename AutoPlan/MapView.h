#if !defined(AFX_MAPVIEW_H__4A9CA6E8_00C8_464B_89B5_38EFDFF6547A__INCLUDED_)
#define AFX_MAPVIEW_H__4A9CA6E8_00C8_464B_89B5_38EFDFF6547A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapView view

class CMapView : public CScrollView
{
protected:
	CMapView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMapView)

// Attributes
public:

// Operations
public:
	CMapDoc* GetDocument();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMapView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPVIEW_H__4A9CA6E8_00C8_464B_89B5_38EFDFF6547A__INCLUDED_)
