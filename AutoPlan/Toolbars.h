#ifndef TOOLBARS_H
#define TOOLBARS_H

#include "Resource.h"

static UINT BASED_CODE FloorBuilderTools[] =
{
	ID_SEPARATOR,           // for combo box (placeholder)
	ID_SEPARATOR,
	ID_TOOLS_INSERTFLOOR,
	ID_TOOLS_REMOVEFLOOR,
	ID_TOOLS_FLOORPROPERTIES,
	ID_SEPARATOR,
//	ID_TOOLS_SNAPTOCORNER,
//	ID_TOOLS_SNAPTOWALL,
	ID_TOOLS_SNAPTOGRID,
	ID_SEPARATOR,
	ID_TOOLS_SELECT,
	ID_TOOLS_WALL,
	ID_TOOLS_DOOR,
	ID_TOOLS_WINDOW,
	ID_TOOLS_STUD,
//	ID_TOOLS_JOIST,
	ID_SEPARATOR,
	ID_SEPARATOR,
};

class CFloorBuilderBar: public CToolBar
{
public:
	CFloorBuilderBar();
	CComboBox m_ComboFloor;
	CComboBox m_ComboScale;
	virtual ~CFloorBuilderBar();
protected:
	//{{AFX_MSG(CFloorBuilderBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


static UINT BASED_CODE WLANPlanningTools[] =
{
	ID_SEPARATOR,           // for combo box (placeholder)
	ID_SEPARATOR,
	ID_TOOLS_SELECT,
	ID_TOOLS_ACCESSPOINT,
	ID_TOOLS_COVERAGEMAP,
	ID_SEPARATOR,
	ID_SEPARATOR,
};

class CWLANPlanningBar: public CToolBar
{
public:
	CWLANPlanningBar();
	CComboBox m_ComboFloor;
	CComboBox m_ComboScale;
	virtual ~CWLANPlanningBar();
protected:
	//{{AFX_MSG(CWLANPlanningBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

static UINT BASED_CODE MapTools[] =
{
	ID_SEPARATOR,           // for combo box (placeholder)
	ID_SEPARATOR,
	ID_SEPARATOR,
};

class CCoverageMapBar: public CToolBar
{
public:
	CCoverageMapBar();
	CComboBox m_ComboScale;
	virtual ~CCoverageMapBar();
protected:
	//{{AFX_MSG(CCoverageMapBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif