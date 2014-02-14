#if !defined(AFX_LANPTVIEW_H__3B6F1B5D_13C8_4531_AFE1_201D76C6AF5E__INCLUDED_)
#define AFX_LANPTVIEW_H__3B6F1B5D_13C8_4531_AFE1_201D76C6AF5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LANPTView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLANPTView view

class CLANPTView : public CScrollView
{
protected:
	CLANPTView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLANPTView)

// Attributes
public:
	UINT Tool;
	bool Draggable;
	bool Select;
	CPoint LastPosition;
	bool Captured;

// Operations
public:
	CLANPTDoc* GetDocument();
	void DrawGrid(CDC* pDC);
	Point2d Convert(CPoint point);
	CPoint Convert(Point2d point);
	void ResetFloorCombo(void);
	void ResetScaleCombo(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLANPTView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLANPTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CLANPTView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	afx_msg void OnEditClear();
	//}}AFX_MSG
	afx_msg void OnFloorChange(void);
	afx_msg void OnScaleChange(void);
	afx_msg void OnTool(UINT nID);
	afx_msg void OnUpdateTool(CCmdUI* pCmdUI);
	afx_msg void OnMap(UINT nID);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANPTVIEW_H__3B6F1B5D_13C8_4531_AFE1_201D76C6AF5E__INCLUDED_)
