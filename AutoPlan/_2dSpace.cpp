#include "stdafx.h"
#include "_2dSpace.h"


int Line2d::PassThrough(Point2d* P)
{
	Vector2d V = Vector2d(&p,P);
	double t = V.x*v.y - V.y*v.x;
	return (t < 0.000001 && t > -0.000001);
}

Point2d Line2d::ClosestPointTo(Point2d* P)
{
	return Point2d(Vector2d(&p,P).Product(v)/(v.x*v.x + v.y*v.y)*v + p);
}

int Line2d::Intersect(Line2d* L, Point2d* P)
{
	double t, td = v.y*L->v.x - L->v.y*v.x;
	if(td < 0.000001 && td > -0.000001) return 0;
	t = ((L->p.y - p.y)*L->v.x - (L->p.x - p.x)*L->v.y)/td;
	*P = Point2d(t*v + p);
	if((PassThrough(P) != 0) && (L->PassThrough(P) != 0)) return 1;
	return 0;
}

int Ray2d::PassThrough(Point2d* P)
{
	Vector2d V = Vector2d(&p,P);
	double t = V.x*v.y - V.y*v.x;
	if(t < 0.000001 && t> -0.000001)
	{
		if(V.Product(v) > 0) return 2;
		if(V.Product(v) == 0) return 1;
	}
	return 0;
}

Point2d Ray2d::ClosestPointTo(Point2d* P)
{
	Point2d P1 = Line2d::ClosestPointTo(P);
	if(PassThrough(&P1)) return P1;
	return p;

}

int LineSegment2d::PassThrough(Point2d* P)
{
	Vector2d V1 = Vector2d(&p1,P);
	Vector2d V2 = Vector2d(&p2,P);
	double t = V1.x*V2.y - V1.y*V2.x;
	if(t < 0.000001 && t > -0.000001)
	{
		if(V1.Product(V2) < 0) return 2;
		if(V1.Product(v) == 0) return 1;
		if(V2.Product(v) == 0) return 3;
	}
	return 0;
}

Point2d LineSegment2d::ClosestPointTo(Point2d* P)
{
	Point2d P1 = Line2d::ClosestPointTo(P);
	if(PassThrough(&P1)) return P1;
	if(Vector2d(&P1,&p1).Product(v) > 0) return p1;
	return p2;

}

Vector2d LineSegment2d::DirectionAt(Point2d P)
{
	Point2d Origin;
	if((p1.x - P.x)*(p1.x - P.x) + (p1.y - P.y)*(p1.y - P.y) < (p2.x - P.x)*(p2.x - P.x) + (p2.y - P.y)*(p2.y - P.y))
		Origin = p1;
	else Origin = p2;
	Vector2d Sample = Vector2d(&P, &Origin);
	Vector2d Direction = v/v.Abs();
	if(Direction.Product(Sample) > 0) return Direction;
	return Direction*-1;
}
