#include "stdafx.h"
#include "Floor.h"


// PlaneWall Implementation

PlaneWall* PlaneWall::GetDraftCopy(void)
{
	PlaneWall* DraftCopy = new PlaneWall(p, d, h);
	list<Surface*>::iterator itpch, endpch;
	itpch = Patches.begin();
	endpch = Patches.end();
	for(; itpch != endpch; itpch++)
		DraftCopy->AddPatch(((PlaneWallElement*) *itpch)->GetDraftCopy());
	return DraftCopy;
}

void PlaneWall::SetAltitude(double altitude)
{
	SetRectangle(Point(p.x, p.y, altitude), d, h);
}

void PlaneWall::SetHeight(double height)
{
	SetRectangle(p, d, height);
}

void PlaneWall::SetAroundCorner(Corner* corner, Point2d point)
{
	Vector2d V1, V2;
	Point *P1, P2;
	Point2d P2d1, P2d2;
	V1 = Vector2d(&corner->Position, &point);
	V1 = V1/V1.Abs();
	double d1, d2;
	list<Surface*>::iterator itpch, endpch;
	itpch = Patches.begin();
	endpch = Patches.end();
	for(; itpch != endpch; itpch++)
	{
		P1 = ((PlaneWallElement*) *itpch)->GetPoint();
		P2d1 = Point2d(P1->x, P1->y);
		V2 = *((PlaneWallElement*) *itpch)->GetDirection();
		P2d2 = V2 + P2d1;
		d1 = (corner->Position.x - P2d1.x)*(corner->Position.x - P2d1.x) + (corner->Position.y - P2d1.y)*(corner->Position.y - P2d1.y);
		d2 = (corner->Position.x - P2d2.x)*(corner->Position.x - P2d2.x) + (corner->Position.y - P2d2.y)*(corner->Position.y - P2d2.y);
		P2d1 = sqrt(d1)*V1 + corner->Position;
		P2d2 = sqrt(d2)*V1 + corner->Position;
		((PlaneWallElement*) *itpch)->SetPosition(P2d1, P2d2);
	}
	SetPosition(corner->Position, point);
}

double PlaneWall::AngleAt(Corner* C)
{
	Vector2d Direction;
	Point2d P2d1, P2d2;
	Vector2d* D;
	P2d1 = Point2d(GetPoint()->x, GetPoint()->y);
	D = GetDirection();
	P2d2 = *D + P2d1;
	Direction = *D;
	if((C->Position.x - P2d1.x)*(C->Position.x - P2d1.x) + (C->Position.y - P2d1.y)*(C->Position.y - P2d1.y) < (C->Position.x - P2d2.x)*(C->Position.x - P2d2.x) + (C->Position.y - P2d2.y)*(C->Position.y - P2d2.y))
//	if(C == Corner1)
Direction = Direction/Direction.Abs();
	else Direction = -1*Direction/Direction.Abs();
//	Direction = Vector2d(&(C->Position), &(this->OtherCorner(C)->Position));
//	Direction = Direction/Direction.Abs();
	if(Direction.y > 0) return -1 - Direction.x;
	return 1 + Direction.x;
}

int PlaneWall::CheckValidityWith(PlaneWall* Wall)
{
	LineSegment2d L1, L2;
	Point* P ;
	Vector2d* D2d;
	Point2d P2d, P2d1, P2d2;
	bool Invalid = false;
	P = Wall->GetPoint();
	D2d = Wall->GetDirection();
	L1 = LineSegment2d(Point2d(p.x,p.y), d);
	L2 = LineSegment2d(Point2d(P->x,P->y), *D2d);
	if(L1.Intersect(&L2, &P2d) == 0) return -1;
	list<Surface*>::iterator it, end;
	it = Patches.begin();
	end = Patches.end();
	for(; it != end; it++)
	{
		P = ((PlaneWallElement*) *it)->GetPoint();
		D2d = ((PlaneWallElement*) *it)->GetDirection();
		P2d1 = Point2d(P->x, P->y);
		P2d2 = *D2d + P2d1;
		if((P2d.x - P2d1.x)*(P2d.x - P2d2.x) < 0 && (P2d.y - P2d1.y)*(P2d.y - P2d2.y) < 0)
			if(!((PlaneWallElement*) *it)->IsSplitable()) Invalid = true;
	}
	it = Wall->Patches.begin();
	end = Wall->Patches.end();
	for(; it != end; it++)
	{
		P = ((PlaneWallElement*) *it)->GetPoint();
		D2d = ((PlaneWallElement*) *it)->GetDirection();
		P2d1 = Point2d(P->x, P->y);
		P2d2 = *D2d + P2d1;
		if((P2d.x - P2d1.x)*(P2d.x - P2d2.x) < 0 && (P2d.y - P2d1.y)*(P2d.y - P2d2.y) < 0)
			if(!((PlaneWallElement*) *it)->IsSplitable()) Invalid = true;
	}
	if(Invalid) return 0;
	return -1;
}

void PlaneWall::AddCornersTo(PlaneWall* Wall, list<Corner*> *NewCorners, list<Corner*> *Corners, list<PlaneWall*> *Walls)
{
	LineSegment2d L1, L2;
	int intersect = 0;
	Point2d P2d, P2dEnd1, P2dEnd2, P2dEnd3, P2dEnd4;
	Point* P = Wall->GetPoint();
	Vector2d* D;
	D = GetDirection();
	P2dEnd3 = Point2d(GetPoint()->x, GetPoint()->y);
	P2dEnd4 = *D + P2dEnd3;
	D = Wall->GetDirection();
	P2dEnd1 = Point2d(Wall->GetPoint()->x, Wall->GetPoint()->y);
	P2dEnd2 = *D + P2dEnd1;
	L1 = LineSegment2d(Point2d(p.x,p.y), d);
	L2 = LineSegment2d(Point2d(P->x,P->y), *D);
	intersect = L1.Intersect(&L2, &P2d);
	if(intersect == 0)
	{
		if((P2dEnd1.x - P2dEnd3.x)*(P2dEnd1.x - P2dEnd3.x) + (P2dEnd1.y - P2dEnd3.y)*(P2dEnd1.y - P2dEnd3.y) < 0.04 || (P2dEnd1.x - P2dEnd4.x)*(P2dEnd1.x - P2dEnd4.x) + (P2dEnd1.y - P2dEnd4.y)*(P2dEnd1.y - P2dEnd4.y) < 0.04)
		{
			P2d = Point2d(P2dEnd1);
			intersect = 1;
		}
		if((P2dEnd2.x - P2dEnd3.x)*(P2dEnd2.x - P2dEnd3.x) + (P2dEnd2.y - P2dEnd3.y)*(P2dEnd2.y - P2dEnd3.y) < 0.04 || (P2dEnd2.x - P2dEnd4.x)*(P2dEnd2.x - P2dEnd4.x) + (P2dEnd2.y - P2dEnd4.y)*(P2dEnd2.y - P2dEnd4.y) < 0.04)
		{
			P2d = Point2d(P2dEnd2);
			intersect = 1;
		}
	}
	if(intersect == 0) return;
	list<Corner*>::iterator itc, endc;
	Corner* ClosestCorner;
	PlaneWall* NewWall;
	double ClosestDistance = 0.04, d1, d2;
	bool Found = false;
	d1 = (P2d.x - Corner1->Position.x)*(P2d.x - Corner1->Position.x) + (P2d.y - Corner1->Position.y)*(P2d.y - Corner1->Position.y);
	d2 = (P2d.x - Corner2->Position.x)*(P2d.x - Corner2->Position.x) + (P2d.y - Corner2->Position.y)*(P2d.y - Corner2->Position.y);

	if(d1 < d2)
	{
		ClosestDistance = d1;
		ClosestCorner = Corner1;
	}
	else
	{
		ClosestDistance = d2;
		ClosestCorner = Corner2;
	}

	if(ClosestDistance >= 0.04)
	{
		ClosestCorner = new Corner(P2d);
		Corners->push_back(ClosestCorner);
		NewWall = AddCorner(ClosestCorner);
		Walls->push_front(NewWall);
	}
	

	d1 = (P2d.x - P2dEnd1.x)*(P2d.x - P2dEnd1.x) + (P2d.y - P2dEnd1.y)*(P2d.y - P2dEnd1.y);
	d2 = (P2d.x - P2dEnd2.x)*(P2d.x - P2dEnd2.x) + (P2d.y - P2dEnd2.y)*(P2d.y - P2dEnd2.y);
	if(d1 < 0.04)
	{
		if(Wall->Corner1 != ClosestCorner)
		{
			Wall->Corner1 = ClosestCorner;
	//AfxMessageBox("About to be tied");
			ClosestCorner->AddWall(Wall);
	//AfxMessageBox("Just tied");
		}
		return;
	}
	if(d2 < 0.04)
	{
		if(Wall->Corner2 != ClosestCorner)
		{
			Wall->Corner2 = ClosestCorner;
	//AfxMessageBox("About to be tied");
			ClosestCorner->AddWall(Wall);
	//AfxMessageBox("Just tied");
		}
		return;
	}
//AfxMessageBox("Attention Here!");
	itc = NewCorners->begin();
	endc = NewCorners->end();
	d1 = (ClosestCorner->Position.x - P->x)*(ClosestCorner->Position.x - P->x) + (ClosestCorner->Position.y - P->y)*(ClosestCorner->Position.y - P->y);
	while(itc != endc && !Found)
	{
//AfxMessageBox("New Step in the Sort Loop");
		d2 = ((*itc)->Position.x - P->x)*((*itc)->Position.x - P->x) + ((*itc)->Position.y - P->y)*((*itc)->Position.y - P->y);
//AfxMessageBox("Calculated Element Distance");
		if(*itc == ClosestCorner) Found = true;
		if(d1 < d2)
		{
			if(!Found) NewCorners->insert(itc, ClosestCorner);
//AfxMessageBox("Mark Split Point");
			Found = true;
		}
		itc++;
	}
	if(!Found)
	{
		NewCorners->insert(itc, ClosestCorner);
//AfxMessageBox("Mark Split Point");
	}
//AfxMessageBox("Left Here!");
}

PlaneWall* PlaneWall::AddCorner(Corner* C)
{
	list<Surface*> MovedPatches;
	list<Surface*>::iterator it, end;
	Corner* EndCorner2 = Corner2;
	PlaneWall* NewWall;
	Point P3d;
	Vector2d D2d;
	Point2d P2d1, P2d2;
//AfxMessageBox("Mark Position 0");
	SetPosition(Corner1->Position, C->Position);
	Corner2 = C;
//AfxMessageBox("Mark Position I");
	NewWall = new PlaneWall(Point(C->Position.x, C->Position.y, p.z), Vector2d(&C->Position, &EndCorner2->Position), h);
	NewWall->Corner1 = C;
	NewWall->Corner2 = EndCorner2;
//AfxMessageBox("Mark Position II");
	EndCorner2->Walls.remove(this);
	EndCorner2->AddWall(NewWall);
	C->AddWall(this);
	C->AddWall(NewWall);
//AfxMessageBox("Mark Position III");
	it = Patches.begin();
	end = Patches.end();
	for(; it != end; it++)
	{
//AfxMessageBox("It's Here!");
		P3d = *((PlaneWallElement*) *it)->GetPoint();
		D2d = *((PlaneWallElement*) *it)->GetDirection();
		P2d1 = Point2d(P3d.x, P3d.y);
		P2d2 = D2d + P2d1;
		D2d = Vector2d(&Corner2->Position, &Corner1->Position);
		if(D2d.Product(Vector2d(&Corner2->Position, &P2d1)) < 0 && D2d.Product(Vector2d(&Corner2->Position, &P2d2)) < 0)
		{
			MovedPatches.push_back(*it);
			NewWall->AddPatch(*it);
		}
		else if(D2d.Product(Vector2d(&Corner2->Position, &P2d1)) < 0 || D2d.Product(Vector2d(&Corner2->Position, &P2d2)) < 0)
		{
// Split the Patch here
		}
	}
	
	it = MovedPatches.begin();
	end = MovedPatches.end();
	for(; it != end; it++)
	{
		Patches.remove(*it);
	}

	return NewWall;
}

void PlaneWall::MoveWallElements(PlaneWall* Wall)
{
	list<Surface*> MovedPatches;
	list<Surface*>::iterator it, end;
	it = Patches.begin();
	end = Patches.end();
	for(; it != end; it++)
	{
		MovedPatches.push_back(*it);
		Wall->AddPatch(*it);
	}
	
	it = MovedPatches.begin();
	end = MovedPatches.end();
	for(; it != end; it++)
	{
		Patches.remove(*it);
	}
}

PlaneWall::~PlaneWall()
{
	list<Surface*>::iterator start, end, it;
	start = Patches.begin();
	end = Patches.end();
	for(it = start; it != end; it++) delete *it;
}

PlaneWindow* PlaneWall::AddWindow(void)
{
	PlaneWindow* TempWindow = new PlaneWindow();
	AddPatch(TempWindow);
	return TempWindow;
}

PlaneDoor* PlaneWall::AddDoor(void)
{
	PlaneDoor* TempDoor = new PlaneDoor();
	AddPatch(TempDoor);
	return TempDoor;
}

PlaneStud* PlaneWall::AddStud(void)
{
	PlaneStud* TempStud = new PlaneStud();
	AddPatch(TempStud);
	return TempStud;
}

PlaneJoist* PlaneWall::AddJoist(void)
{
	PlaneJoist* TempJoist = new PlaneJoist();
	AddPatch(TempJoist);
	return TempJoist;
}

int PlaneWall::PlaceDistributionBox(Point2d* POriginal, Point2d* PRender, Room* ROutDoor)
{
	int found0, found1, Clockwise;
	Point2d P1, P2;
	Point *P3;
	Vector2d V1, V2, *V3;
	PlaneDoor* TempDoor;
	list<Surface*>::iterator its, its1, starts, ends;
	if(Room1!=ROutDoor && Room2!=ROutDoor)
		return 0;
	if(Patches.size() > 0)
	{
		found0 = 0;
		found1 = 0;
		starts = Patches.begin();
		ends = Patches.end();
		for(its = starts; its != ends; its++)
		{
			if(((PlaneWallElement*) (*its))->GetElementType() == 0)
			{
				found0 = 1;
				P3 = ((PlaneWallElement*) (*its))->GetPoint();
				V3 = ((PlaneWallElement*) (*its))->GetDirection();
				P1.x = P3->x + V3->x;
				P1.y = P3->y + V3->y;
				V1 = (*V3)/(V3->Abs());
				P1 = 1.4*V1 + P1;
				TempDoor = (PlaneDoor*) *its;
				if(((PlaneDoor*) (*its))->Clockwise) Clockwise = 1;
				else Clockwise = 0;
				found1 = 0;
				P3 = GetPoint();
				V3 = GetDirection();
				if((P1.x <= P3->x + tollerance && P1.x >= P3->x + V3->x - tollerance || P1.x >= P3->x + tollerance && P1.x <= P3->x + V3->x - tollerance) &&
					(P1.y <= P3->y + tollerance && P1.y >= P3->y + V3->y - tollerance || P1.y >= P3->y + tollerance && P1.y <= P3->y + V3->y - tollerance))
					found1 = 1;
				if(found1 == 1)
				for(its1 = starts; its1 != ends; its1++)
				{
					P3 = ((PlaneWallElement*) (*its1))->GetPoint();
					V3 = ((PlaneWallElement*) (*its1))->GetDirection();
					if((P1.x <= P3->x + tollerance && P1.x >= P3->x + V3->x - tollerance || P1.x >= P3->x + tollerance && P1.x <= P3->x + V3->x - tollerance) &&
						(P1.y <= P3->y + tollerance && P1.y >= P3->y + V3->y - tollerance || P1.y >= P3->y + tollerance && P1.y <= P3->y + V3->y - tollerance))
						found1 = 0;
				}
			}
		}
		if(found1)
		{
			V3 = TempDoor->GetDirection();
			V1.x = V3->y;
			V1.y = -V3->x;
			V1 = (V1)/(V1.Abs());
//			if(Clockwise)
				P2 = 0.2*V1 + P1;
//			else
//				P2 = -0.2*V1 + P1;
			*POriginal = P1;
			*PRender = P2;
			return 1;
		}

		if(found0) return -1;
		return 0;
	}
	else return 0;
}

int PlaneWall::PlaceSwitch(Point2d* POriginal, Point2d* PRender)
{
	int found0, found1, Clockwise;
	Point2d P1, P2;
	Point *P3;
	Vector2d V1, V2, *V3;
	PlaneDoor* TempDoor;
	list<Surface*>::iterator its, its1, starts, ends;
	if(Patches.size() > 0)
	{
		found0 = 0;
		found1 = 0;
		starts = Patches.begin();
		ends = Patches.end();
		for(its = starts; its != ends; its++)
		{
			if(((PlaneWallElement*) (*its))->GetElementType() == 0)
			{
				found0 = 1;
				P3 = ((PlaneWallElement*) (*its))->GetPoint();
				V3 = ((PlaneWallElement*) (*its))->GetDirection();
				P1.x = P3->x + V3->x;
				P1.y = P3->y + V3->y;
				V1 = (*V3)/(V3->Abs());
				P1 = 0.4*V1 + P1;
				TempDoor = (PlaneDoor*) *its;
				if(((PlaneDoor*) (*its))->Clockwise) Clockwise = 1;
				else Clockwise = 0;
				found1 = 0;
				P3 = GetPoint();
				V3 = GetDirection();
				if((P1.x <= P3->x + tollerance && P1.x >= P3->x + V3->x - tollerance || P1.x >= P3->x + tollerance && P1.x <= P3->x + V3->x - tollerance) &&
					(P1.y <= P3->y + tollerance && P1.y >= P3->y + V3->y - tollerance || P1.y >= P3->y + tollerance && P1.y <= P3->y + V3->y - tollerance))
					found1 = 1;
				if(found1 == 1)
				for(its1 = starts; its1 != ends; its1++)
				{
					P3 = ((PlaneWallElement*) (*its1))->GetPoint();
					V3 = ((PlaneWallElement*) (*its1))->GetDirection();
					if((P1.x <= P3->x + tollerance && P1.x >= P3->x + V3->x - tollerance || P1.x >= P3->x + tollerance && P1.x <= P3->x + V3->x - tollerance) &&
						(P1.y <= P3->y + tollerance && P1.y >= P3->y + V3->y - tollerance || P1.y >= P3->y + tollerance && P1.y <= P3->y + V3->y - tollerance))
						found1 = 0;
				}
			}
		}
		if(found1)
		{
			V3 = TempDoor->GetDirection();
			V1.x = V3->y;
			V1.y = -V3->x;
			V1 = (V1)/(V1.Abs());
//			if(Clockwise)
				P2 = 0.5*V1 + P1;
//			else
//				P2 = -0.5*V1 + P1;
			*POriginal = P1;
			*PRender = P2;
			return 1;
		}

		if(found0) return -1;
		return 0;
	}
	else return 0;
}

int PlaneWall::PlacePrise(Point2d* POriginal, Point2d* PRender)
{
	int found0, found1, Clockwise;
	Point2d P1, P2;
	Point *P3;
	Vector2d V1, V2, *V3;
	PlaneDoor* TempDoor;
	list<Surface*>::iterator its, its1, starts, ends;
	if(Patches.size() > 0)
	{
		found0 = 0;
		found1 = 0;
		starts = Patches.begin();
		ends = Patches.end();
		for(its = starts; its != ends; its++)
		{
			if(((PlaneWallElement*) (*its))->GetElementType() == 0)
			{
				found0 = 1;
				P3 = ((PlaneWallElement*) (*its))->GetPoint();
				V3 = ((PlaneWallElement*) (*its))->GetDirection();
				P1.x = P3->x + V3->x;
				P1.y = P3->y + V3->y;
				V1 = (*V3)/(V3->Abs());
				P1 = 0.8*V1 + P1;
				TempDoor = (PlaneDoor*) *its;
				if(((PlaneDoor*) (*its))->Clockwise) Clockwise = 1;
				else Clockwise = 0;
				found1 = 0;
				P3 = GetPoint();
				V3 = GetDirection();
				if((P1.x <= P3->x + tollerance && P1.x >= P3->x + V3->x - tollerance || P1.x >= P3->x + tollerance && P1.x <= P3->x + V3->x - tollerance) &&
					(P1.y <= P3->y + tollerance && P1.y >= P3->y + V3->y - tollerance || P1.y >= P3->y + tollerance && P1.y <= P3->y + V3->y - tollerance))
					found1 = 1;
				if(found1 == 1)
				for(its1 = starts; its1 != ends; its1++)
				{
					P3 = ((PlaneWallElement*) (*its1))->GetPoint();
					V3 = ((PlaneWallElement*) (*its1))->GetDirection();
					if((P1.x <= P3->x + tollerance && P1.x >= P3->x + V3->x - tollerance || P1.x >= P3->x + tollerance && P1.x <= P3->x + V3->x - tollerance) &&
						(P1.y <= P3->y + tollerance && P1.y >= P3->y + V3->y - tollerance || P1.y >= P3->y + tollerance && P1.y <= P3->y + V3->y - tollerance))
						found1 = 0;
				}
			}
		}
		if(found1)
		{
			V3 = TempDoor->GetDirection();
			V1.x = V3->y;
			V1.y = -V3->x;
			V1 = (V1)/(V1.Abs());
//			if(Clockwise)
				P2 = 0.5*V1 + P1;
//			else
//				P2 = -0.5*V1 + P1;
			*POriginal = P1;
			*PRender = P2;
			return 1;
		}

		if(found0) return -1;
		return 0;
	}
	else return 0;
}

Point PlaneWall::GetImage(Point* P)
{
	Point2d Point1, Point2, Point3;
	Point1 = Point2d(GetPoint()->x, GetPoint()->y);
	Point2 = Point2d(P->x, P->y);
	Vector2d* V = GetDirection();
	Line2d L = Line2d(Point1, *V);
	Point3 = L.ClosestPointTo(&Point2);
	Vector2d TempVector = Vector2d(&Point2, &Point3);
	TempVector = 2*TempVector;
	return Vector(TempVector.x, TempVector.y, 0) + *P;
}

Point PlaneWall::GetReflectingPoint(Point* P)
{
	Point2d Point1, Point2, Point3;
	Point1 = Point2d(GetPoint()->x, GetPoint()->y);
	Point2 = Point2d(P->x, P->y);
	Vector2d* V = GetDirection();
	Line2d L = Line2d(Point1, *V);
	Point3 = L.ClosestPointTo(&Point2);
	return Point(Point3.x, Point3.y, P->z);
}

double PlaneWall::Attenuate(Line* L)
{
	Point P;
	if(Intersect(L, &P) == 0) return 0;
	PlaneWallElement* Element = (PlaneWallElement*) PassThroughWhich(&P);
	if(Element != 0) return Element->Attenuation;
	return Attenuation;
}

double PlaneWall::TransmitAt(Line* L, Point *P)
{
	PlaneWallElement* Element = (PlaneWallElement*) PassThroughWhich(P);
	if(Element != 0) return Element->TransmitCoeff;
	return TransmitCoeff;
}

double PlaneWall::ReflectAt(Line* L, Point *P)
{
	PlaneWallElement* Element = (PlaneWallElement*) PassThroughWhich(P);
	if(Element != 0) return Element->ReflectCoeff;
	return ReflectCoeff;
}
void PlaneWall::Draw(CDC* pDC, int Scale, CPen* WallPen, CPen* ElementPen, CPen* StudPen)
{
	CPen* DefPen;
	list<Surface*>::iterator end, it;
	end = Patches.end();
	list<PlaneWallElement*> Elements;
	list<PlaneWallElement*>::iterator Elementend1, Elementend2, Elementit1, Elementit2, TempElementit;
	PlaneWallElement* TempElement;
	DefPen = (CPen*) pDC->SelectObject(ElementPen);
	for(it = Patches.begin(); it != end; ++it)
	{
		Elements.push_front((PlaneWallElement*) (*it));
		if(((PlaneWallElement*) (*it))->GetElementType() == 2) pDC->SelectObject(StudPen);
		((PlaneWallElement*) (*it))->Draw(pDC, Scale);
		pDC->SelectObject(ElementPen);
	}
	pDC->SelectObject(WallPen);	
	Vector2d TempVector1, TempVector2;
	Elementend1 = Elements.end();
	Elementend2 = Elementend1--;
	Elementit1 = Elements.begin();
	for(; Elementit1 != Elementend1; Elementit1++)
	{
		Elementit2 = Elementit1;
		Elementit2++;
		for(; Elementit2 != Elementend2; Elementit2++)
		{
			TempVector1 = Vector2d((*Elementit1)->GetPoint()->x - p.x, (*Elementit1)->GetPoint()->y - p.y);
			TempVector2 = Vector2d((*Elementit2)->GetPoint()->x - p.x, (*Elementit2)->GetPoint()->y - p.y);
			if(TempVector1.x * TempVector1.x + TempVector1.y *TempVector1.y > TempVector2.x * TempVector2.x + TempVector2.y * TempVector2.y)
			{
				TempElement = *Elementit1;
				*Elementit1 =*Elementit2;
				*Elementit2 = TempElement;
			}
		}
	}

	CPoint point1 = CPoint(Scale*p.x, Scale*p.y);
	CPoint point2 = CPoint(point1.x + Scale*d.x, point1.y + Scale*d.y);
	CPoint TempPoint1, TempPoint2;
	Point2d TempPoint2d;
	pDC->MoveTo(point1);
	for(Elementit2 = Elements.begin(); Elementit2 != Elementend2;)
	{
		TempPoint2d = Point2d((*Elementit2)->GetPoint()->x, (*Elementit2)->GetPoint()->y);
		TempVector1 = Vector2d((*Elementit2)->GetDirection()->x, (*Elementit2)->GetDirection()->y);
		if(TempVector1.Product(d) < 0)
		{
			TempPoint1 = CPoint(Scale*(TempPoint2d.x + TempVector1.x), Scale*(TempPoint2d.y + TempVector1.y));
			TempPoint2 = CPoint(Scale*TempPoint2d.x, Scale*TempPoint2d.y);
		}
		else
		{
			TempPoint1 = CPoint(Scale*TempPoint2d.x, Scale*TempPoint2d.y);
			TempPoint2 = CPoint(Scale*(TempPoint2d.x + TempVector1.x), Scale*(TempPoint2d.y + TempVector1.y));
		}
		pDC->LineTo(TempPoint1);
		Elementit2++;
		pDC->MoveTo(TempPoint2);
	}
	pDC->LineTo(point2);
	pDC->SelectObject(DefPen);
}

CArchive& operator<< (CArchive& ar, PlaneWall& W)
{
	int n;
	list<Surface*>::iterator ite, ende;


	ar << W.TransmitCoeff<< W.ReflectCoeff << W.Thickness;
	ar << W.p.x << W.p.y << W.p.z << W.d.x << W.d.y << W.h;

	n = W.Patches.size();
	ar << n;

	ite = W.Patches.begin();
	ende = W.Patches.end();
	for(; ite != ende; ite++)
	{
		((PlaneWallElement*) *ite)->Store(ar);

	}

	return ar;
}

CArchive& operator>> (CArchive& ar, PlaneWall& W)
{
	double WPx, WPy, WPz, WDx, WDy, WH;
	int i, n, t;
	list<Surface*>::iterator ite, ende;

	ar >> W.TransmitCoeff >> W.ReflectCoeff >> W.Thickness;
	ar >> WPx >> WPy >> WPz >> WDx >> WDy >> WH;
	W.SetRectangle(Point(WPx,WPy,WPz), Vector2d(WDx, WDy), WH);

	PlaneWallElement* NewElement;
	double ETransmitCoeff, EReflectCoeff, EThickness;
	double EPx, EPy, EPz, EDx, EDy, EH;
	BYTE DClockwise;
	ar >> n;
	for(i=0; i<n; i++)
	{
		ar >> t;
		ar >> ETransmitCoeff >> EReflectCoeff >> EThickness;
		ar >> EPx >> EPy >> EPz >> EDx >> EDy >> EH;
		switch(t)
		{
		case 0:
			NewElement = new PlaneDoor(Point(EPx,EPy,EPz), Vector2d(EDx,EDy), EH);
			ar >> DClockwise;
			((PlaneDoor*) NewElement)->Clockwise = (bool) DClockwise;
			break;

		case 1:
			NewElement = new PlaneWindow(Point(EPx,EPy,EPz), Vector2d(EDx,EDy), EH);
			break;

		case 2:
			NewElement = new PlaneStud(Point(EPx,EPy,EPz), Vector2d(EDx,EDy), EH);
			break;

		case 3:
			NewElement = new PlaneJoist(Point(EPx,EPy,EPz), Vector2d(EDx,EDy), EH);
			break;
		};
		
		W.AddPatch(NewElement);
	}
	return ar;
}


CArchive& PlaneWallElement::Store(CArchive& ar)
{
	ar << TransmitCoeff<< ReflectCoeff << Thickness;
	ar << p.x << p.y << p.z << d.x << d.y << h;
	
	return ar;
}


// PlaneWindow Implementation

void PlaneWindow::Draw(CDC* pDC, int Scale)
{
	CPoint point1 = CPoint(Scale*p.x, Scale*p.y);
	CPoint point2 = CPoint(point1.x + Scale*d.x, point1.y + Scale*d.y);
	CSize csize = CSize(point1.y - point2.y, point2.x - point1.x);
	double size = sqrt(csize.cx * csize.cx + csize.cy * csize.cy);
	if(csize.cx > 0) csize.cx = ceil(10/size*csize.cx);
	else csize.cx = floor(10/size*csize.cx);
	if(csize.cy > 0) csize.cy = ceil(10/size*csize.cy);
	else csize.cy = floor(10/size*csize.cy);
	CPoint Corners[5];
	Corners[0] = point1 + csize;
	Corners[1] = point2 + csize;
	Corners[2] = point2 - csize;
	Corners[3] = point1 - csize;
	Corners[4] = Corners[0];
	pDC->Polyline(Corners, 5);
	pDC->MoveTo(point1);
	pDC->LineTo(point2);
}

CArchive& PlaneWindow::Store(CArchive& ar)
{
	ar << 1;
	PlaneWallElement::Store(ar);

	return ar;
}


// PlaneDoor Implementation

void PlaneDoor::Draw(CDC* pDC, int Scale)
{
	CPoint point1 = CPoint(Scale*p.x, Scale*p.y);
	CPoint point2 = CPoint(point1.x + Scale*d.x, point1.y + Scale*d.y);
	CSize PointDiff = point2 - point1;
	double r = pow(PointDiff.cx*PointDiff.cx + PointDiff.cy*PointDiff.cy, 0.5);
	CRect FullRect = CRect(point1.x - r,point1.y+r,point1.x + r, point1.y - r);
	CPoint PointStart = CPoint(point1.x + (point2.y - point1.y), point1.y - (point2.x - point1.x));
	FullRect.NormalizeRect();
	pDC->MoveTo(point1);
	pDC->LineTo(PointStart);
	pDC->Arc(FullRect,PointStart,point2);
}

CArchive& PlaneDoor::Store(CArchive& ar)
{
	ar << 0;
	PlaneWallElement::Store(ar);
	ar << (BYTE) Clockwise;

	return ar;
}


// PlaneStud Implementation

void PlaneStud::Draw(CDC* pDC, int Scale)
{
	CPoint point1 = CPoint(p.x*Scale, p.y*Scale);
	CPoint point2 = CPoint(point1.x + d.x*Scale, point1.y + d.y*Scale);
	pDC->MoveTo(point1);
	pDC->LineTo(point2);
}

CArchive& PlaneStud::Store(CArchive& ar)
{
	ar << 2;
	PlaneWallElement::Store(ar);

	return ar;
}


// PlaneJoist Implementation

void PlaneJoist::Draw(CDC* pDC, int Scale)
{
	CPoint point1 = CPoint(p.x, p.y);
	CPoint point2 = CPoint(point1.x + d.x, point1.y + d.y);
	pDC->MoveTo(point1);
	pDC->LineTo(point2);
}

CArchive& PlaneJoist::Store(CArchive& ar)
{
	ar << 3;
	PlaneWallElement::Store(ar);

	return ar;
}


// Corner Implementation

PlaneWall* Corner::NextWall(PlaneWall* W)
{
	list<PlaneWall*>::iterator it, start, end;
	end = Walls.end();
	start = Walls.begin();
	for(it = start; it != end; it++)
		if(*it == W)
		{
			it++;
			if(it != end) return *it;
			return *start;
		}
	return 0;
}
	
PlaneWall* Corner::PreviousWall(PlaneWall* W)
{
	list<PlaneWall*>::iterator it, start, end;
	end = Walls.end();
	start = Walls.begin();
	for(it = start; it != end; it++)
		if(*it == W)
		{
			if(it != start) it--;
			else it = --end;
			return *it;
		}
	return 0;
}

Room* Corner::DetermineRoom(PlaneWall* RE1, PlaneWall* RE2, bool RecursiveValidity)
{
	bool Clockwise = true;
	bool HalfTour = false;
	int tour = 0;
	bool Valid = true;
	bool ClockwiseValidity = FlagCount > 1 || Walls.size() == 2;
	bool divide = true;
	double hypoteneous;
	Vector2d V1, V2;
	Point2d Pos;
	double totaldot, totalcross, tempdot, tempcross, temptotalcross, temptotaldot;
	PlaneWall *RETemp;
	Corner *CTemp;
	CTemp = RE1->OtherCorner(this);
	V1 = Vector2d(&CTemp->Position, &Position);
	Room* R = new Room;
	RETemp = RE2;
	R->Walls.push_back(RETemp);
	CTemp = RETemp->OtherCorner(this);
	V2 = Vector2d(&Position, &CTemp->Position);
	totalcross = V1*V2;
	totaldot = V1.Product(V2);
	RETemp = CTemp->NextWall(RETemp);
	while(CTemp != this)
	{
		R->Walls.push_back(RETemp);
		Pos = CTemp->Position;
		CTemp = RETemp->OtherCorner(CTemp);
		if(ClockwiseValidity)
		{
			V1 = V2;
			V2 = Vector2d(&Pos, &CTemp->Position);
			tempcross = V1*V2;
			tempdot = V1.Product(V2);
			if(tempcross != 0)
			{
				if(divide)
				{
					hypoteneous = tempdot*tempdot + tempcross*tempcross;
					tempcross = tempcross/hypoteneous;
					tempdot = tempdot/hypoteneous;
				}
				divide = !divide;
				temptotalcross = totalcross*tempdot + tempcross*totaldot;
				temptotaldot = totaldot*tempdot - totalcross*tempcross;
				if((totalcross >= 0) ^ (temptotalcross >= 0))
				{
					if(totalcross >=0 && tempcross > 0 && tour == 0)
					{
						Clockwise = true;
						HalfTour = true;
					}
					if(totalcross < 0 && tempcross < 0 && tour == 0)
					{
						Clockwise = false;
						HalfTour = true;
					}
					if(totalcross < 0 && tempcross > 0 && HalfTour) tour++;
					if(totalcross >=0 && tempcross < 0 && HalfTour) tour--;
				}
				totalcross = temptotalcross;
				totaldot = temptotaldot;
			}
		}
		RETemp = CTemp->NextWall(RETemp);
	}
	list<PlaneWall*>::iterator it, itp, start, end;
	if((FlagCount > 1 || Walls.size() == 2) && RecursiveValidity)
	{
		Room* RTemp;
		start = R->Walls.begin();
		end = R->Walls.end();
		itp = end;
		itp--;
		for(it = start; it != end; it++)
		{
			if((*it)->Target == (*itp)->Target && (*it)->Target != this)
			{
				RTemp = (*it)->Target->DetermineRoom(*itp, *it, false);
				if(RTemp)
				{
					if((*it)->Target->FlagCount == 1 && (*it)->Target->Walls.size() != 2) Valid = false;
					if((int) (*it)->Target > (int) this) Valid = false;
				}
			}
			itp = it;
		}
	}
	if(ClockwiseValidity && !Clockwise || !Valid)
	{
		delete R;
		return 0;
	}
	return R;
}

void Corner::AddWall(PlaneWall* W)
{
	bool Found = false;
	list<PlaneWall*>::iterator it, end;
	it = Walls.begin();
	end = Walls.end();
	while(it != end && !Found)
		if(W->AngleAt(this) > (*it)->AngleAt(this)) Found = true;
		else it++;
	Walls.insert(it,W);
}

PlaneWall* Corner::JoinWalls(list<PlaneWall*> *ExistingWalls)
{
	Vector2d D1, D2;
	Corner *EndCorner1, *EndCorner2;
	list<PlaneWall*>::iterator itw;
	itw = Walls.begin();
	PlaneWall *W1 = *itw;
	itw++;
	PlaneWall *W2 = *itw;
	D1 = *W1->GetDirection();
	D2 = *W2->GetDirection();
	D1 = D1/D1.Abs();
	D2 = D2/D2.Abs();
	if(D1*D2 > 0.1 || D1*D2 < -0.1) return 0;
	if(W1->Corner1 == this) EndCorner1 = W1->Corner2;
	else EndCorner1 = W1->Corner1;
	if(W2->Corner1 == this) EndCorner2 = W2->Corner2;
	else EndCorner2 = W2->Corner1;
	W1->SetPosition(EndCorner1->Position, EndCorner2->Position);
	W2->MoveWallElements(W1);
	EndCorner2->Walls.remove(W2);
	ExistingWalls->remove(W2);
	delete W2;
	EndCorner2->AddWall(W1);
	W1->Corner1	= EndCorner1;
	W1->Corner2 = EndCorner2;
	return W1;
}

// RoomEdge Implementation


//	Room Implementation

bool Room::SameWith(Room* R)
{
	list<PlaneWall*>::iterator it1, it2, end1, end2;
	it1 = Walls.begin();
	end1 = Walls.end();
	it2 = R->Walls.begin();
	end2 = R->Walls.end();
	while(it1 != it2 && it1 != end1) it1++;
	if(it1 == end1) return false;
	for(; it2 != end2; it2++)
	{
		if(it1 == end1) it1 = Walls.begin();
		if(it1 != it2) return false;
		it1++;
	}
	return true;
}

void PlanElement::DrawConnections(CDC* pDC, int Scale)
{
	if(Source != 0)
	{
		pDC->MoveTo(Source->RenderPosition.x*Scale, Source->RenderPosition.y*Scale);
		pDC->LineTo(RenderPosition.x*Scale, RenderPosition.y*Scale);
	}
}

void Boite::DrawConnections(CDC* pDC, int Scale)
{
	list<Point2d>::iterator it, start, end;
	pDC->MoveTo(RenderPosition.x*Scale, RenderPosition.y*Scale);
	start = PathPoints.begin();
	end = PathPoints.end();
	for(it = start; it != end; it++)
	{
		pDC->LineTo((it)->x*Scale, (it)->y*Scale);
	}
}

void Boite::Draw(CDC* pDC, int Scale)
{
	double r = 0.075;
/*	list<Point2d>::iterator it, start, end;
	pDC->MoveTo(RenderPosition.x*Scale, RenderPosition.y*Scale);
	start = PathPoints.begin();
	end = PathPoints.end();
	for(it = start; it != end; it++)
	{
		pDC->LineTo((it)->x*Scale, (it)->y*Scale);
	}
*/
	pDC->Ellipse((RenderPosition.x - r)*Scale, (RenderPosition.y + r)*Scale, (RenderPosition.x + r)*Scale, (RenderPosition.y - r)*Scale);
}

void DistributionBox::Draw(CDC* pDC, int Scale)
{
	CPoint Points[4];
	Vector2d V1, V2, V3, V4;
	Point2d PStart, PEnd, PTemp1, PTemp2, PTemp3, PTemp4;
	CPoint point;
	CBrush* TempBrush;
	V1=Vector2d(&RenderPosition, &SourcePosition);
	V1=V1/V1.Abs();
	V2.x=V1.y;
	V2.y=-V1.x;
	V3=V2-V1;
	V3=V3/1.414213;

	PTemp1=0.15*V1 - 0.3*V2 + RenderPosition;
	PTemp2=-0.15*V1 - 0.3*V2 + RenderPosition;
	PTemp3=-0.15*V1 + 0.3*V2 + RenderPosition;
	PTemp4=0.15*V1 + 0.3*V2 + RenderPosition;
	Points[0].x = PTemp1.x*Scale;
	Points[0].y = PTemp1.y*Scale;
	Points[1].x = PTemp2.x*Scale;
	Points[1].y = PTemp2.y*Scale;
	Points[2].x = PTemp3.x*Scale;
	Points[2].y = PTemp3.y*Scale;
	TempBrush = (CBrush*) pDC->SelectStockObject(BLACK_BRUSH);
	pDC->Polygon(Points, 3);
	Points[1].x = PTemp4.x*Scale;
	Points[1].y = PTemp4.y*Scale;
	pDC->SelectStockObject(WHITE_BRUSH);
	pDC->Polygon(Points, 3);
	pDC->SelectObject(TempBrush);

}

void Switch::Draw(CDC* pDC, int Scale)
{
	double r = 0.10;
	Vector2d V1, V2;
	Point2d PTemp1;
/*	if(Source != 0)
	{
		pDC->MoveTo(Source->RenderPosition.x*Scale, Source->RenderPosition.y*Scale);
		pDC->LineTo(RenderPosition.x*Scale, RenderPosition.y*Scale);
	}
*/
	V1=Vector2d(&SourcePosition, &RenderPosition);
	V1=V1/V1.Abs();
	pDC->MoveTo(RenderPosition.x*Scale, RenderPosition.y*Scale);
	PTemp1=0.3*V1 + RenderPosition;
	pDC->LineTo(PTemp1.x*Scale, PTemp1.y*Scale);

	V2.x=V1.y;
	V2.y=-V1.x;
	PTemp1=-0.1*V2+PTemp1;
	pDC->LineTo(PTemp1.x*Scale, PTemp1.y*Scale);
	pDC->Ellipse((RenderPosition.x - r)*Scale, (RenderPosition.y + r)*Scale, (RenderPosition.x + r)*Scale, (RenderPosition.y - r)*Scale);

}

void Lamp::Draw(CDC* pDC, int Scale)
{
	CPoint point;
	double r = 0.15;
/*	if(Source != 0)
	{
		pDC->MoveTo(Source->RenderPosition.x*Scale, Source->RenderPosition.y*Scale);
		pDC->LineTo(RenderPosition.x*Scale, RenderPosition.y*Scale);
	}
*/
	pDC->Ellipse((RenderPosition.x - r)*Scale, (RenderPosition.y + r)*Scale, (RenderPosition.x + r)*Scale, (RenderPosition.y - r)*Scale);
	r = r/1.4142;
	point = CPoint((RenderPosition.x - r)*Scale, (RenderPosition.y + r)*Scale);
	pDC->MoveTo(point);
	point = CPoint((RenderPosition.x + r)*Scale, (RenderPosition.y - r)*Scale);
	pDC->LineTo(point);
	point = CPoint((RenderPosition.x + r)*Scale, (RenderPosition.y + r)*Scale);
	pDC->MoveTo(point);
	point = CPoint((RenderPosition.x - r)*Scale, (RenderPosition.y - r)*Scale);
	pDC->LineTo(point);
}

void Prise::Draw(CDC* pDC, int Scale)
{
	double r = 0.15;
	Vector2d V1, V2, V3, V4;
	Point2d PStart, PEnd, PTemp1, PTemp2;
	CPoint point;
/*	if(Source != 0)
	{
		pDC->MoveTo(Source->RenderPosition.x*Scale, Source->RenderPosition.y*Scale);
		pDC->LineTo(RenderPosition.x*Scale, RenderPosition.y*Scale);
	}
*/
	V1=Vector2d(&RenderPosition, &SourcePosition);
	V1=V1/V1.Abs();
	V2.x=V1.y;
	V2.y=-V1.x;
	V3=V2-V1;
	V3=V3/1.414213;

	PTemp1=0.15*V3 + RenderPosition;
	pDC->MoveTo(PTemp1.x*Scale, PTemp1.y*Scale);
	PTemp1=0.15*V3 + PTemp1;
	pDC->LineTo(PTemp1.x*Scale, PTemp1.y*Scale);
	
	V4.x=V3.y;
	V4.y=-V3.x;
	PTemp2=0.08*V4+PTemp1;
	pDC->MoveTo(PTemp2.x*Scale, PTemp2.y*Scale);
	PTemp2=-0.08*V4+PTemp1;
	pDC->LineTo(PTemp2.x*Scale, PTemp2.y*Scale);

	PTemp1=0.05*V3+PTemp1;
	PTemp2=0.04*V4+PTemp1;
	pDC->MoveTo(PTemp2.x*Scale, PTemp2.y*Scale);
	PTemp2=-0.04*V4+PTemp1;
	pDC->LineTo(PTemp2.x*Scale, PTemp2.y*Scale);

	PTemp1=0.05*V3+PTemp1;
	PTemp2=0.02*V4+PTemp1;
	pDC->MoveTo(PTemp2.x*Scale, PTemp2.y*Scale);
	PTemp2=-0.02*V4+PTemp1;
	pDC->LineTo(PTemp2.x*Scale, PTemp2.y*Scale);


	PEnd=r*V2 + RenderPosition;
	PStart=-r*V2 + RenderPosition;
	pDC->Arc((RenderPosition.x - r)*Scale, (RenderPosition.y + r)*Scale, (RenderPosition.x + r)*Scale, (RenderPosition.y - r)*Scale, PStart.x*Scale, PStart.y*Scale, PEnd.x*Scale, PEnd.y*Scale);
	pDC->MoveTo(PStart.x*Scale, PStart.y*Scale);
	pDC->LineTo(PEnd.x*Scale, PEnd.y*Scale);
}

// LANNode Implementation

LANNode* LANNode::Select(Point2d point, int Scale)
{
	if((Position.x - point.x)*(Position.x - point.x)*Scale*Scale + (Position.y - point.y)*(Position.y - point.y)*Scale*Scale < 900)
	{
		Selected = true;
		return this;
	}
	Selected = false;
	return NULL;
}


double WNAntenna::PropagateThrough(LineSegment* L)
{
	Vector* V = L->GetDirection();
	double d = V->x*V->x + V->y*V->y + V->z*V->z;
	return Power/(4*3.1415*d);
}

void AP::Draw(CDC* pDC, int Scale)
{
	int i,j;
	int Mask[15][16] = {{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
						{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
						{0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0},
						{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
						{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
						{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
						{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
						{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
						{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
						{0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
						{0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
						{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0}};

	COLORREF Src[15][16] = {{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(0,0,0),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(0,0,0),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(0,0,0),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(0,0,0),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(0,0,0),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(66,66,168)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(66,66,168),RGB(96,96,192)},
							{RGB(133,133,207),RGB(133,133,207),RGB(133,133,207),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(66,66,168),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(133,133,207),RGB(133,133,207),RGB(133,133,207),RGB(133,133,207),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(66,66,168),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(133,133,207),RGB(133,133,207),RGB(133,133,207),RGB(96,96,192),RGB(96,96,192),RGB(66,66,168),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(133,133,207),RGB(133,133,207),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)},
							{RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192),RGB(96,96,192)}};
	for(i=0; i<16; i++)
		for(j=0; j<15; j++)
			if(Mask[j][i]) pDC->FillSolidRect(Scale*Position.x - 21 + 3*i, Scale*Position.y + 21 - 3*j, 3, 3, (Selected == false)? Src[j][i]: RGB(128,128,128));
			
}

CArchive& operator<< (CArchive& ar, AP& N)
{
	CString NName = N.Name;
	CString NWNAntennaType = N.Antenna.Type;
	ar << N.Position.x << N.Position.y << N.Offset << NName << NWNAntennaType << N.Antenna.Power;
	return ar;
}

CArchive& operator>> (CArchive& ar, AP& N)
{
	CString NName, NWNAntennaType;
	ar >> N.Position.x >> N.Position.y >> N.Offset >> NName >> NWNAntennaType >> N.Antenna.Power;
	strcpy(N.Name, (LPCTSTR) NName);
	strcpy(N.Antenna.Type, (LPCTSTR) NWNAntennaType);
	return ar;
}

// Floor Implementation

void Floor::SetAltitude(double altitude)
{
	list<PlaneWall*>::iterator start, end, it;
	start = Walls.begin();
	end = Walls.end();
	for(it = start; it != end; ++it) (*it)->SetAltitude(altitude);
	Altitude = altitude;
}

void Floor::SetHeight(double height)
{
	list<PlaneWall*>::iterator start, end, it;
	start = Walls.begin();
	end = Walls.end();
	for(it = start; it != end; ++it) (*it)->SetAltitude(height);
	Height = height;
}

int Floor::CheckWallValidity(PlaneWall* Wall)
{
	list<PlaneWall*>::iterator it, end;
	it = Walls.begin();
	end= Walls.end();
	for(; it != end; it++)
	{
		if(*it != Wall) if(Wall->CheckValidityWith(*it) == 0) return 0;
	}
	return -1;
}

void Floor::DeleteCornersTo(PlaneWall* Wall)
{
	Corner* TempCorner;

	TempCorner = Wall->Corner1;
	if(TempCorner)
	{
		TempCorner->Walls.remove(Wall);
		if(TempCorner->Walls.size() == 2)
		{
			if(TempCorner->JoinWalls(&Walls))
			{
				Corners.remove(TempCorner);
				delete TempCorner;
			}
		}
		else if(TempCorner->Walls.size() == 0)
		{
			Corners.remove(TempCorner);
			delete TempCorner;
		}
		Wall->Corner1 = 0;
	}

	TempCorner = Wall->Corner2;
	if(TempCorner)
	{
		TempCorner->Walls.remove(Wall);
		if(TempCorner->Walls.size() == 2)
		{
			if(TempCorner->JoinWalls(&Walls))
			{
				Corners.remove(TempCorner);
				delete TempCorner;
			}
		}
		else if(TempCorner->Walls.size() == 0)
		{
			Corners.remove(TempCorner);
			delete TempCorner;
		}
		Wall->Corner2 = 0;
	}
}

void Floor::AddCornersTo(PlaneWall* Wall, bool JoinWalls)
{
	PlaneWall* NewWall;
	list<Corner*> NewCorners;
	list<Corner*>::iterator itc, endc;
	list<PlaneWall*>::iterator it, end;
	Point2d P2d1, P2d2;
	Vector2d* V2d;
	it = Walls.begin();
	end= Walls.end();
//AfxMessageBox("Mark Position a");
	for(; it != end; it++) if(*it != Wall) (*it)->AddCornersTo(Wall, &NewCorners, &Corners, &Walls);

	P2d1 = Point2d(Wall->GetPoint()->x, Wall->GetPoint()->y);
	V2d = Wall->GetDirection();
	P2d2 = *V2d + P2d1;
//AfxMessageBox("Mark Position b");

	Corner *NewCorner, *MarkCorner;
	if(Wall->Corner1 == 0)
	{
		NewCorner = new Corner(P2d1);
		Wall->Corner1 = NewCorner;
		NewCorner->Walls.push_back(Wall);
		Corners.push_back(NewCorner);
//AfxMessageBox("Mark Position b1");
	}
	if(Wall->Corner2 == 0)
	{
		NewCorner = new Corner(P2d2);
		Wall->Corner2 = NewCorner;
		NewCorner->Walls.push_back(Wall);
		Corners.push_back(NewCorner);
//AfxMessageBox("Mark Position b2");
	}

	if(!JoinWalls) return;

	NewWall = Wall;
	NewCorner = NewWall->Corner1;
	MarkCorner = NewWall->OtherCorner(NewCorner);
	if(NewCorner->Walls.size()==2)
	{
		NewWall = NewCorner->JoinWalls(&Walls);
		if(NewWall == 0)
		{
			NewWall = Wall;
		}
		else
		{
			Corners.remove(NewCorner);
			delete NewCorner;
		}
	}

	if(NewWall->Corner1 == MarkCorner)
	{
		NewWall->Corner1 = NewWall->Corner2;
		NewWall->Corner2 = MarkCorner;
	}

	itc = NewCorners.begin();
	endc = NewCorners.end();
	for(; itc != endc; itc++)
	{
		NewWall = NewWall->AddCorner(*itc);
		Walls.push_front(NewWall);
	}

//	Wall = NewWall;
	NewCorner = NewWall->Corner2;
	if(NewCorner->Walls.size()==2)
	{
		NewWall = NewCorner->JoinWalls(&Walls);
		if(NewWall == 0)
		{
			NewWall = Wall;
		}
		else
		{
			Corners.remove(NewCorner);
			delete NewCorner;
		}
	}

	SelectedWall = NewWall;
//AfxMessageBox("Mark Position c");

}

PlaneWall* Floor::GetSelectedWallCopy(void)
{
	return SelectedWall->GetDraftCopy();
}

PlaneWallElement* Floor::GetSelectedElementCopy(void)
{
	return SelectedWallElement->GetDraftCopy();
}

void Floor::AddWall(void)
{
	PlaneWall* TempWall = new PlaneWall();
	SelectedWall = TempWall;
	Walls.push_back(TempWall);
}

void Floor::SetWall(Point2d point1, Point2d point2)
{
//AfxMessageBox("Mark Position 1");
	DeleteCornersTo(SelectedWall);
//AfxMessageBox("Mark Position 2");
	SelectedWall->SetRectangle(Point(point1.x, point1.y, Altitude), Vector2d(&point1, &point2), Height);
//AfxMessageBox("Mark Position 3");
	AddCornersTo(SelectedWall);
//AfxMessageBox("Mark Position 4");
}

void Floor::RemoveWall(void)
{
	DeleteCornersTo(SelectedWall);
	Walls.remove(SelectedWall);
	delete SelectedWall;
}

Room* Floor::GetRoom(Point2d *P, Room* R1, Point2d* P1)
{
	return 0;
}

Room* Floor::GetRoom(Point2d P)
{
	bool Found = false;
	Point2d P1, P2;
	double distance, tempdistance;
	Ray2d L;
	Room *R1;
	PlaneWall *RE1;
	int n;
	list<PlaneWall*>::iterator it, end, it1, end1;
	R1 = *(Rooms.begin());
	RE1 = *(R1->Walls.begin());
	P1 = Point2d((RE1->Corner2->Position.x + RE1->Corner1->Position.x)/2, (RE1->Corner2->Position.y + RE1->Corner1->Position.y)/2);
	distance = (P1.x - P.x)*(P1.x - P.x) + (P1.y - P.y)*(P1.y - P.y);
	L = Ray2d(P, &P1);
	while(!Found)
	{
		n = 0;
		Found = true;
		it = R1->Walls.begin();
		end = R1->Walls.end();
		for(; it != end; it++)
		{
			if(*it != RE1 || true)
			{
				if((*it)->Intersect2d(&L,&P2) != 0)
				{
					n++;
					tempdistance = (P2.x - P.x)*(P2.x - P.x) + (P2.y - P.y)*(P2.y - P.y);
					if(tempdistance < distance)
					{
						distance = tempdistance;
//						R1 = (*it)->OtherRoom(R1);
						RE1 = *it;
						P1 = P2;
//						Found = false;
					}
				}
			}
		}
		if((n%2) == 0)
		{
			if(R1 == Outdoor) return Outdoor;
			R1 = RE1->OtherRoom(R1);
			Found = false;
		}
	}
	return R1;
}

void Floor::DeleteRooms(void)
{
	list<Room*>::iterator it, end;
	end = Rooms.end();
	for(it = Rooms.begin(); it != end; it++) delete *it;
}

void Floor::DetermineRoom(Corner* Flag)
{
	Room* TempRoom;
	list<PlaneWall*>::iterator it, itp, end;
	it = Flag->Walls.begin();
	end = Flag->Walls.end();
	itp = end;
	itp--;
	for(; it != end; it++)
	{
		if((*it)->Target == Flag && (*itp)->Target == Flag)
		{
			TempRoom = Flag->DetermineRoom(*itp, *it);
			if(TempRoom)
			{
				Rooms.push_back(TempRoom);
			}
		}
		itp = it;
	}
}

void Floor::AddRoomFlag(Corner* C)
{
	bool Found = false;
	list<Corner*>::iterator it, end;
	it = RoomFlags.begin();
	end = RoomFlags.end();
	C->FlagCount++;
	for(; it!= end; it++)
		if(*it == C) Found = true;
	if(!Found) RoomFlags.push_back(C);
}

void Floor::DetermineRooms(void)
{
	list<Corner*> TempCorners1, TempCorners2;
	list<Corner*>::iterator it, end, it3, end3;
	list<PlaneWall*> TempWalls;
	list<PlaneWall*>::iterator it2, end2;
	bool Found = false;

	DeleteRooms();
//	Find a Corner to start with
	Corner* Start = *(Corners.begin());

//	Preload the list with the initial Corner
	TempCorners1.push_back(Start);

//	Mark RoomFlags
	it = TempCorners1.begin();
	end = TempCorners1.end();
	while(TempCorners1.size() > 0)
	{
		for(; it != end; it++)
		{
			it2 = (*it)->Walls.begin();
			end2 = (*it)->Walls.end();
			for(; it2 != end2; it2++)
			{
				if((*it2)->Target == 0)
				{
					(*it2)->Target = (*it2)->OtherCorner(*it);
					Found = false;
					it3 = TempCorners1.begin();
					end3 = TempCorners1.end();
					for(; it3 != end3; it3++) if(*it3 == (*it2)->Target) Found = true;
					if(Found)
					{
						AddRoomFlag((*it2)->Target);
					}
					else
					{
						it3 = TempCorners2.begin();
						end3 = TempCorners2.end();
						for(; it3 != end3; it3++) if(*it3 == (*it2)->Target) Found = true;
						if(Found)
						{
							AddRoomFlag((*it2)->Target);
						}
						else TempCorners2.push_back((*it2)->Target);
					}
				}
			}
		}
		TempCorners1.clear();
		TempCorners1.insert(TempCorners1.end(),TempCorners2.begin(), TempCorners2.end());
		TempCorners2.clear();
		it = TempCorners1.begin();
		end = TempCorners1.end();
	}

//	Find Rooms
	it = RoomFlags.begin();
	end = RoomFlags.end();
	for(; it != end; it++)
	{
		DetermineRoom(*it);
	}

//	Join Walls into Rooms
	list<Room*>::iterator itr, startr, endr;
	itr = Rooms.begin();
	endr = Rooms.end();
	for(; itr != endr; itr++)
	{
		it2 = (*itr)->Walls.begin();
		end2 = (*itr)->Walls.end();
		for(; it2 != end2; it2++)
		{
			if((*it2)->Room1 == 0) (*it2)->Room1 = *itr;
			else (*it2)->Room2 = *itr;
		}
	}
	Outdoor = new Room;
// Find an outer wall to start with
	PlaneWall *TempWall1;
	it2 = Walls.begin();
	Found = false;
	while(!Found)
	{
		if((*it2)->Room1 == 0 || (*it2)->Room2 == 0)
		{
			TempWall1 = *it2;
			if((*it2)->Room1 == 0) (*it2)->Room1 = Outdoor;
			else (*it2)->Room2 = Outdoor;
			Found = true;
		}
		it2++;
	}
// Determine the Outer Room
	Outdoor->Walls.push_back(TempWall1);
	Corner *TempCorner1, *TempCorner2;
	TempCorner1 = TempWall1->Corner1;
	TempCorner2 = TempWall1->Corner2;
	while(TempCorner1 != TempCorner2)
	{
		it2 = TempCorner2->Walls.begin();
		Found = false;
		while(!Found)
		{
			if((*it2)->Room1 == 0 && TempWall1 != *it2)
			{
				TempWall1 = *it2;
				TempWall1->Room1 = Outdoor;
				Found = true;
			}
			if((*it2)->Room2 == 0 && TempWall1 != *it2)
			{
				TempWall1 = *it2;
				TempWall1->Room2 = Outdoor;
				Found = true;
			}
			it2++;
		}
		Outdoor->Walls.push_back(TempWall1);
		TempCorner2 = TempWall1->OtherCorner(TempCorner2);
	}
}

void Floor::DeterminePathGraph(void)
{
	double d1, d2;
	PlaneWall* TempWall;
	Corner *C1, *C2;
	list<Corner*> TempCorners1, TempCorners2;
	list<Corner*>::iterator it, end, it3, end3;
	list<PlaneWall*> TempWalls;
	list<PlaneWall*>::iterator it2, end2;
	bool Found = false;

	it2 = Walls.begin();
	end2 = Walls.end();
	for(; it2 != end2; it2++)
	{
		(*it2)->Target = 0;
	}

	TempWall = TheDistributionBox->ConnectedWall;
	C1 = TempWall->Corner1;
	C2 = TempWall->Corner2;
	d1 = (C1->Position.x - TheDistributionBox->Position.x)*(C1->Position.x - TheDistributionBox->Position.x) + (C1->Position.y - TheDistributionBox->Position.y)*(C1->Position.y - TheDistributionBox->Position.y);
	d2 = (C2->Position.x - TheDistributionBox->Position.x)*(C2->Position.x - TheDistributionBox->Position.x) + (C2->Position.y - TheDistributionBox->Position.y)*(C2->Position.y - TheDistributionBox->Position.y);
	if(d1 < d2) GraphStart = C1;
	else GraphStart = C2;

//	Preload the list with the initial Corner
	TempCorners1.push_back(GraphStart);

//	Mark RoomFlags
	it = TempCorners1.begin();
	end = TempCorners1.end();
	while(TempCorners1.size() > 0)
	{
		for(; it != end; it++)
		{
			it2 = (*it)->Walls.begin();
			end2 = (*it)->Walls.end();
			for(; it2 != end2; it2++)
			{
				if((*it2)->Target == 0)
				{
					(*it2)->Target = (*it2)->OtherCorner(*it);
					Found = false;
					it3 = TempCorners1.begin();
					end3 = TempCorners1.end();
					for(; it3 != end3; it3++) if(*it3 == (*it2)->Target) Found = true;
					if(!Found)
					{
						it3 = TempCorners2.begin();
						end3 = TempCorners2.end();
						for(; it3 != end3; it3++) if(*it3 == (*it2)->Target) Found = true;
						if(!Found)
							TempCorners2.push_back((*it2)->Target);
					}
				}
			}
		}
		TempCorners1.clear();
		TempCorners1.insert(TempCorners1.end(),TempCorners2.begin(), TempCorners2.end());
		TempCorners2.clear();
		it = TempCorners1.begin();
		end = TempCorners1.end();
	}
}

void Floor::DeterminePlanElements(void)
{
	int i, res0, res1, res2;
	double d, d1, d2, dx, dy;
	Point2d POr, PRen;
	Vector2d *V1, *V2;
	Corner* Corners[4];
	Corner *TempCorner1;
	PlaneWall *TempWall1;
	Room *R1;
	DistributionBox* Dbx;
	Lamp* L;
	Switch* Swt;
	Prise* Prs;
	list<Room*>::iterator itr, startr, endr;
	list<PlaneWall*>::iterator itw, startw, itpw, endw;
	Dbx = 0;
	startr = Rooms.begin();
	endr = Rooms.end();
	for(itr = startr; itr != endr; itr++)
	{
		i = 0;
		dx = 0;
		dy = 0;
		startw = (*itr)->Walls.begin();
		endw = (*itr)->Walls.end();
		itpw = endw;
		itpw--;
		itw = startw;
		if((*itw)->Corner1 == (*itpw)-> Corner1 || (*itw)->Corner1 == (*itpw)->Corner2)
			TempCorner1 = (*itw)->Corner1;
		else
			TempCorner1 = (*itw)->Corner2;
		TempWall1 = *itw;
		for(; itw != endw; itw++)
		{
			V1 = (*itpw)->GetDirection();
			V2 = (*itw)->GetDirection();
			d = (*V1)*(*V2);
			if(d > tollerance || d < -tollerance)
			{
				dx+= TempCorner1->Position.x;
				dy+= TempCorner1->Position.y;
				if(i < 4) Corners[i] = TempCorner1;
				i++;
			}
//Determine Distribution Box
			if(Dbx == 0)
			{
				res0 = (*itw)->PlaceDistributionBox(&POr,&PRen, Outdoor);
				if(res0 == 1)
				{
					R1 = GetRoom(PRen);
					if(R1 == *itr)
					{
						Dbx = new DistributionBox();
						Dbx->SetPosition(POr, PRen);
						Dbx->SetSourcePosition(POr);
						Dbx->ConnectedWall = *itw;
						Dbx->HostRoom = *itr;
//						(*itr)->Switches.push_back(Dbx);
						PlanElements.push_back(Dbx);
						TheDistributionBox = Dbx;
					}
				}
			}

// Determine Switches
			res1 = (*itw)->PlaceSwitch(&POr,&PRen);
			if(res1 == 1)
			{
				R1 = GetRoom(PRen);
				if(R1 == *itr)
				{
					Swt = new Switch();
					Swt->SetPosition(POr, PRen);
					Swt->SetSourcePosition(POr);
					Swt->ConnectedWall = *itw;
					Swt->HostRoom = *itr;
					(*itr)->Switches.push_back(Swt);
					PlanElements.push_back(Swt);
				}
			}
// Determine Prises
			res2 = (*itw)->PlacePrise(&POr,&PRen);
			if(res2 == 1)
			{
				R1 = GetRoom(PRen);
				if(R1 == *itr)
				{
					Prs = new Prise();
					Prs->SetPosition(POr, PRen);
					Prs->SetSourcePosition(POr);
					Prs->ConnectedWall = *itw;
					Prs->HostRoom = *itr;
					(*itr)->Prises.push_back(Prs);
					PlanElements.push_back(Prs);
				}
			}

			TempCorner1 = (*itw)->OtherCorner(TempCorner1);
			itpw = itw;
		}
// Determine Lamps
		if(i != 4)
		{
			dx/=i;
			dy/=i;
			L = new Lamp(Point2d(dx,dy));
			L->HostRoom = *itr;
			(*itr)->Lamps.push_back(L);
			PlanElements.push_back(L);
		}
		else
		{
			dx/=4;
			dy/=4;
			d1 = (Corners[0]->Position.x - Corners[1]->Position.x)*(Corners[0]->Position.x - Corners[1]->Position.x) + (Corners[0]->Position.y - Corners[1]->Position.y)*(Corners[0]->Position.y - Corners[1]->Position.y);
			d1 = sqrt(d1);
			d2 = (Corners[2]->Position.x - Corners[1]->Position.x)*(Corners[2]->Position.x - Corners[1]->Position.x) + (Corners[2]->Position.y - Corners[1]->Position.y)*(Corners[2]->Position.y - Corners[1]->Position.y);
			d2 = sqrt(d2);
			L = new Lamp(Point2d(dx,dy));
			L->HostRoom = *itr;
			(*itr)->Lamps.push_back(L);
			PlanElements.push_back(L);
		}

	}
}

void Floor::DeterminePlanConnections(void)
{
	int i;
	double d1;
	Point2d PointAvg1, PointAvg2, TempPoint, TempPoint1, TempPoint2, TempPoint3;
	Vector2d V1, V2, V3;
	LineSegment2d L1, L2;
	Boite* Bt;
	Switch* Swt;
	Prise* Prs;
	Lamp* L;

	Corner *TempCorner, *TempCorner1, *TempCorner2;
	PlaneWall *TempWall, *TempWall2;
	list<PlaneWall*> PathWalls;
	list<PlaneWall*>::iterator itw, startw, endw;
	list<Corner*> PathCorners;
	list<Room*>::iterator itr, startr, endr;
	list<Lamp*>::iterator itle, startle, endle;
	list<Switch*>::iterator itse, startse, endse;
	list<Prise*>::iterator itpe, startpe, endpe;
	list<PlanElement*>::iterator ite, starte, ende;
	
	DeterminePathGraph();

	startw = Walls.begin();
	endw = Walls.end();
	for(itw = startw; itw != endw; itw++)
	{
		(*itw)->i1 = 0;
		(*itw)->i2 = 0;
	}

	startr = Rooms.begin();
	endr = Rooms.end();
	for(itr = startr; itr != endr; itr++)
	{	
		i = 0;
		PointAvg1.x = 0;
		PointAvg1.y = 0;
		PointAvg2.x = 0;
		PointAvg2.y = 0;
		Bt = new Boite();
		Bt->HostRoom = *itr;

		startse = (*itr)->Switches.begin();
		endse = (*itr)->Switches.end();
		for(itse = startse; itse != endse; itse++)
		{
			Swt = *itse;
			Swt->Source = Bt;
			PointAvg1.x+= Swt->SourcePosition.x;
			PointAvg1.y+= Swt->SourcePosition.y;
			PointAvg2.x+= Swt->RenderPosition.x;
			PointAvg2.y+= Swt->RenderPosition.y;
			Bt->ConnectedElements.push_back(Swt);
			i++;
		}

		startle = (*itr)->Lamps.begin();
		endle = (*itr)->Lamps.end();
		for(itle = startle; itle != endle; itle++)
		{
			L = *itle;
			L->Source = Bt;
			TempPoint = Swt->ConnectedWall->ClosestPoint2dTo(&L->RenderPosition);
			PointAvg1.x += TempPoint.x;
			PointAvg1.y += TempPoint.y;
			PointAvg2.x+= L->RenderPosition.x;
			PointAvg2.y+= L->RenderPosition.y;
			Bt->ConnectedElements.push_back(L);
			i++;
		}

		startpe = (*itr)->Prises.begin();
		endpe = (*itr)->Prises.end();
		for(itpe = startpe; itpe != endpe; itpe++)
		{
			Prs = *itpe;
			Prs->Source = Bt;
			PointAvg1.x+= Prs->SourcePosition.x;
			PointAvg1.y+= Prs->SourcePosition.y;
			PointAvg2.x+= Prs->RenderPosition.x;
			PointAvg2.y+= Prs->RenderPosition.y;
			Bt->ConnectedElements.push_back(Prs);
			i++;
		}

		PointAvg1.x/=i;
		PointAvg1.y/=i;
		PointAvg2.x/=i;
		PointAvg2.y/=i;
		V1 = Vector2d(&PointAvg1, &PointAvg2);
		V1 = V1/V1.Abs();
		PointAvg2 = 0.1*V1 + PointAvg1;
		Bt->Position = PointAvg1;
		Bt->RenderPosition = PointAvg2;
		Bt->ConnectedWall = Swt->ConnectedWall;
		(*itr)->Boites.push_back(Bt);
		PlanElements.push_back(Bt);

		starte = Bt->ConnectedElements.begin();
		ende = Bt->ConnectedElements.end();
		for(ite = starte; ite != ende; ite++)
		{
			(*ite)->SourcePosition = PointAvg1;
		}

		i = 0;
		V3.x = 0;
		V3.y = 0;
		TempPoint = Bt->Position;
		TempPoint2 = Bt->RenderPosition;
		TempWall = Bt->ConnectedWall;
		TempCorner = TempWall->OtherCorner(TempWall->Target);

		while(TempCorner != GraphStart)
		{
			TempCorner2 = 0;
			startw = TempCorner->Walls.begin();
			endw = TempCorner->Walls.end();
			for(itw = startw; itw != endw; itw++)
			{
				if((*itw)->Target == TempCorner)
				{
					TempCorner1 = (*itw)->OtherCorner(TempCorner);
					if(TempCorner2 == 0)
					{
						TempCorner2 = TempCorner1;
						TempWall2 = *itw;
					}
					else
					{
						if((*itw)->Room1 != Outdoor && (*itw)->Room2 != Outdoor)
						{
							TempCorner2 = TempCorner1;
							TempWall2 = *itw;
						}
					}
				}
			}
			TempCorner1 = TempWall->OtherCorner(TempCorner);
			V1 = Vector2d(&(TempCorner1->Position), &(TempCorner->Position));
			V1 = 0.04*V1/V1.Abs();
			V2 = Vector2d(&(TempCorner->Position), &(TempCorner2->Position));
			V2 = 0.04*V2/V2.Abs();
			d1 = V1*V2;
			PathWalls.push_back(TempWall);
			if(d1 > tollerance || d1 < -tollerance)
			{
				startw = PathWalls.begin();
				endw = PathWalls.end();
				for(itw = startw; itw != endw; itw++)
				{
					if(d1 < 0)
					{
						(*itw)->i1++;
						if((*itw)->i1 > i) i = (*itw)->i1;
					}
					else
					{
						(*itw)->i2++;
						if((*itw)->i2 > i) i = (*itw)->i2;
					}
				}

				V2 = i*V2;
				TempPoint2 = V2 + V3 + TempPoint;
				Bt->PathPoints.push_back(TempPoint2);
				i = 0;
				V3 = V2;
				TempPoint = TempCorner->Position;
				PathWalls.clear();
			}
			TempWall = TempWall2;
			TempCorner = TempCorner2;

		}

		if(TempCorner == GraphStart && TempWall != TheDistributionBox->ConnectedWall)
		{
			TempWall2 = TheDistributionBox->ConnectedWall;
			TempCorner2 = TempWall2->OtherCorner(TempCorner);

			TempCorner1 = TempWall->OtherCorner(TempCorner);
			V1 = Vector2d(&(TempCorner1->Position), &(TempCorner->Position));
			V1 = 0.04*V1/V1.Abs();
			V2 = Vector2d(&(TempCorner->Position), &(TempCorner2->Position));
			V2 = 0.04*V2/V2.Abs();
			d1 = V1*V2;
			PathWalls.push_back(TempWall);
			if(d1 > tollerance || d1 < -tollerance)
			{
				startw = PathWalls.begin();
				endw = PathWalls.end();
				for(itw = startw; itw != endw; itw++)
				{
					if(d1 < 0)
					{
						(*itw)->i1++;
						if((*itw)->i1 > i) i = (*itw)->i1;
					}
					else
					{
						(*itw)->i2++;
						if((*itw)->i2 > i) i = (*itw)->i2;
					}
				}

				V2 = i*V2;
				TempPoint2 = V2 + V3 + TempPoint;
				Bt->PathPoints.push_back(TempPoint2);
				i = 0;
				V3 = V2;
				TempPoint = TempCorner->Position;
				PathWalls.clear();
			}
			TempWall = TempWall2;
			TempCorner = TempCorner2;
		}


		TempCorner1 = TempWall->OtherCorner(TempCorner);
		V1 = Vector2d(&(TempCorner1->Position), &(TempCorner->Position));
		V1 = 0.04*V1/V1.Abs();
		V2 = Vector2d(&TheDistributionBox->Position, &TheDistributionBox->RenderPosition);
		V2 = 0.04*V2/V2.Abs();
		d1 = V1*V2;
		if(d1 < 0)
		{
			TempWall->i1++;
			if(TempWall->i1 > i) i = TempWall->i1;
		}
		else
		{
			TempWall->i2++;
			if(TempWall->i2 > i) i = TempWall->i2;
		}
		V2 = i*V2;
		TempPoint2 = V2 + V3 + TempPoint;
		Bt->PathPoints.push_back(TempPoint2);
		TempPoint2 = V2 + TheDistributionBox->Position;
		Bt->PathPoints.push_back(TempPoint2);
		Bt->PathPoints.push_back(TheDistributionBox->RenderPosition);

	}

}

void Floor::AddWindow(void)
{
	SelectedWallElement = SelectedWall->AddWindow();
}

void Floor::SetWindow(Point2d point1, Point2d point2)
{
	SelectedWallElement->SetRectangle(Point(point1.x, point1.y, Altitude + 0.8), Vector2d(&point1, &point2), 2.4);
}

void Floor::AddDoor(void)
{
	SelectedWallElement = SelectedWall->AddDoor();
}

void Floor::SetDoor(Point2d point1, Point2d point2)
{
	SelectedWallElement->SetRectangle(Point(point1.x, point1.y, Altitude), Vector2d(&point1, &point2), 2.4);
}

void Floor::AddStud(void)
{
	SelectedWallElement = SelectedWall->AddStud();
}

void Floor::SetStud(Point2d point1, Point2d point2)
{
	SelectedWallElement->SetRectangle(Point(point1.x, point1.y, Altitude), Vector2d(&point1, &point2), Height);
}

void Floor::GetAPNames(char names[][16])
{
	list<AP*>::iterator start, end, it;
	end = APs.end();
	int i = 0;
	for(it = APs.begin(); it != end; ++it)
	{
		strcpy(names[i],(*it)->Name);
		i++;
	}
}

int Floor::CheckAPNameInvalidity(char name[])
{
	list<AP*>::iterator start, end, it;
	end = APs.end();
	for(it = APs.begin(); it != end; ++it) if(strcmp((*it)->Name, name) == 0) return 1;
	return 0;
}
/*
void Floor::GenerateCoverageMap(WLANNode* WN)
{
	Point P;
	int i = WN->WNNo;
	int j = 0;
	bool Continue = true;
	list<RoomEdgeImage*>::iterator it[6], end[6];
	Room* SourceRoom = WN->R;
	Room* TargetRoom = GetRoom(Point2d(P.x, P.y));
	RoomEdgeImage* ImageTree = TargetRoom->RoomEdgeImages[i];
	it[0] = ImageTree->RoomEdgeImages.begin();
	end[0] = ImageTree->RoomEdgeImages.end();
	while(it[0] != end[0])
	{
		(*it[j])->PropagateThrough(&P);
		if(Continue && j<6)
		{
			ImageTree = *it[j++];
			it[j] = ImageTree->RoomEdgeImages.begin();
			end[j] = ImageTree->RoomEdgeImages.end();
		}
		else it[j]++;
		if(it[j] == end[j] && j!=0)
		{
			ImageTree = *it[--j];
			it[j]++;
		}
	}
}
*/
Point2d Floor::Snap(Point2d P, bool ToSelected, bool Select, bool ExcludeCurrent)
{
	list<PlaneWall*>::iterator end, it;
	it = Walls.begin();
	end = Walls.end();
	if(Walls.size() == 0) return P;
	if(ToSelected) return SelectedWall->ClosestPoint2dTo(&P);
	if(Walls.size() == 1 && ExcludeCurrent) return P;
	Vector2d TempVector1, TempVector2;
	Point2d TempPoint;
	if(Select) SelectedWall = *it;
	Point2d ClosestPoint = (*it)->ClosestPoint2dTo(&P);
	TempVector1 = Vector2d(&P, &ClosestPoint);
	if(ExcludeCurrent) end--;
	for(it++; it != end; ++it)
	{
		TempPoint = (*it)->ClosestPoint2dTo(&P);
		TempVector2 = Vector2d(&P,&TempPoint);
		if(TempVector1.x * TempVector1.x + TempVector1.y * TempVector1.y > TempVector2.x * TempVector2.x + TempVector2.y * TempVector2.y)
		{
			if(Select) SelectedWall = *it;
			ClosestPoint = TempPoint;
			TempVector1 = Vector2d(&P, &ClosestPoint);
		}
	}
	return ClosestPoint;
}

void Floor::DrawWall(CDC* pDC, int Scale, CPen* WallPen, CPen* ElementPen, CPen* StudPen)
{
	SelectedWall->Draw(pDC, Scale, WallPen, ElementPen, StudPen);
}

void Floor::Draw(CDC* pDC, int Scale, CPen* WallPen, CPen* ElementPen, CPen* StudPen)
{
	list<PlaneWall*>::iterator end, it;
	end = Walls.end();
	for(it = Walls.begin(); it != end; ++it) (*it)->Draw(pDC, Scale, WallPen, ElementPen, StudPen);
}

void Floor::DrawLAN(CDC* pDC, int Scale)
{
	list<AP*>::iterator end, it;
	end = APs.end();
	for(it = APs.begin(); it != end; ++it) (*it)->Draw(pDC, Scale);
}

void Floor::DrawPlan(CDC* pDC, int Scale)
{
	list<PlanElement*>::iterator end, it;
	it = PlanElements.begin();
	end = PlanElements.end();
	for(; it != end; ++it) (*it)->DrawConnections(pDC, Scale);
	it = PlanElements.begin();
	for(; it != end; ++it) (*it)->Draw(pDC, Scale);
}

CArchive& operator<< (CArchive& ar, Floor& F)
{
	int  n;
	list<PlaneWall*>::iterator itw, endw;
	list<AP*>::iterator ita, enda;

	CString FName = F.Name;
	BYTE FHidden = (BYTE) F.Hidden;
	ar << F.Altitude << F.Height << FName << FHidden;
	
	n = F.Walls.size();
	ar << n;
	itw = F.Walls.begin();
	endw = F.Walls.end();
	for(; itw != endw; itw++)
	{
		ar << *(*itw);
	}

	n = F.APs.size();
	ar << n;
	ita = F.APs.begin();
	enda = F.APs.end();
	for(; ita != enda; ita++)
	{
		ar << *(*ita);
	}
	
	return ar;
}

CArchive& operator>> (CArchive& ar, Floor& F)
{
	int i, n;
	CString FName;
	BYTE FHidden;
	PlaneWall* NewWall;
	PlaneCeiling* TempCeiling;
	AP* NewAP;
	ar >> F.Altitude >> F.Height >> FName >> FHidden;
	strcpy(F.Name, (LPCTSTR) FName);
	F.Hidden = (bool) FHidden;
	TempCeiling = new PlaneCeiling(F.Altitude + F.Height);
	F.ceiling = TempCeiling;

	ar >> n;
	for(i=0; i<n; i++)
	{
		NewWall = new PlaneWall();
		F.SelectedWall = NewWall;
		F.Walls.push_back(NewWall);
		ar >> *NewWall;
//		F.DeleteCornersTo(NewWall);
		F.AddCornersTo(NewWall, false);
	}

	ar >> n;
	for(i=0; i<n; i++)
	{
		NewAP = new AP();
		F.APs.push_back(NewAP);
		ar >> *NewAP;
	}
	return ar;
}

void Floor::Dump(void)
{
	list<PlaneWall*>::iterator it, end;
	list<Corner*>::iterator itc, endc;
	FILE *TheFile;
	char tempstr[10], tempstr1[10], tempstr2[10];
	int i, j, tempint;
	Point *tempPoint;
	double tempdouble1, tempdouble2;
	TheFile = fopen("E:\\dump.txt", "w");
	it = Walls.begin();
	end = Walls.end();
	i = 0;
	for(; it != end; it++)
	{
		itoa(i,tempstr,10);
		tempint = (int) *it;
		itoa(tempint,tempstr1,10);
		fprintf(TheFile, "Wall %s: %s\n",tempstr, tempstr1);
		// Corners
		tempint = (int) (*it)->Corner1;
		itoa(tempint,tempstr,10);
		fprintf(TheFile, "Corner1: %s\t",tempstr);
		tempint = (int) (*it)->Corner2;
		itoa(tempint,tempstr,10);
		fprintf(TheFile, "Corner2: %s\t",tempstr);
		// Positions
		tempPoint = (*it)->GetPoint();
		tempdouble1 = tempPoint->x; tempdouble2 = tempPoint->y;
		gcvt(tempdouble1, 7, tempstr1);
		gcvt(tempdouble2, 7, tempstr2);
		fprintf(TheFile, "Position1: %s,%s\t", tempstr1, tempstr2);
		tempdouble1 = (*it)->GetDirection()->x + tempPoint->x; tempdouble2 = (*it)->GetDirection()->y + tempPoint->y;
		gcvt(tempdouble1, 7, tempstr1);
		gcvt(tempdouble2, 7, tempstr2);
		fprintf(TheFile, "Position2: %s,%s\n", tempstr1, tempstr2);
		fprintf(TheFile, "-------\n");
		i++;
	}

	itc = Corners.begin();
	endc = Corners.end();
	i = 0;
	for(; itc != endc; itc++)
	{
		itoa(i,tempstr,10);
		tempint = (int) *itc;
		itoa(tempint,tempstr1,10);
		fprintf(TheFile, "Corner %s: %s\n",tempstr, tempstr1);
		// Positions
		tempdouble1 = (*itc)->Position.x; tempdouble2 = (*itc)->Position.y;
		gcvt(tempdouble1, 7, tempstr1);
		gcvt(tempdouble2, 7, tempstr2);
		fprintf(TheFile, "Position: %s,%s\t", tempstr1, tempstr2);
		it = (*itc)->Walls.begin();
		end = (*itc)->Walls.end();
		j = 0;
		for(; it != end; it++)
		{
			itoa(j,tempstr,10);
			tempint = (int) *it;
			itoa(tempint,tempstr1,10);
			fprintf(TheFile, "Wall %s: %s\t",tempstr, tempstr1);
			j++;
		}
		fprintf(TheFile, "\n-------\n");
		i++;
	}

	fclose(TheFile);
}

// Building Implementation

void Building::GenerateDefault()
{
	
	Floor* TempFloor = new Floor("Floor1");
	TempFloor->floor = Ceilings.back();
	PlaneCeiling* TempCeiling = new PlaneCeiling(TempFloor->GetAltitude()+TempFloor->GetHeight());
	Ceilings.push_back(TempCeiling);
	TempFloor->ceiling = TempCeiling;
	Floors.push_front(TempFloor);
	SelectedFloor = TempFloor;
}

int Building::CheckFloorNameInvalidity(char name[])
{
	list<Floor*>::iterator start, end, it;
	start = Floors.begin();
	end = Floors.end();
	for(it = start; it != end; ++it) if(strcmp((*it)->Name, name) == 0) return 1;
	return 0;
}

void Building::GetFloorNames(char names[][16])
{
	list<Floor*>::iterator start, end, it;
	start = Floors.begin();
	end = Floors.end();
	int i = 0;
	for(it = start; it != end; ++it)
	{
		strcpy(names[i],(*it)->Name);
		i++;
	}
}

int Building::GetSelected(void)
{
	list<Floor*>::iterator start, end, it;
	start = Floors.begin();
	end = Floors.end();
	int i = 0, n = 0;
	for(it = start; it != end; ++it, ++i) if(SelectedFloor == (*it)) n = i;
	return n;
}

void Building::SetSelected(int no)
{
	list<Floor*>::iterator start, end, it;
	start = Floors.begin();
	end = Floors.end();
	int i = 0;
	for(it = start; it != end; ++it, ++i) if(i == no) SelectedFloor = *it;
}

int Building::AddFloor(char name[], double height, bool top)
{
	if(CheckFloorNameInvalidity(name)) return 0;
	double altitude;
	PlaneCeiling* TempCeiling;
	list<Floor*>::iterator it, MarkPos;
	if(top) 
	{
		MarkPos = Floors.end();
		altitude = (Floors.back())->GetAltitude() + (Floors.back())->GetHeight();
		TempCeiling = (Floors.back())->ceiling;
	}
	else
	{
		for(it = Floors.begin(); it != Floors.end(); ++it) if((*it) == SelectedFloor) MarkPos = it;
		altitude = (*MarkPos)->GetAltitude();
		TempCeiling = (*MarkPos)->ceiling;
	}
	Floor* TempFloor = new Floor(name, altitude, height);
	TempFloor->floor = TempCeiling;
	altitude+=height;
	TempCeiling = new PlaneCeiling(altitude);
	TempFloor->ceiling = TempCeiling;
	SelectedFloor = TempFloor;
	MarkPos = Floors.insert(MarkPos, TempFloor);
	for(it = ++MarkPos; it != Floors.end(); ++it)
	{
// Attention! floors and ceilings are not set properly in this case

		(*it)->SetAltitude(altitude);
		altitude+= (*it)->GetHeight();
	}
	return 1;
}

int Building::RemoveFloor(void)
{
	list<Floor*>::iterator it, MarkPos, MarkPos1;
	if(Floors.size() == 1) return 0;
	for(it = Floors.begin(); it != Floors.end(); it++) if((*it) == SelectedFloor) MarkPos = it;
	double altitude = (*MarkPos)->GetAltitude();
	PlaneCeiling* TempCeiling = (*MarkPos)->floor;
	Floor* NextSelected;
	MarkPos1 = MarkPos;
	for(it = ++MarkPos; it != Floors.end(); ++it)
	{
		(*it)->SetAltitude(altitude);
		(*it)->floor =  TempCeiling;
		altitude+= (*it)->GetHeight();
		(*it)->ceiling->Altitude = altitude;
	}
	if(MarkPos1 == Floors.begin()) NextSelected = (*++MarkPos1);
	else NextSelected = (*--MarkPos1);
	delete SelectedFloor->ceiling;
	Ceilings.remove(SelectedFloor->ceiling);
	delete SelectedFloor;
	Floors.remove(SelectedFloor);
	SelectedFloor = NextSelected;
	return 1;
}

int Building::SetFloorName(char name[])
{
	if(CheckFloorNameInvalidity(name)) return 0;
	strcpy(SelectedFloor->Name,name);
	return 1;
}

void Building::SetFloorHeight(double height)
{
	double altitude = SelectedFloor->GetAltitude();
	SelectedFloor->SetAltitude(height);
	altitude+= height;
	list<Floor*>::iterator it, MarkPos;
	for(it = Floors.begin(); it != Floors.end(); it++) if((*it) == SelectedFloor) MarkPos = it;
	for(it = ++MarkPos; it != Floors.end(); ++it)
	{
		(*it)->SetAltitude(altitude);
		altitude+= (*it)->GetHeight();
	}
}

void Building::AddWall(void)
{
	SelectedFloor->AddWall();
}

PlaneWall* Building::GetSelectedWallCopy(void)
{
	return SelectedFloor->GetSelectedWallCopy();
}

PlaneWallElement* Building::GetSelectedElementCopy(void)
{
	return SelectedFloor->GetSelectedElementCopy();
}

void Building::SetWall(Point2d point1, Point2d point2)
{
	SelectedFloor->SetWall(point1,point2);
}

void Building::RemoveWall(void)
{
	SelectedFloor->RemoveWall();
}

void Building::AddWindow(void)
{
	SelectedFloor->AddWindow();
}

void Building::SetWindow(Point2d point1, Point2d point2)
{
	SelectedFloor->SetWindow(point1, point2);
}

void Building::AddDoor(void)
{
	SelectedFloor->AddDoor();
}

void Building::SetDoor(Point2d point1, Point2d point2)
{
	SelectedFloor->SetDoor(point1, point2);
}

void Building::AddStud(void)
{
	SelectedFloor->AddStud();
}

void Building::SetStud(Point2d point1, Point2d point2)
{
	SelectedFloor->SetStud(point1, point2);
}

void Building::DetermineRooms(void)
{
	list<Floor*>::iterator start, end, it;
	start = Floors.begin();
	end = Floors.end();
//	SelectedFloor->Dump();
	for(it = start; it != end; ++it) (*it)->DetermineRooms();
	return;
}

void Building::DeterminePlanElements(void)
{
	list<Floor*>::iterator start, end, it;
	start = Floors.begin();
	end = Floors.end();
//	SelectedFloor->Dump();
	for(it = start; it != end; ++it) (*it)->DeterminePlanElements();
	return;
}

void Building::DeterminePlanConnections(void)
{
	list<Floor*>::iterator start, end, it;
	start = Floors.begin();
	end = Floors.end();
//	SelectedFloor->Dump();
	for(it = start; it != end; ++it) (*it)->DeterminePlanConnections();
	return;
}

void Building::GenerateImageTree(WLANNode* WN)
{
// Find the Floor that hosts the WN
	list<Floor*>::iterator endf, itf;
	itf = Floors.begin();
	endf = Floors.end();
	Floor* HostFloor;
	list<AP*>::iterator enda, ita;
	for(; itf != endf; itf++)
	{
		ita = (*itf)->APs.begin();
		enda = (*itf)->APs.end();
		for(; ita != enda; ita++)
			if(*ita == WN) HostFloor = *itf;
	}
	queue<Interaction*> InteractionList1, InteractionList2, ImageList1, ImageList2, *CurrentList, *NextList, *TempList;
	list<PlaneWall*>::iterator itw, endw, itwp;
	list<Room*>::iterator itr, endr;
	Interaction** TempInteractions;
	Interaction *TempInteraction, *SourceInteraction;
	Corner *Corner1, *Corner2;
	Point *SourcePoint, ImagePoint;
	Point *TestPoint;
	Vector2d V1, V2, V3, *V4;
	int i, InteractionCount, Order = 1, intcount = 0;
char ic[10];

	NextList = &InteractionList1;
	Room *TempRoom2, *TempRoom = WN->R;
	SourcePoint = new Point(WN->Position.x, WN->Position.y, HostFloor->GetAltitude() + WN->Offset);
	InteractionCount = TempRoom->Walls.size() + 2;
	TempInteractions = new Interaction*[InteractionCount+1];
	WN->Interactions = TempInteractions;
	TempRoom->Interactions[WN->WNNo].push_back(0);
	i = 0;
	itw = TempRoom->Walls.begin();
	endw = TempRoom->Walls.end();
	itwp = endw;
	itwp--;
	if((*itwp)->Corner1 == (*itw)->Corner1 || (*itwp)->Corner2 == (*itw)->Corner1) Corner1 = (*itw)->Corner1;
	else Corner1 = (*itw)->Corner2;
	for(; itw != endw; itw++)
	{
		Corner2 = (*itw)->OtherCorner(Corner1);
		V1 = Vector2d(Corner2->Position.x - Corner1->Position.x, Corner2->Position.y - Corner1->Position.y);
		V2 = Vector2d(SourcePoint->x - Corner1->Position.x, SourcePoint->y - Corner1->Position.y);
// Test Interaction Potential
		if(V1*V2 > 0)
		{
			ImagePoint = (*itw)->GetImage(SourcePoint);
			TempInteraction = new Interaction(Order, ImagePoint, *itw, TempRoom, SourcePoint, 0);
			NextList->push(TempInteraction);
			TempInteractions[i] = TempInteraction;
			i++;
			intcount++;
		}
		Corner1 = Corner2;
	}
	ImagePoint = HostFloor->ceiling->GetImage(SourcePoint);
	TempInteraction = new Interaction(Order, ImagePoint, (PlaneWall*) HostFloor->ceiling, TempRoom, SourcePoint, 0);
	NextList->push(TempInteraction);
	TempInteractions[i] = TempInteraction;
	i++;
	intcount++;
	ImagePoint = HostFloor->floor->GetImage(SourcePoint);
	TempInteraction = new Interaction(Order, ImagePoint, (PlaneWall*) HostFloor->floor, TempRoom, SourcePoint, 0);
	NextList->push(TempInteraction);
	TempInteractions[i] = TempInteraction;
	i++;
	TempInteractions[i] = 0;
	intcount++;

	CurrentList = &InteractionList1;
	NextList = &InteractionList2;
	do
	{
		while(!CurrentList->empty() && Order < 4)
		{
			SourceInteraction = CurrentList->front();
// Interacted with the Source Room
			SourcePoint = &SourceInteraction->ImagePoint;
			TempRoom = SourceInteraction->SourceRoom;
			if(SourceInteraction->Wall == (PlaneWall*) HostFloor->ceiling || SourceInteraction->Wall == (PlaneWall*) HostFloor->floor)
			{
				TempRoom2 = 0;
				InteractionCount = TempRoom->Walls.size() + 1;
			}
			else
			{
				TempRoom2 = SourceInteraction->Wall->OtherRoom(SourceInteraction->SourceRoom);
				InteractionCount = TempRoom->Walls.size() + TempRoom2->Walls.size() + 2;
			}
			TempInteractions = new Interaction*[InteractionCount+1];
			SourceInteraction->Interactions = TempInteractions;
			i = 0;
			itw = TempRoom->Walls.begin();
			endw = TempRoom->Walls.end();
			itwp = endw;
			itwp--;
			if((*itwp)->Corner1 == (*itw)->Corner1 || (*itwp)->Corner2 == (*itw)->Corner1) Corner1 = (*itw)->Corner1;
			else Corner1 = (*itw)->Corner2;
			for(; itw != endw; itw++)
			{
				Corner2 = (*itw)->OtherCorner(Corner1);
				V1 = Vector2d(Corner2->Position.x - Corner1->Position.x, Corner2->Position.y - Corner1->Position.y);
				V2 = Vector2d(SourcePoint->x - Corner1->Position.x, SourcePoint->y - Corner1->Position.y);
// Test Reflecting Potential
				if(V1*V2 > 0 && SourceInteraction->Wall != *itw)
				{
					ImagePoint = (*itw)->GetImage(SourcePoint);
					TempInteraction = new Interaction(Order, ImagePoint, *itw, TempRoom, SourcePoint, SourceInteraction);
					NextList->push(TempInteraction);
					TempInteractions[i] = TempInteraction;
					i++;
					intcount++;
				}
				Corner1 = Corner2;
			}			
			if(SourcePoint->z < HostFloor->ceiling->Altitude && SourceInteraction->Wall != (PlaneWall*) HostFloor->ceiling)
			{
				ImagePoint = HostFloor->ceiling->GetImage(SourcePoint);
				TempInteraction = new Interaction(Order, ImagePoint, (PlaneWall*) HostFloor->ceiling, TempRoom, SourcePoint, SourceInteraction);
				NextList->push(TempInteraction);
				TempInteractions[i] = TempInteraction;
				i++;
				intcount++;
			}
			
			if(SourcePoint->z > HostFloor->floor->Altitude && SourceInteraction->Wall != (PlaneWall*) HostFloor->floor)
			{
				ImagePoint = HostFloor->floor->GetImage(SourcePoint);
				TempInteraction = new Interaction(Order, ImagePoint, (PlaneWall*) HostFloor->floor, TempRoom, SourcePoint, SourceInteraction);
				NextList->push(TempInteraction);
				TempInteractions[i] = TempInteraction;
				i++;
				intcount++;
			}

// Interacted with the Neighbouring Room
			if(TempRoom2 != 0)
			{
				V4 = SourceInteraction->Wall->GetDirection();
				TestPoint = SourceInteraction->Wall->GetPoint();
				SourcePoint = SourceInteraction->SourcePoint;
				TempRoom2->Interactions[WN->WNNo].push_back(SourceInteraction);
				itw = TempRoom2->Walls.begin();
				endw = TempRoom2->Walls.end();
				itwp = endw;
				itwp--;
				if((*itwp)->Corner1 == (*itw)->Corner1 || (*itwp)->Corner2 == (*itw)->Corner1) Corner1 = (*itw)->Corner1;
				else Corner1 = (*itw)->Corner2;
				for(; itw != endw; itw++)
				{
					Corner2 = (*itw)->OtherCorner(Corner1);
					V1 = Vector2d(Corner2->Position.x - Corner1->Position.x, Corner2->Position.y - Corner1->Position.y);
					V2 = Vector2d(TestPoint->x+V4->x/2 - Corner1->Position.x, TestPoint->y+V4->y/2 - Corner1->Position.y);
					V3 = Vector2d(SourcePoint->x - Corner1->Position.x, SourcePoint->y - Corner1->Position.y);
					if(V1*V2 > 0  && V1*V3 > 0 && SourceInteraction->Wall != *itw)
					{
						ImagePoint = (*itw)->GetImage(SourcePoint);
						TempInteraction = new Interaction(Order, ImagePoint, *itw, TempRoom2, SourcePoint, SourceInteraction);
						NextList->push(TempInteraction);
						TempInteractions[i] = TempInteraction;
						i++;
						intcount++;
					}
					Corner1 = Corner2;
				}			
				if(SourcePoint->z < HostFloor->ceiling->Altitude && SourceInteraction->Wall != (PlaneWall*) HostFloor->ceiling && TempRoom2 != HostFloor->Outdoor)
				{
					ImagePoint = HostFloor->ceiling->GetImage(SourcePoint);
					TempInteraction = new Interaction(Order, ImagePoint, (PlaneWall*) HostFloor->ceiling, TempRoom2, SourcePoint, SourceInteraction);
					NextList->push(TempInteraction);
					TempInteractions[i] = TempInteraction;
					i++;
					intcount++;
				}
				
				if(SourcePoint->z > HostFloor->floor->Altitude && SourceInteraction->Wall != (PlaneWall*) HostFloor->floor && TempRoom2 != HostFloor->Outdoor)
				{
					ImagePoint = HostFloor->floor->GetImage(SourcePoint);
					TempInteraction = new Interaction(Order, ImagePoint, (PlaneWall*) HostFloor->floor, TempRoom2, SourcePoint, SourceInteraction);
					NextList->push(TempInteraction);
					TempInteractions[i] = TempInteraction;
					i++;
					intcount++;
				}
	
			}
			TempInteractions[i] = 0;

			CurrentList->pop();
		};
		Order++;
		TempList = CurrentList;
		CurrentList = NextList;
		NextList = TempList;
	}
	while(!CurrentList->empty());
itoa(intcount,ic,10);
AfxMessageBox(ic);
}

double Building::TraverseImageTree(WLANNode* WN, Point* P)
{
	Room *TempRoom, *TempRoom2;
	Point2d point = Point2d(P->x, P->y);
	TempRoom = SelectedFloor->GetRoom(point);
	if(TempRoom == SelectedFloor->Outdoor) return 130;
	double z, zi, zq, phase, f, dx, dy ,dz, d, d2, lambda, c, pi, interact; 
	pi = 3.1415926535;
	f = 2400000000;
	c = 300000000;
	lambda = 0.125;
	zi = 0;
	zq = 0;
	int i,k=0;
	bool LoS;
	Point P4, P3, P2, P1 = Point(WN->Position.x, WN->Position.y, SelectedFloor->GetAltitude() + WN->Offset);
	PlaneWall *TempWall;
	LineSegment L1, L2;
	queue<Interaction*> InteractionList1, InteractionList2, ImageList1, ImageList2, *CurrentList, *NextList, *TempList;
	Interaction *TempInteraction, *TempInteraction2, *UpperInteraction;
	Interaction** Interactions;
	list<Interaction*>::iterator it, end;
	list<PlaneWall*>::iterator	itw, endw;
	NextList = &InteractionList1;
	CurrentList = &InteractionList2;
	it = TempRoom->Interactions[WN->WNNo].begin();
	end = TempRoom->Interactions[WN->WNNo].end();
	while(it != end)
	{
		
		TempInteraction = *it;

		NextList->push(TempInteraction);
		TempInteraction2 = TempInteraction;
		TempRoom2 = TempRoom;
		LoS = true;
		P2 = *P;
		interact = 1;
		while(TempInteraction2 != 0 && LoS)
		{
			TempWall = TempInteraction2->Wall;
			if(TempInteraction2->SourceRoom != TempRoom2)
			{
				L2 = LineSegment(P2, TempInteraction2->SourcePoint);
				if(TempWall->Intersect(&L2, &P3) != 0)
				{
// Transmission Coefficient at P3
					interact*= TempWall->TransmitAt(&L2, &P3);
					if(!TempRoom2->Convex)
					{
					}
				}
				else LoS = false;
				TempRoom2 = TempInteraction2->SourceRoom;
			}
			else
			{
				L2 = LineSegment(P2, &TempInteraction2->ImagePoint);
				if(TempWall != (PlaneWall*) SelectedFloor->ceiling && TempWall != (PlaneWall*) SelectedFloor->floor)
				{
					if(TempWall->Intersect(&L2, &P3) != 0)
					{
// Reflection Coefficient at P3
						interact*= TempWall->ReflectAt(&L2, &P3);
						if(!TempRoom2->Convex)
						{
						}
					}
					else LoS = false;
					P2 = TempWall->GetImage(&P2);
				}
				else
				{
					interact*= ((PlaneCeiling*) TempWall)->ReflectAt(&L2, &P3);
					P2 = ((PlaneCeiling*) TempWall)->GetImage(&P2);
				}
			}
			TempInteraction2 = TempInteraction2->Parent;
		}
		if(!TempRoom2->Convex)
		{
			L2 = LineSegment(P2, &P1);

		}
		if(LoS)
		{
			dx = P2.x - P1.x;
			dy = P2.y - P1.y;
			dz = P2.z - P1.z;
			d2 = dx*dx + dy*dy + dz*dz;
			d = sqrt(d2);
			if(d<1) d = 1;
			phase = 2*pi*d/lambda;
			zi+= interact*cos(phase)/d;
			zq+= interact*sin(phase)/d;
		}
		it++;
	}

	while(!NextList->empty())
	{
		TempList = CurrentList;
		CurrentList = NextList;
		NextList = TempList;
		while(!CurrentList->empty())
		{
			UpperInteraction = CurrentList->front();
			if(UpperInteraction == 0)
				Interactions = WN->Interactions;
			else
				Interactions = UpperInteraction->Interactions;
			i = 0;
			if(Interactions == 0) TempInteraction = 0;
			else TempInteraction = Interactions[i];
			while(TempInteraction != 0)
			{
				if(TempInteraction->SourceRoom == TempRoom)
				{
					if(TempInteraction->Interactions != 0)
							NextList->push(TempInteraction);
					TempInteraction2 = TempInteraction;
					TempRoom2 = TempRoom;
					LoS = true;
					P2 = *P;
					interact = 1;
					while(TempInteraction2 != 0 && LoS)
					{
						TempWall = TempInteraction2->Wall;
						if(TempInteraction2->SourceRoom != TempRoom2)
						{
							L2 = LineSegment(P2, TempInteraction2->SourcePoint);
							if(TempWall->Intersect(&L2, &P3) != 0)
							{
	// Transmission Coefficient at P3
								interact*= TempWall->TransmitAt(&L2, &P3);
								if(!TempRoom2->Convex)
								{
								}
							}
							else LoS = false;
							TempRoom2 = TempInteraction2->SourceRoom;
						}
						else
						{
							L2 = LineSegment(P2, &TempInteraction2->ImagePoint);
							if(TempWall != (PlaneWall*) SelectedFloor->ceiling && TempWall != (PlaneWall*) SelectedFloor->floor)
							{
								if(TempWall->Intersect(&L2, &P3) != 0)
								{
// Reflection Coefficient at P3
									interact*= TempWall->ReflectAt(&L2, &P3);
									if(!TempRoom2->Convex)
									{
									}
								}
								else LoS = false;
								P2 = TempWall->GetImage(&P2);
							}
							else
							{
								interact*= ((PlaneCeiling*) TempWall)->ReflectAt(&L2, &P3);
								P2 = ((PlaneCeiling*) TempWall)->GetImage(&P2);
							}
						}
						TempInteraction2 = TempInteraction2->Parent;
					}
					if(!TempRoom2->Convex)
					{
						L2 = LineSegment(P2, &P1);

					}
					if(LoS)
					{
						dx = P2.x - P1.x;
						dy = P2.y - P1.y;
						dz = P2.z - P1.z;
						d2 = dx*dx + dy*dy + dz*dz;
						d = sqrt(d2);
						if(d<1) d = 1;
						phase = 2*pi*d/lambda;
						zi+= interact*cos(phase)/d;
						zq+= interact*sin(phase)/d;
					}
				}
				i++;
				TempInteraction = Interactions[i];
			}
			CurrentList->pop();
		}
	}
	z = zi*zi + zq*zq;
	return -10*log(z);
}

int Building::GetAPCount(void)
{
	list<Floor*>::iterator start, end, it;
	start = Floors.begin();
	end = Floors.end();
	int count = 0;
	for(it = start; it != end; ++it) count+= (*it)->APs.size();
	return count;
}

int Building::AddAccessPoint()
{
	char name[] = "AP", no[4];
	int count = GetAPCount();
	itoa(++count,no,10);
	strcat(name,no);
	if(CheckAPNameInvalidity(name)) return 0;
	AP* TempAP = new AP();
	TempAP->WNNo = count - 1;
	strcpy(TempAP->Name, name);
	SelectedFloor->APs.push_back(TempAP);
	SelectedAP = TempAP;	
	return 1;
}

int Building::CheckAPNameInvalidity(char name[])
{
	list<Floor*>::iterator end, it;
	end = Floors.end();
	for(it = Floors.begin(); it != end; it++)
		if((*it)->CheckAPNameInvalidity(name)) return 1;
	return 0;
}

int Building::SetAPName(char name[])
{
	if(CheckFloorNameInvalidity(name)) return 0;
	strcpy(SelectedAP->Name, name);
	return 1;
}

void Building::GetAPNames(char names[][16])
{
	int i = 0;
	list<Floor*>::iterator end1, it1;
	end1 = Floors.end();
	list<AP*>::iterator end2, it2;
	for(it1 = Floors.begin(); it1 != end1; it1++)
	{
		end2 = (*it1)->APs.end();
		for(it2 = (*it1)->APs.begin(); it2 != end2; it2++)
		{
			strcpy(names[i],(*it2)->Name);
			i++;
		}
	}
}

char* Building::GetSelectedAPName(void)
{
	return SelectedAP->Name;
}

void Building::SetSelectedAP(char name[])
{
	list<Floor*>::iterator end1, it1;
	end1 = Floors.end();
	list<AP*>::iterator end2, it2;
	for(it1 = Floors.begin(); it1 != end1; it1++)
	{
		end2 = (*it1)->APs.end();
		for(it2 = (*it1)->APs.begin(); it2 != end2; it2++)
			if(strcmp(name,(*it2)->Name) == 0) SelectedAP = *it2;
	}
}

void Building::RemoveAP(void)
{
	if(SelectedAP != 0) 
	SelectedFloor->APs.remove(SelectedAP);
}

void Building::SetSelectedAP(Point2d point, int Scale)
{
	AP* TempAP;
	list<AP*>::iterator end2, it2;
	end2 = SelectedFloor->APs.end();
	if(SelectedAP) SelectedAP->Selected = false;
	SelectedAP = 0;
	for(it2 = SelectedFloor->APs.begin(); it2 != end2; it2++)
	{
		TempAP = (AP*) (*it2)->Select(point, Scale);
		if(TempAP) SelectedAP = TempAP;
	}
}

void Building::SetAPPosition(Point2d point)
{
	SelectedAP->Position = point;
	SelectedAP->R = SelectedFloor->GetRoom(SelectedAP->Position);
//	SelectedAP->DeleteImageTree();
//	GenerateImageTree(SelectedAP);
}

void Building::SetAPPosition(Point2d point, double altitude)
{
	SelectedAP->Position = point;
	SelectedAP->Offset = altitude;
	SelectedAP->R = SelectedFloor->GetRoom(SelectedAP->Position);
//	SelectedAP->DeleteImageTree();
//	GenerateImageTree(SelectedAP);
}

void Building::TestDown(Point2d point, CDC* pDC, int Scale, CPen* WallPen, CPen* ElementPen, CPen* StudPen)
{
	list<PlaneWall*>::iterator end, it;
//	list<Room*>::iterator itr, endr;
	Room* TestRoom = SelectedFloor->GetRoom(point);
//	itr = SelectedFloor->Rooms.begin();
//	for(int i=0; i<n && i<SelectedFloor->Rooms.size(); i++) itr++;
//	Room* TestRoom = *itr;
	
	it = TestRoom->Walls.begin();
	end = TestRoom->Walls.end();
	for(; it != end; it++)
	{
		(*it)->Draw(pDC, Scale, WallPen, ElementPen, StudPen);
	}
}

Point2d Building::Snap(Point2d P, bool ToSelected, bool Select, bool ExcludeCurrent, bool ToSelectedFloor)
{
	list<Floor*>::iterator end, it;
	it = Floors.begin();
	end = Floors.end();
	if(Floors.size() == 0) return P;
	if(ToSelected || Select) return SelectedFloor->Snap(P, ToSelected, Select);
	if(ToSelectedFloor) return SelectedFloor->Snap(P);
	Vector2d TempVector1, TempVector2;
	Point2d TempPoint;
	Point2d ClosestPoint;
	bool found = false;
	while(it != end && !found)
	{
		if(!((*it)->GetWallCount() == 0 || (*it)->GetWallCount() == 1 && ExcludeCurrent && SelectedFloor == *it))
		{
			ClosestPoint = (*it)->Snap(P, ToSelected, Select, ExcludeCurrent && *it == SelectedFloor);
			TempVector1 = Vector2d(&P, &ClosestPoint);
			found = true;
		}
		it++;
	}
	if(it == end && !found) return P;
	for(; it != end; ++it)
	{
		if(!((*it)->GetWallCount() == 0 || (*it)->GetWallCount() == 1 && ExcludeCurrent && SelectedFloor == *it))
		{
			TempPoint = (*it)->Snap(P, ToSelected, Select, ExcludeCurrent && *it == SelectedFloor);
			TempVector2 = Vector2d(&P,&TempPoint);
			if(TempVector1.x * TempVector1.x + TempVector1.y * TempVector1.y > TempVector2.x * TempVector2.x + TempVector2.y * TempVector2.y)
			{
				ClosestPoint = TempPoint;
				TempVector1 = Vector2d(&P, &ClosestPoint);
			}
		}
	}
	return ClosestPoint;
}

void Building::DrawWall(CDC* pDC, int Scale, BOOL Inverse)
{
	CPen *WallPen, *ElementPen, *StudPen;
	int DrawMode;
	if(Inverse) DrawMode = pDC->SetROP2(R2_NOTXORPEN);
	else DrawMode = pDC->SetROP2(R2_COPYPEN);
	WallPen = new CPen(PS_SOLID, 10, RGB(128,128,128));
	ElementPen = new CPen(PS_SOLID, 1, RGB(64,64,64));
	StudPen = new CPen(PS_SOLID, 14, RGB(64,64,64));
	SelectedFloor->DrawWall(pDC, Scale, WallPen, ElementPen, StudPen);
	pDC->SetROP2(DrawMode);
	delete WallPen;
	delete ElementPen;
	delete StudPen;
}

void Building::Draw(CDC* pDC, int Scale)
{
	CPen *WallPen, *ElementPen, *StudPen;
	list<Floor*>::iterator end, it;
	end = Floors.end();
	WallPen = new CPen(PS_SOLID, 10, RGB(224,224,224));
	ElementPen = new CPen(PS_SOLID, 1, RGB(224,224,224));
	StudPen = new CPen(PS_SOLID, 14, RGB(224,224,224));
	int DrawMode = pDC->SetROP2(R2_COPYPEN);
	for(it = Floors.begin(); it != end; ++it) if(!(*it)->Hidden && *it != SelectedFloor) (*it)->Draw(pDC, Scale, WallPen, ElementPen, StudPen);
	delete WallPen;
	delete ElementPen;
	delete StudPen;
	WallPen = new CPen(PS_SOLID, 10, RGB(128,128,128));
	ElementPen = new CPen(PS_SOLID, 1, RGB(64,64,64));
	StudPen = new CPen(PS_SOLID, 14, RGB(64,64,64));
	SelectedFloor->Draw(pDC, Scale, WallPen, ElementPen, StudPen);
	pDC->SetROP2(DrawMode);
	delete WallPen;
	delete ElementPen;
	delete StudPen;
}

void Building::DrawLAN(CDC* pDC, int Scale)
{
	SelectedFloor->DrawLAN(pDC, Scale);
}

void Building::DrawPlan(CDC* pDC, int Scale)
{
	SelectedFloor->DrawPlan(pDC, Scale);
}

CArchive& operator<< (CArchive& ar, Building& B)
{
	int i, n, s;
	list<Floor*>::iterator itf, endf;
	n = B.Floors.size();
	ar << n;

	itf = B.Floors.begin();
	endf = B.Floors.end();
	for(i=0; itf != endf; itf++)
	{
		ar << *(*itf);
		if(B.SelectedFloor == *itf) s = i;
	}

	ar << s;

	return ar;
}

CArchive& operator>> (CArchive& ar, Building& B)
{
	int i, n, s;
	list<Floor*>::iterator itf, endf;
	Floor* NewFloor;
	ar >> n;

	for(i=0; i<n; i++)
	{
		NewFloor = new Floor("Floor1");
		B.Floors.push_back(NewFloor);
		ar >> *NewFloor;
		NewFloor->floor = B.Ceilings.back();
		B.Ceilings.push_back(NewFloor->ceiling);
	}

	ar >> s;
	itf = B.Floors.begin();
	endf = B.Floors.end();
	for(i=0; itf != endf; itf++)
	{
		if(i==s) B.SelectedFloor = *itf;
	}

	B.SelectedAP = 0;

	return ar;
}

HMETAFILE Building::GenerateCoverageMap(CMetaFileDC* MetaFile, int Scale, Vector2d CampSize)
{
	double h2;
	double PLd0 = 20;
	double d0 = 1;
//	double n = 2.5;
//	double ConstFAF = 0;
	double Attenuation, Att;
//	int fc;
	int i, j, r, g, b;
	int x = CampSize.x*Scale;
	int y = CampSize.y*Scale;
	int ix = 30;
	int iy = 30;
	h2 = SelectedFloor->GetAltitude() + 0.9;
	if(GetAPCount() == 0) return MetaFile->Close();
	Point P1, P2;
//	LineSegment L;
//	list<PlaneWall*>::iterator start, end, it;
//	start = SelectedFloor->Walls.begin();
//	end = SelectedFloor->Walls.end();
	list<Floor*>::iterator itf, endf;
	for(i=14; i<x; i+=ix)
		for(j=14;j<y;j+=iy)
		{
			P2 = Point((double) i/Scale,(double) -j/Scale,h2);
			itf = Floors.begin();
			endf = Floors.end();
			for(; itf != endf; itf++)
			{
				list<AP*>::iterator ita, enda;
				ita = (*itf)->APs.begin();
				enda = (*itf)->APs.end();
				Att = 0;
				Attenuation = TraverseImageTree(*ita, &P2);
				ita++;
				for(; ita != enda; ita++)
				{
					Att = TraverseImageTree(*ita, &P2);
				if(Att < Attenuation && Att != 0) Attenuation = Att;
				}
			}
			if(Attenuation < 25.6)
			{
				if(Attenuation<0) Attenuation = 0;
				r = 255;
				g = Attenuation*10;
				b = 0;
			}
			else if(Attenuation < 51.2)
			{
				r = 512 - Attenuation*10;
				g = 255;
				b = 0;
			}
			else if(Attenuation < 76.8)
			{
				r = 0;
				g = 255;
				b = Attenuation*10 - 512;
			}
			else if(Attenuation < 102.4)
			{
				r = 0;
				g = 1024 - Attenuation*10;
				b = 255;
			}
			else if(Attenuation < 121.6)
			{
				r = Attenuation*10 - 1024;
				g = 0;
				b = 255;
			}
			else
			{
				r = 255;
				g = 255;
				b = 255;
			}
			MetaFile->FillSolidRect(i-14, -j-14, 30, 30, RGB(r,g,b));

		}
	Draw(MetaFile, Scale);

	return MetaFile->Close();
}
