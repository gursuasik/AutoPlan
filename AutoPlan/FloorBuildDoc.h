#if !defined(AFX_FLOORBUILDDOC_H__B0178D9B_0530_46FF_BB24_09F44390FD44__INCLUDED_)
#define AFX_FLOORBUILDDOC_H__B0178D9B_0530_46FF_BB24_09F44390FD44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FloorBuildDoc.h : header file
//
#include "Floor.h"

/////////////////////////////////////////////////////////////////////////////
// CFloorBuildDoc document

class CFloorBuildDoc : public CDocument
{
protected:
	CFloorBuildDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFloorBuildDoc)

// Attributes
public:
	BYTE ShowGrid;
	double GridSize;
	int Scale;
	Vector2d CampusSize;
	Building TheBuilding;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFloorBuildDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFloorBuildDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CFloorBuildDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOORBUILDDOC_H__B0178D9B_0530_46FF_BB24_09F44390FD44__INCLUDED_)
