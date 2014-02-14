// CAPT.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CAPT.h"

#include "MainFrm.h"
#include "LANPlanningFrame.h"
#include "FloorBuilderFrame.h"
#include "MapFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCAPTApp

BEGIN_MESSAGE_MAP(CCAPTApp, CWinApp)
	//{{AFX_MSG_MAP(CCAPTApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCAPTApp construction

CCAPTApp::CCAPTApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCAPTApp object

CCAPTApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCAPTApp initialization

BOOL CCAPTApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
//AfxMessageBox("Mark Position 1");
/*	CMultiDocTemplate* pDocTemplate1;
	pDocTemplate1 = new CMultiDocTemplate(
		IDR_WLANPTTYPE,
		RUNTIME_CLASS(CLANPTDoc),
		RUNTIME_CLASS(CLANPlanningFrame), // custom MDI child frame
		RUNTIME_CLASS(CLANPTView));
	AddDocTemplate(pDocTemplate1);
*/
//AfxMessageBox("Mark Position 2");
	CMultiDocTemplate* pDocTemplate2;
	pDocTemplate2 = new CMultiDocTemplate(
		IDR_FLOORBUILDTYPE,
		RUNTIME_CLASS(CFloorBuildDoc),
		RUNTIME_CLASS(CFloorBuilderFrame), // custom MDI child frame
		RUNTIME_CLASS(CFloorBuildView));
	AddDocTemplate(pDocTemplate2);
/*
//AfxMessageBox("Mark Position 3");
	CMultiDocTemplate* pDocTemplate3;
	pDocTemplate3 = new CMultiDocTemplate(
		IDR_COVERAGEMAPTYPE,
		RUNTIME_CLASS(CMapDoc),
		RUNTIME_CLASS(CMapFrame), // custom MDI child frame
		RUNTIME_CLASS(CMapView));
	AddDocTemplate(pDocTemplate3);
	MapTemplate = pDocTemplate3;
*/
// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
//AfxMessageBox("Mark Position 4");

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
//	EnableShellOpen();
//	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
//	CCommandLineInfo cmdInfo;
//	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
//	if (!ProcessShellCommand(cmdInfo))
//		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

//AfxMessageBox("Mark Position 5");
	return TRUE;
}
/*
void CCAPTApp::NewMapFile(HMETAFILE HMetaFile, int Scale, Vector2d CampSize)
{
	CMapDoc* NewMap = (CMapDoc*) MapTemplate->CreateNewDocument();
	CMapFrame* NewFrame;
	NewMap->HMetaFile= HMetaFile;
	NewMap->Scale = Scale;
	NewMap->CampusSize = CampSize;
	NewFrame = (CMapFrame*) MapTemplate->CreateNewFrame(NewMap, NULL);
	MapTemplate->InitialUpdateFrame(NewFrame, NewMap, TRUE);
}
*/
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CCAPTApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCAPTApp message handlers

