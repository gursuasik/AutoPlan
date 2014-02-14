// MapDoc.cpp : implementation file
//

#include "stdafx.h"
#include "CAPT.h"
#include "MapDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapDoc

IMPLEMENT_DYNCREATE(CMapDoc, CDocument)

CMapDoc::CMapDoc()
{
}

BOOL CMapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CMapDoc::~CMapDoc()
{
	DeleteMetaFile(HMetaFile);
}


BEGIN_MESSAGE_MAP(CMapDoc, CDocument)
	//{{AFX_MSG_MAP(CMapDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapDoc diagnostics

#ifdef _DEBUG
void CMapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapDoc serialization

void CMapDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapDoc commands
