#if !defined(_3DSPACE_H)
#define _3DSPACE_H

#include <math.h>
#include <list>

#include "_2dSpace.h"

using namespace std;


class Point {

public:
	double x, y, z;
	Point() {}
	Point(double X, double Y, double Z): x(X), y(Y), z(Z) {}
	friend Point operator *(Point P, double k) {return Point(k*P.x, k*P.y, k*P.z);}
	friend Point operator *(double k, Point P) {return Point(k*P.x, k*P.y, k*P.z);}
	friend Point operator /(Point P, double k) {return Point(P.x/k, P.y/k, P.z/k);}
	int operator ==(const Point& P){return ((fabs(x - P.x) < 0.000001 && fabs(y - P.y) < 0.000001 && fabs(z - P.z) < 0.000001));}
	int operator !=(const Point& P){return !((fabs(x - P.x) < 0.000001 && fabs(y - P.y) < 0.000001 && fabs(z - P.z) < 0.000001));}
};


class Vector {

public:
	double x, y, z;
	Vector() {}
	Vector(double X, double Y, double Z): x(X), y(Y), z(Z) {}
	Vector(Point* P) {x= P->x; y = P->y; z = P->z;}
	Vector(Point* P1, Point* P2) {x = P2->x - P1->x; y = P2->y - P1->y; z = P2->z - P1->z;}
	double Abs(void) {return sqrt(x*x + y*y + z*z);}
	double Product(Vector V) {return x*V.x + y*V.y + z*V.z;}
	Vector operator +(Vector V) {return Vector(x + V.x, y + V.y, z + V.z);}
	Vector operator -(Vector V) {return Vector(x - V.x, y - V.y, z - V.z);}
	Vector operator *(Vector V) {return Vector(y*V.z - V.y*z, z*V.x - x*V.z, x*V.y - y*V.x);}
	Point operator +(Point P) {return Point(P.x + x, P.y + y, P.z + z);}
	friend Vector operator /(Vector V, double k) {return Vector(V.x/k, V.y/k, V.z/k);}
	friend Vector operator *(Vector V, double k) {return Vector(k*V.x, k*V.y, k*V.z);}
	friend Vector operator *(double k, Vector V) {return Vector(k*V.x, k*V.y, k*V.z);}
	int operator ==(const Vector& V){return ((fabs(x - V.x) < 0.000001) && (fabs(y - V.y) < 0.000001) && (fabs(z - V.z) < 0.000001));}
	int operator !=(const Vector& V){return !(fabs(x - V.x) < 0.000001 && fabs(y - V.y) < 0.000001 && fabs(z - V.z) < 0.000001);}
};


class Line {
friend class Plane;
protected:
	Point p;
	Vector v;

public:
	Line() {}
	Line(Point P1, Point *P2) {p = P1; v = Vector(&p,P2);}
	Line(Point P, Vector V): p(P), v(V) {}
	Point* GetPoint(void) {return &p;}
	Vector* GetDirection(void) {return &v;}
	void SetPoint(Point P) {p = P;}
	void SetDirection(Vector V) {v = V;}
	void MoveBy(Vector V) {p = V + p;}
	virtual int PassThrough(Point* P);
	virtual Point ClosestPointTo(Point* P);
	int Intersect(Line* L, Point* P);
};


class Ray: public Line {
	
private:

public:
	Ray() {}
	Ray(Point P, Vector V): Line(P,V) {}
	Ray(Point P1, Point* P2): Line(P1,P2) {}
	Point ClosestPointTo(Point* P);
	int PassThrough(Point* P);
};


class Edge {
friend class EdgedPlane;
protected:
	Point p1;
	Point p2;
public:
	Edge() {}
	Edge(Point P1, Point P2): p1(P1), p2(P2) {}
	virtual Point* GetEndPoint1(void) {return &p1;}
	virtual Point* GetEndPoint2(void) {return &p2;}
	virtual void SetEndPoint1(Point P) {p1 = P;}
	virtual void SetEndPoint2(Point P) {p2 = P;}
	virtual void MoveBy(Vector V) = 0;
	virtual int PassThrough(Point* P) = 0;
	virtual Point ClosestPointTo(Point* P) = 0;
	virtual int Intersect(Line* L, Point* P) = 0;
};


class LineSegment: public Edge, public Line {

public:
	LineSegment() {}
	LineSegment(Point P1, Point* P2): Edge(P1,*P2), Line(P1,P2) {}
	void SetPoint(Point P) {p = P; p1 = P;}
	void SetEndPoint1(Point P) {p = P; p1 = P;}
	void MoveBy(Vector V) {p = V + p; p1 = V + p1; p2 = V + p2;}
	int PassThrough(Point* P);
	Point ClosestPointTo(Point* P);
	int Intersect(Line* L, Point* P) {return Line::Intersect(L, P);}
};


class Surface {

public:
	Surface() {}
	virtual void MoveBy(Vector V) = 0;
	virtual int PassThrough(Point* P) = 0;
	virtual int Intersect(Line* L, Point* P) = 0;
};


class Plane: public Surface {

protected:
	Point p;
	Vector n;

public:
	Plane() {}
	Plane(Point P, Vector N): Surface(), p(P), n(N) {}
	Plane(Point P1, Point* P2, Point* P3) {p = P1; n = Vector(&P1,P2) * Vector(&P1,P3); }
	Plane(double X, double Y, double Z) {Point P1, P2; p = Point(X,0,0); P1 = Point(0,Y,0); P2 = Point(0,0,Z); n = Vector(&p,&P1) * Vector(&p,&P2);}
	void SetPlane(Point P, Vector N) {p = P; n = N;}
	Point* GetPoint(void) {return &p;}
	Vector* GetNormal(void) {return &n;}
	void MoveBy(Vector V) {p = V + p;}
	virtual int PassThrough(Point* P);
	int Intersect(Line* L, Point* P);
	int Intersect(Plane* P, Line* L);
};


class VerticalRect: public Plane {

protected:
	double h;
	Vector2d d;

public:
	VerticalRect(): Plane() {}
	VerticalRect(Point P, Vector2d D, double Height) {p = P; d = D; n = Vector(D.x,D.y,0) * Vector(0,0,Height); h = Height;}
	void SetRectangle(Point P, Vector2d D, double Height) {p = P; d = D; n = Vector(D.x,D.y,0) * Vector(0,0,Height); h = Height;}
	void SetPosition(Point2d point1, Point2d point2);
	Vector2d* GetDirection(void) {return &d;}
	int PassThrough(Point* P);
	Point2d ClosestPoint2dTo(Point2d* P);
	int Intersect2d(Line2d* L, Point2d* );
};


class Parallelogram: public Plane {
	Vector v1, v2;

public:
	Parallelogram(): Plane() {}
	Parallelogram(Point RefPoint, Vector V1, Vector V2): Plane(RefPoint, V1*V2), v1(V1), v2(V2) {}
	int PassThrough(Point* P);
};


template <class T>
class PatchedSurface: public T {

protected:
	list <Surface*> Patches;

public:
	PatchedSurface(): T() {}
	void AddPatch(Surface* P) {Patches.push_back(P);}
	void RemovePatch(Surface *P) {Patches.remove(P);}
	void MoveBy(Vector V);
//	int PassThrough(Point* P);
//	Point* Intersect(Line* L);
	Surface* PassThroughWhich(Point* P);
};


template <class T>
void PatchedSurface<T>::MoveBy(Vector V)
{
	T::MoveBy(V);
	list<Surface*>::iterator start, end, it;
	start = Patches.begin();
	end = Patches.end();
	for(it = start; it != end; it++) (*it)->MoveBy(V);
}

template <class T>
Surface* PatchedSurface<T>::PassThroughWhich(Point* P)
{
	list<Surface*>::iterator start, end, it;
	start = Patches.begin();
	end = Patches.end();
	for(it = start; it != end; it++) if((*it)->PassThrough(P)) return *it;
	return 0;
}


/*
template <class T>
int PatchedSurface<T>::PassThrough(Point* P)
{
	if(T::PassThrough(P) == 0) return 0;
	list<Surface*>::iterator start, end, it;
	start = Patches.begin();
	end = Patches.end();
	for(it = start; it != end; it++) if((*it)->PassThrough(P)) return 0;
	return 1;
}

template <class T>
Point* PatchedSurface<T>::Intersect(Line* L)
{
	Point* P;
	P = T::Intersect(L);
	if(P == 0) return 0;
	list<Surface*>::iterator start, end, it;
	start = Patches.begin();
	end = Patches.end();
	for(it = start; it != end; it++)
		if((*it)->PassThrough(P))
		{
			delete P;
			return 0;
		}
	return P;
}
*/

#endif
