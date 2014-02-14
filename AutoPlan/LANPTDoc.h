#if !defined(AFX_LANPTDOC_H__DA71441E_317D_48BF_A729_CD7BDB57AA9D__INCLUDED_)
#define AFX_LANPTDOC_H__DA71441E_317D_48BF_A729_CD7BDB57AA9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LANPTDoc.h : header file
//
#include "Floor.h"

/////////////////////////////////////////////////////////////////////////////
// CLANPTDoc document

class CLANPTDoc : public CDocument
{
protected:
	CLANPTDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLANPTDoc)

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
	//{{AFX_VIRTUAL(CLANPTDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLANPTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLANPTDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANPTDOC_H__DA71441E_317D_48BF_A729_CD7BDB57AA9D__INCLUDED_)
