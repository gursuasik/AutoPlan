; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFloorBuilderFrame
LastTemplate=CMDIChildWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CAPT.h"
LastPage=0

ClassCount=17
Class1=CCAPTApp
Class2=CCAPTDoc
Class3=CCAPTView
Class4=CMainFrame

ResourceCount=10
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_WLANPTTYPE
Resource4=IDR_WLANPTTYPE (English (U.S.))
Resource5=IDD_ABOUTBOX (English (U.S.))
Class5=CChildFrame
Class6=CAboutDlg
Class7=CFloorBuildView
Class8=CFloorBuildDoc
Resource6=IDD_MAPBAR (English (U.S.))
Class9=CFloorBuilderFrame
Class10=CLANPTView
Class11=CLANPTDoc
Class12=CLANPlanningFrame
Class13=CCoverageMapDoc
Class14=CoverageMapView
Class15=CMapDoc
Class16=CMapView
Class17=CMapFrame
Resource7=IDD_DIALOGBAR1 (English (U.S.))
Resource8=IDR_FLOORBUILDTYPE (English (U.S.))
Resource9=IDR_MAINFRAME (English (U.S.))
Resource10=IDD_NAVBAR (English (U.S.))

[CLS:CCAPTApp]
Type=0
HeaderFile=CAPT.h
ImplementationFile=CAPT.cpp
Filter=N
LastObject=CCAPTApp

[CLS:CCAPTDoc]
Type=0
HeaderFile=CAPTDoc.h
ImplementationFile=CAPTDoc.cpp
Filter=N

[CLS:CCAPTView]
Type=0
HeaderFile=CAPTView.h
ImplementationFile=CAPTView.cpp
Filter=C
LastObject=CCAPTView
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=CAPT.cpp
ImplementationFile=CAPT.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
CommandCount=8
Command8=ID_APP_ABOUT

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_WLANPTTYPE]
Type=1
Class=CCAPTView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
CommandCount=21
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_WLANPTTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_CLEAR
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_VIEW_GRID
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_APP_ABOUT
CommandCount=23

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CLEAR
Command9=ID_EDIT_CUT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CFloorBuildView]
Type=0
HeaderFile=FloorBuildView.h
ImplementationFile=FloorBuildView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC
LastObject=CFloorBuildView

[CLS:CFloorBuildDoc]
Type=0
HeaderFile=FloorBuildDoc.h
ImplementationFile=FloorBuildDoc.cpp
BaseClass=CDocument
Filter=N

[MNU:IDR_FLOORBUILDTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_VIEW_GRID
Command18=ID_WINDOW_NEW
Command19=ID_WINDOW_CASCADE
Command20=ID_WINDOW_TILE_HORZ
Command21=ID_WINDOW_ARRANGE
Command22=ID_APP_ABOUT
CommandCount=22

[CLS:CFloorBuilderFrame]
Type=0
HeaderFile=FloorBuilderFrame.h
ImplementationFile=FloorBuilderFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
VirtualFilter=mfWC
LastObject=CFloorBuilderFrame

[CLS:CLANPTView]
Type=0
HeaderFile=LANPTView.h
ImplementationFile=LANPTView.cpp
BaseClass=CScrollView
Filter=C
LastObject=CLANPTView
VirtualFilter=VWC

[CLS:CLANPTDoc]
Type=0
HeaderFile=LANPTDoc.h
ImplementationFile=LANPTDoc.cpp
BaseClass=CDocument
Filter=N

[CLS:CLANPlanningFrame]
Type=0
HeaderFile=LANPlanningFrame.h
ImplementationFile=LANPlanningFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
VirtualFilter=mfWC
LastObject=ID_VIEW_GRID

[CLS:CCoverageMapDoc]
Type=0
HeaderFile=CoverageMapDoc.h
ImplementationFile=CoverageMapDoc.cpp
BaseClass=CDocument
Filter=N

[CLS:CoverageMapView]
Type=0
HeaderFile=overageMapView.h
ImplementationFile=overageMapView.cpp
BaseClass=CScrollView
Filter=C
LastObject=CoverageMapView

[CLS:CMapDoc]
Type=0
HeaderFile=MapDoc.h
ImplementationFile=MapDoc.cpp
BaseClass=CDocument
Filter=N

[CLS:CMapView]
Type=0
HeaderFile=MapView.h
ImplementationFile=MapView.cpp
BaseClass=CScrollView
Filter=C
VirtualFilter=VWC
LastObject=CMapView

[CLS:CMapFrame]
Type=0
HeaderFile=MapFrame.h
ImplementationFile=MapFrame.cpp
BaseClass=CMDIChildWnd
Filter=M
VirtualFilter=mfWC
LastObject=CMapFrame

[DLG:IDD_DIALOGBAR1 (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_MAPBAR (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_IMAGE1,{4C599241-6926-101B-9992-00000B65C6F9},1342177280

[DLG:IDD_NAVBAR (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDOK,button,1342243585

