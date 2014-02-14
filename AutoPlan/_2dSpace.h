#if !defined(_2DSPACE_H)
#define _2DSPACE_H

#include <math.h>
#include <list>

#define tollerance 0.000001

using namespace std;


class Point2d {

public:
	double x, y;
	Point2d() {}
	Point2d(double X, double Y): x(X), y(Y) {}
	friend Point2d operator *(Point2d P, double k) {return Point2d(k*P.x, k*P.y);}
	friend Point2d operator *(double k, Point2d P) {return Point2d(k*P.x, k*P.y);}
	friend Point2d operator /(Point2d P, double k) {return Point2d(P.x/k, P.y/k);}
	int operator ==(const Point2d& P){return ((fabs(x - P.x) < 0.000001 && fabs(y - P.y) < 0.000001));}
	int operator !=(const Point2d& P){return !((fabs(x - P.x) < 0.000001 && fabs(y - P.y) < 0.000001));}
};


class Vector2d {

public:
	double x, y;
	Vector2d() {}
	Vector2d(double X, double Y): x(X), y(Y) {}
	Vector2d(Point2d* P) {x= P->x; y = P->y;}
	Vector2d(Point2d* P1, Point2d* P2) {x = P2->x - P1->x; y = P2->y - P1->y;}
	double Abs(void) {return sqrt(x*x + y*y);}
	double Product(Vector2d V) {return x*V.x + y*V.y;}
	Vector2d operator +(Vector2d V) {return Vector2d(x + V.x, y + V.y);}
	Vector2d operator -(Vector2d V) {return Vector2d(x - V.x, y - V.y);}
	double operator *(Vector2d V) {return x*V.y - y*V.x;}
	Point2d operator +(Point2d P) {return Point2d(P.x + x, P.y + y);}
	friend Vector2d operator /(Vector2d V, double k) {return Vector2d(V.x/k, V.y/k);}
	friend Vector2d operator *(Vector2d V, double k) {return Vector2d(k*V.x, k*V.y);}
	friend Vector2d operator *(double k, Vector2d V) {return Vector2d(k*V.x, k*V.y);}
	int operator ==(const Vector2d& V){return (fabs(x - V.x) < 0.000001 && fabs(y - V.y) < 0.000001);}
	int operator !=(const Vector2d& V){return !(fabs(x - V.x) < 0.000001 && fabs(y - V.y) < 0.000001);}
};


class Line2d {
friend class Plane;
protected:
	Point2d p;
	Vector2d v;

public:
	Line2d() {}
	Line2d(Point2d P1, Point2d *P2): p(P1), v(Vector2d(&P1,P2)) {}
	Line2d(Point2d P, Vector2d V): p(P), v(V) {}
	void MoveBy(Vector2d V) {p = V + p;}
	virtual int PassThrough(Point2d* P);
	virtual Point2d ClosestPointTo(Point2d* P);
	int Intersect(Line2d* L, Point2d* P);
};


class Ray2d: public Line2d {
	
private:

public:
	Ray2d() {}
	Ray2d(Point2d P, Vector2d V): Line2d(P,V) {}
	Ray2d(Point2d P1, Point2d* P2): Line2d(P1,P2) {}
	Point2d ClosestPointTo(Point2d* P);
	int PassThrough(Point2d* P);
};


class Edge2d {
friend class EdgedPlane;
protected:
	Point2d p1;
	Point2d p2;
public:
	Edge2d() {}
	Edge2d(Point2d P1, Point2d P2): p1(P1), p2(P2) {}
	virtual void MoveBy(Vector2d V) = 0;
	virtual int PassThrough(Point2d* P) = 0;
	virtual Point2d ClosestPointTo(Point2d* P) = 0;
	virtual int Intersect(Line2d* L, Point2d* P) = 0;
	virtual Vector2d DirectionAt(Point2d P) = 0;
};


class LineSegment2d: public Edge2d, public Line2d {

public:
	LineSegment2d() {}
	LineSegment2d(Point2d P1, Point2d P2): Edge2d(P1,P2), Line2d(P1,&P2) {}
	LineSegment2d(Point2d P, Vector2d V): Edge2d(P,V+P), Line2d(P,V) {}
	void MoveBy(Vector2d V) {p = V + p; p1 = V + p1; p2 = V + p2;}
	int PassThrough(Point2d* P);
	Point2d ClosestPointTo(Point2d*);
	int Intersect(Line2d* L, Point2d* P) {return Line2d::Intersect(L, P);}
	Vector2d DirectionAt(Point2d P);
};


class Rectangle2d {

public:
	Point2d p;
	Vector2d d;
	void MoveBy(Vector2d V) { p = V + p;}
	int PassThrough(Point2d* P) { return (P->x > p.x && P->x < p.x+d.x || P->x < p.x && P->x > p.x+d.x) && (P->y > p.y && P->y < p.y+d.y || P->y < p.y && P->y > p.y+d.y);}
};


#endif
