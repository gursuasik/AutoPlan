#if !defined(BUILDING_H)
#define BUILDING_H

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <list>
#include <queue>
//#include <vector>
//#include <map>

#include "_3dSpace.h"

using namespace std;


class PlaneWallElement: public VerticalRect {

protected:
	double Offset;
	bool Splitable;

public:
	double Attenuation;
	double TransmitCoeff;
	double ReflectCoeff;
	double Thickness;
	bool Selected;
	bool IsSplitable(void) {return Splitable;}
	virtual PlaneWallElement* GetDraftCopy(void) = 0;
	virtual int GetElementType(void) = 0;

//	MFC Compatibles Only
	virtual void Draw(CDC* pDC, int Scale) = 0;	
	virtual CArchive& Store(CArchive& ar);
};


class PlaneWindow: public PlaneWallElement {
	
public:
	PlaneWindow() {Splitable = false;}
	PlaneWindow(Point P, Vector2d D, double H) {TransmitCoeff = 1; ReflectCoeff = 0; Splitable = false; SetRectangle(P, D, H);}
	PlaneWallElement* GetDraftCopy(void) {return (PlaneWallElement*) new PlaneWindow(p,d,h);}
	virtual int GetElementType(void) {return 1;}

//	MFC Compatibles Only
	void Draw(CDC* pDC, int Scale);
	CArchive& Store(CArchive& ar);
};


class PlaneDoor: public PlaneWallElement {

public:
	bool Clockwise;
	PlaneDoor() {Splitable = false; Clockwise = true;}
	PlaneDoor(Point P, Vector2d D, double H) {TransmitCoeff = 0.8; ReflectCoeff = 0.3; Splitable = false; SetRectangle(P, D, H);}
	PlaneWallElement* GetDraftCopy(void) {return (PlaneWallElement*) new PlaneDoor(p,d,h);}
	virtual int GetElementType(void) {return 0;}

//	MFC Compatibles Only
	void Draw(CDC* pDC, int Scale);
	CArchive& Store(CArchive& ar);
};


class PlaneStud: public PlaneWallElement {

public:
	PlaneStud() {Splitable = false;}
	PlaneStud(Point P, Vector2d D, double H) {TransmitCoeff = 0.0555; ReflectCoeff = 0.3; Splitable = false; SetRectangle(P, D, H);}
	PlaneWallElement* GetDraftCopy(void) {return (PlaneWallElement*) new PlaneStud(p,d,h);}
	virtual int GetElementType(void) {return 2;}

//	MFC Compatibles Only
	void Draw(CDC* pDC, int Scale);
	CArchive& Store(CArchive& ar);
};


class PlaneJoist: public PlaneWallElement {

public:
	PlaneJoist() {Splitable = false;}
	PlaneJoist(Point P, Vector2d D, double H) {TransmitCoeff = 0.0555; ReflectCoeff = 0.3; Splitable = false; SetRectangle(P, D, H);}
	PlaneWallElement* GetDraftCopy(void) {return (PlaneWallElement*) new PlaneJoist(p,d,h);}
	virtual int GetElementType(void) {return 3;}

	//	MFC Compatibles Only
	void Draw(CDC* pDC, int Scale);
	CArchive& Store(CArchive& ar);
};


class Corner;
class Room;
class PlanElement;
class Boite;
class Lamp;
class Switch;
class Prise;
class Interaction;
class WallImage;
class RoomEdgeImage;
class WLANNode;

class PlaneWall: public PatchedSurface<VerticalRect> {

public:
	Room *Room1, *Room2;
	Corner *Corner1, *Corner2, *Target;
	bool Selected;
	double Attenuation;
	double TransmitCoeff;
	double ReflectCoeff;
	double Thickness;
	list<Boite*> Boites;
	list<Switch*> Switches;
	list<Prise*> Prises;
	int i1;
	int i2;

	PlaneWall() {Attenuation = 5; TransmitCoeff = 0.0555; ReflectCoeff = 0.3; Corner1 = 0; Corner2 = 0; Target = 0; Room1 = 0; Room2 = 0;}
	PlaneWall(Point P, Vector2d D, double H) {Attenuation = 5; TransmitCoeff = 0.0555; ReflectCoeff = 0.3; SetRectangle(P, D, H); Corner1 = 0; Corner2 = 0; Target = 0; Room1 = 0; Room2 = 0;}
	PlaneWall* GetDraftCopy(void);
	void SetAltitude(double altitude);
	void SetHeight(double height);
	void SetAroundCorner(Corner* corner, Point2d point);
	int CheckValidityWith(PlaneWall* Wall);
	void AddCornersTo(PlaneWall* Wall, list<Corner*> *NewCorners, list<Corner*> *Corners, list<PlaneWall*> *Walls);
	PlaneWall* AddCorner(Corner* C);
	Corner* OtherCorner(Corner* C) {if(C == Corner1) return Corner2; return Corner1;}
	Room* OtherRoom(Room* R) {if(R == Room1) return Room2; return Room1;}
	double AngleAt(Corner* C);
	void LeaveRoom(Room* R) {if(R == Room1) Room1 = 0; else Room2 = 0;}
	void MoveWallElements(PlaneWall* Wall);
	PlaneWindow* AddWindow(void);
	PlaneDoor* AddDoor(void);
	PlaneStud* AddStud(void);
	PlaneJoist* AddJoist(void);
	int PlaceDistributionBox(Point2d* POriginal, Point2d* PRender, Room* ROutDoor);
	int PlaceSwitch(Point2d* POriginal, Point2d* PRender);
	int PlacePrise(Point2d* POriginal, Point2d* PRender);
	Point GetImage(Point* P);
	Point GetReflectingPoint(Point* P);
	double Attenuate(Line* L);
	double TransmitAt(Line* L, Point* P);
	double ReflectAt(Line* L, Point* P);
	~PlaneWall();

//	MFC Compatibles Only
	void Draw(CDC* pDC, int Scale, CPen* WallPen, CPen* ElementPen, CPen* StudPen);
	friend CArchive& operator<< (CArchive& ar, PlaneWall& W);
	friend CArchive& operator>> (CArchive& ar, PlaneWall& W);
};


class PlaneCeiling {

public:
	double Altitude;
//	double Attenuation;
	double TransmitCoeff;
	double ReflectCoeff;
	double Thickness;
	Room *Room1, *Room2;
	PlaneCeiling() {TransmitCoeff = 0.0555; ReflectCoeff = 0.3; }
	PlaneCeiling(double altitude) {Altitude = altitude; TransmitCoeff = 0.0555; ReflectCoeff = 0.3; }
	Point GetImage(Point* P) {return Point(P->x, P->y, 2*Altitude - P->z);}
	Point GetReflectingPoint(Point* P) {return Point(P->x, P->y, Altitude);}
//	double Attenuate(Line* L);
	double TransmitAt(Line* L, Point* P) {return TransmitCoeff;}
	double ReflectAt(Line* L, Point* P) {return ReflectCoeff;}
};

class Corner {

public:
	Point2d Position;
	int FlagCount;
	list<PlaneWall*> Walls;
	Corner(Point2d P): Position(P), FlagCount(0) {}
	PlaneWall* NextWall(PlaneWall* W);
	PlaneWall* PreviousWall(PlaneWall* W);
	Room* DetermineRoom(PlaneWall* W1, PlaneWall* W2, bool RecursiveValidity = true);
	void AddWall(PlaneWall* W);
	PlaneWall* JoinWalls(list<PlaneWall*> *Walls);
};


class Room {

public:
	Corner* Flag;
	bool Convex;
	list<PlaneWall*> Walls;
	list<PlaneWall*> InnerWalls;
	list<Lamp*> Lamps;
	list<Switch*> Switches;
	list<Prise*> Prises;
	list<Boite*> Boites;
	list<Interaction*> Interactions[10];
	bool SameWith(Room* R);
	Room() {Convex = true;}
	~Room() {list<PlaneWall*>::iterator it, end; end = Walls.end(); for(it = Walls.begin(); it != end; it++) (*it)->LeaveRoom(this);}

};


class PlanElement
{
public:
	Point2d Position;
	Point2d SourcePosition;
	Point2d RenderPosition;
	Boite* Source;
	Room* HostRoom;
	PlaneWall* ConnectedWall;
	void SetSourcePosition(Point2d PSource) {SourcePosition=PSource;}
	virtual void DrawConnections(CDC* pDC, int Scale);
	virtual void Draw(CDC* pDC, int Scale) = 0;
};


class Boite: public PlanElement
{
protected:
public:
	list<Point2d> PathPoints;
	list<PlanElement*> ConnectedElements;
	Boite(){Source = 0;};
	void SetPosition(Point2d point1, Point2d point2) {Position = point1; RenderPosition = point2;}
	void DrawConnections(CDC* pDC, int Scale);
	void Draw(CDC* pDC, int Scale);
};

class DistributionBox: public Boite
{
public:
	DistributionBox(){Source = 0;};
	void Draw(CDC* pDC, int Scale);
};

class Switch: public PlanElement
{
public:
	Switch() {}
	void SetPosition(Point2d point1, Point2d point2) {Position = point1; RenderPosition = point2;}
	void Draw(CDC* pDC, int Scale);
};


class Lamp: public PlanElement
{
public:
	Lamp(Point2d point) {RenderPosition = point; Position = point; Source = 0;}
	void SetPosition(Point2d point) {RenderPosition = point; Position = point;}
	void Draw(CDC* pDC, int Scale);
};


class Prise: public PlanElement
{
public:
	Prise(){Source = 0;}
	void SetPosition(Point2d point1, Point2d point2) {Position = point1; RenderPosition = point2;}
	void Draw(CDC* pDC, int Scale);
};


class Interaction {

public:
	int Order;
	Point ImagePoint;
	PlaneWall* Wall;
	Room* SourceRoom;
	Point* SourcePoint;
	Interaction* Parent;
	Interaction** Interactions;
	Interaction(int order, Point imagePoint, PlaneWall* wall, Room* sourceRoom, Point* sourcePoint, Interaction* parent): Order(order), ImagePoint(imagePoint), Wall(wall), SourceRoom(sourceRoom), SourcePoint(sourcePoint), Parent(parent) {Interactions=0;}
};

/*
class WallImage {

public:
	Point Position;
	Interaction* SourceInteraction;
	double MinPowerLoss;
	WallImage(Point position, Interaction* source, Room* sourceRoom): Position(position), SourceInteraction(source), SourceRoom(sourceRoom) {}
	void GetReflectedIn(Room* room);
	double PropagateThrough(Point* P) {return 0;}
};
*/

class LANNode {

protected:

public:
	Point2d Position;
	double Offset;
	Room* R;
	char Name[16];
	bool Selected;
	LANNode(): Selected(false) {}
	LANNode* Select(Point2d point, int Scale);
	LANNode* Select(Point2d point1, Point2d point2);
	virtual void Draw(CDC* DC, int Scale) = 0;

};


class WNAntenna {

public:
	char Type[16];
	double Power;
	WNAntenna(): Power(125) {strcpy(Type, "Omni");}
	double PropagateThrough(LineSegment* L);
};


class WLANNode: public LANNode {

private:

public:
	WNAntenna Antenna;
	int WNNo;
	Room* HomeRoom;
	Interaction** Interactions;
	WLANNode(): LANNode() {}
	void DeleteImageTree(void) {}
	double PropagateThrough(LineSegment* L);
};


class AP: public WLANNode {
	
private:

public:
	AP(): WLANNode() {}

// MFC Compatibles only
	void Draw(CDC* pDC, int Scale);
	friend CArchive& operator<< (CArchive& ar, AP& A);
	friend CArchive& operator>> (CArchive& ar, AP& A);
};


class Floor {
	double Altitude;
	double Height;
	PlaneWall* SelectedWall;
	PlaneWallElement* SelectedWallElement;
//	PlaneWall* SelectedWallCopy;
//	PlaneWallElement* SelectedElementCopy;
	list<Corner*> Corners;
	list<Corner*> RoomFlags;
public:
	PlaneCeiling *floor, *ceiling;
	list<PlaneWall*> Walls;
	list<Room*> Rooms;
	Room* Outdoor;
	list<PlanElement*> PlanElements;
	Corner* GraphStart;
	list<AP*> APs;
	char Name[16];
	bool Hidden;
	DistributionBox* TheDistributionBox;
	Floor(char name[], double altitude = 0, double height = 3.2): Altitude(altitude), Height(height), Hidden(false) {strcpy(Name,name);}
	int GetWallCount(void) {return Walls.size();}
	double GetAltitude(void) {return Altitude;}
	double GetHeight(void) {return Height;}
	void SetAltitude(double altitude);
	void SetHeight(double height);
	Room* GetRoom(Point2d *P, Room* R1, Point2d* P1);
	Room* GetRoom(Point2d P);
	void AddRoomFlag(Corner* C);
	int CheckWallValidity(PlaneWall* Wall);
	PlaneWall* GetSelectedWallCopy(void);
	PlaneWallElement* GetSelectedElementCopy(void);
	void AddWall(void);
	void SetWall(Point2d point1, Point2d point2);
	void RemoveWall(void);
	void AddCornersTo(PlaneWall* Wall, bool JoinWalls = true);
	void DeleteCornersTo(PlaneWall* Wall);
	void DeleteRooms(void);
	void DetermineRoom(Corner* Flag);
	void DetermineRooms(void);
	void DeterminePathGraph(void);
	void DeterminePlanElements(void);
	void DeterminePlanConnections(void);
	void AddWindow(void);
	void SetWindow(Point2d point1, Point2d point2);
	void RemoveWindow(void);
	void AddDoor(void);
	void SetDoor(Point2d point1, Point2d point2);
	void RemoveDoor(void);
	void AddStud(void);
	void SetStud(Point2d point1, Point2d point2);
	void RemoveStud(void);
//	void AddAccessPoint(char name[]);
	void GetAPNames(char names[][16]);
	int CheckAPNameInvalidity(char name[]);
	void GenerateCoverageMap(WLANNode* WN);
//	Point2d* SnapToWalls(Point2d P);
//	Point2d* SnapToSelectedWall(Point2d P);
//	Point2d* SnapToOtherWalls(Point2d P);
	Point2d Snap(Point2d P, bool ToSelected = false, bool Select = false, bool ExcludeCurrent = false);

//	MFC Compatibles Only
	void DrawWall(CDC* pDC, int Scale, CPen* WallPen, CPen* ElementPen, CPen* StudPen);
	void Draw(CDC* pDC, int Scale, CPen* WallPen, CPen* ElementPen, CPen* StudPen);
	void DrawPlan(CDC* pDC, int Scale);
	void DrawLAN(CDC* pDC, int Scale);
	friend CArchive& operator<< (CArchive& ar, Floor& F);
	friend CArchive& operator>> (CArchive& ar, Floor& F);
	void Dump(void);
};


class Building {

	Floor* SelectedFloor;
	list<Floor*> Floors;
	list<PlaneCeiling*> Ceilings;
public:
	AP* SelectedAP;
	Building(){Ceilings.push_back(new PlaneCeiling(0));}
	void GenerateDefault();
	int GetFloorCount(void) {return Floors.size();}
	int GetSelected(void);
	void GetFloorNames(char names[][16]);
	int CheckFloorNameInvalidity(char name[]);
	int AddFloor(char name[], double height = 3.2, bool top = true);
	int RemoveFloor(void);
	void SetSelected(int no);
	int SetFloorName(char name[]);
	void SetFloorHeight(double height);
	int CheckWallValidity(PlaneWall* Wall);
	PlaneWall* GetSelectedWallCopy(void);
	PlaneWallElement* GetSelectedElementCopy(void);
	void AddWall(void);
	void SetWall(Point2d point1, Point2d point2);
	void RemoveWall(void);
	void AddWindow(void);
	void SetWindow(Point2d point1, Point2d point2);
	void RemoveWindow(void);
	void AddDoor(void);
	void SetDoor(Point2d point1, Point2d point2);
	void RemoveDoor(void);
	void AddStud(void);
	void SetStud(Point2d point1, Point2d point2);
	void RemoveStud(void);
	void DetermineRooms(void);
	void DeterminePlanElements(void);
	void DeterminePlanConnections(void);
	void GenerateImageTree(WLANNode* WN);
	double TraverseImageTree(WLANNode* WN, Point* P);
	int GetAPCount(void);
	int AddAccessPoint();
	int CheckAPNameInvalidity(char name[]);
	int SetAPName(char name[]);
	void GetAPNames(char names[][16]);
	char* GetSelectedAPName(void);
	void SetSelectedAP(char name[]);
	void SetSelectedAP(Point2d point, int Scale);
	void SetAPPosition(Point2d point);
	void SetAPPosition(Point2d point, double altitude);
	void RemoveAP();
	void TestDown(Point2d point, CDC* pDC, int Scale, CPen* WallPen, CPen* ElementPen, CPen* StudPen);
	Point2d Snap(Point2d P, bool ToSelected = false, bool Select = false, bool ExcludeCurrent = false, bool ToSelectedFloor = false);

//	MFC Compatibles Only
	void DrawWall(CDC* pDC, int Scale, BOOL Inverse = FALSE);
	void Draw(CDC* pDC, int Scale);
	void DrawLAN(CDC* pDC, int Scale);
	void DrawPlan(CDC* pDC, int Scale);
	friend CArchive& operator<< (CArchive& ar, Building& B);
	friend CArchive& operator>> (CArchive& ar, Building& B);
	HMETAFILE GenerateCoverageMap(CMetaFileDC* MetaFile, int Scale, Vector2d CampSize);
};


#endif
