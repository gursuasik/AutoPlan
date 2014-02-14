// FloorBuildDoc.cpp : implementation file
//

#include "stdafx.h"
#include "CAPT.h"
#include "FloorBuildDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFloorBuildDoc

IMPLEMENT_DYNCREATE(CFloorBuildDoc, CDocument)

CFloorBuildDoc::CFloorBuildDoc()
{
	ShowGrid = 1;
	GridSize = 0.5;
	Scale = 200;
	CampusSize = Vector2d(30,20);
}

BOOL CFloorBuildDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	TheBuilding.GenerateDefault();
	return TRUE;
}

CFloorBuildDoc::~CFloorBuildDoc()
{
}


BEGIN_MESSAGE_MAP(CFloorBuildDoc, CDocument)
	//{{AFX_MSG_MAP(CFloorBuildDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloorBuildDoc diagnostics

#ifdef _DEBUG
void CFloorBuildDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFloorBuildDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFloorBuildDoc serialization

void CFloorBuildDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << ShowGrid << GridSize << Scale << CampusSize.x << CampusSize.y;
		ar << TheBuilding;
	}
	else
	{
		// TODO: add loading code here
		ar >> ShowGrid >> GridSize >> Scale >> CampusSize.x >> CampusSize.y;
		ar >> TheBuilding;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFloorBuildDoc commands
