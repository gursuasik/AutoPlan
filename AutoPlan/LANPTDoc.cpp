// LANPTDoc.cpp : implementation file
//

#include "stdafx.h"
#include "CAPT.h"
#include "LANPTDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLANPTDoc

IMPLEMENT_DYNCREATE(CLANPTDoc, CDocument)

CLANPTDoc::CLANPTDoc()
{
	ShowGrid = 1;
	GridSize = 0.5;
	Scale = 100;
}

BOOL CLANPTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CFileDialog FileBox(TRUE, "*.bpf",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Building Plan Files (*.bpf)|*.bpf|All Files (*.*)|*.*||");
	FileBox.m_ofn.lpstrTitle = "Import Building from a File";
	if(FileBox.DoModal() != IDOK)
		return FALSE;
	CString FileName = FileBox.GetPathName();
	CFile File(FileName,CFile::modeRead);
	CArchive ar(&File,CArchive::load);
	ar >> ShowGrid >> GridSize >> Scale >> CampusSize.x >> CampusSize.y;
	ar >> TheBuilding;
	TheBuilding.DetermineRooms();
	return TRUE;
}

CLANPTDoc::~CLANPTDoc()
{
}


BEGIN_MESSAGE_MAP(CLANPTDoc, CDocument)
	//{{AFX_MSG_MAP(CLANPTDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLANPTDoc diagnostics

#ifdef _DEBUG
void CLANPTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLANPTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLANPTDoc serialization

void CLANPTDoc::Serialize(CArchive& ar)
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
		ar >> ShowGrid>> GridSize >> Scale >> CampusSize.x >> CampusSize.y;
		ar >> TheBuilding;
		TheBuilding.DetermineRooms();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLANPTDoc commands
