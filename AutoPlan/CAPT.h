// CAPT.h : main header file for the CAPT application
//


#if !defined(AFX_CAPT_H__F6D90483_9666_4075_9CF1_45333B530564__INCLUDED_)
#define AFX_CAPT_H__F6D90483_9666_4075_9CF1_45333B530564__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "LANPTDoc.h"
#include "LANPTView.h"
#include "FloorBuildDoc.h"
#include "FloorBuildView.h"
#include "MapDoc.h"
#include "MapView.h"

/////////////////////////////////////////////////////////////////////////////
// CCAPTApp:
// See CAPT.cpp for the implementation of this class
//

class CCAPTApp : public CWinApp
{
public:
	CCAPTApp();
	CMultiDocTemplate* MapTemplate;
	void NewMapFile(HMETAFILE HMetaFile, int Scale, Vector2d CampSize);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAPTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCAPTApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPT_H__F6D90483_9666_4075_9CF1_45333B530564__INCLUDED_)
