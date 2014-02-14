#if !defined(AFX_FLOORBUILDVIEW_H__3C60A45A_0C59_4FCD_9125_3CA97C1F6F2E__INCLUDED_)
#define AFX_FLOORBUILDVIEW_H__3C60A45A_0C59_4FCD_9125_3CA97C1F6F2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FloorBuildView.h : header file
//
#include "FloorBuildDoc.h"
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CFloorBuildView view

class CFloorBuildView : public CScrollView
{
protected:
	CFloorBuildView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFloorBuildView)

// Attributes
public:
	UINT Snaps;
	UINT Tool;
	BOOL Captured;
	Point2d FirstPoint, TemporaryPoint;
	PlaneWall* TrialWall;
	PlaneWallElement* TrialWallElement;
	int Step;
	int DrawMode, RoomIndex;
	CPen *WallPen, *ElementPen, *StudPen;
	CFloorBuildDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFloorBuildView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DrawGrid(CDC* pDC);
	Point2d Convert(CPoint point);
	CPoint Convert(Point2d point);
	Point2d Snap(CPoint point, bool ExcludeCurrent = false);
	void ResetFloorCombo(void);
	void ResetScaleCombo(void);
	virtual ~CFloorBuildView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFloorBuildView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnFloorChange(void);
	afx_msg void OnInsertFloor(UINT nID);
	afx_msg void OnRemoveFloor(UINT nID);
	afx_msg void OnFloorProperties(UINT nID);
	afx_msg void OnScaleChange(void);
	afx_msg void OnSnap(UINT nID);
	afx_msg void OnUpdateSnap(CCmdUI* pCmdUI);
	afx_msg void OnTool(UINT nID);
	afx_msg void OnUpdateTool(CCmdUI* pCmdUI);
	afx_msg void OnMap(UINT nID);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FloorBuildView.cpp
inline CFloorBuildDoc* CFloorBuildView::GetDocument()
   { return (CFloorBuildDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOORBUILDVIEW_H__3C60A45A_0C59_4FCD_9125_3CA97C1F6F2E__INCLUDED_)
