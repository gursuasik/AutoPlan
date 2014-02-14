#if !defined(AFX_MAPDOC_H__EE7013C3_BE82_42E2_8C82_CC8A65B7A2FC__INCLUDED_)
#define AFX_MAPDOC_H__EE7013C3_BE82_42E2_8C82_CC8A65B7A2FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapDoc document

class CMapDoc : public CDocument
{
protected:
	CMapDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMapDoc)

// Attributes
public:
	int Scale;
	Vector2d CampusSize;
	HMETAFILE HMetaFile;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMapDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPDOC_H__EE7013C3_BE82_42E2_8C82_CC8A65B7A2FC__INCLUDED_)
