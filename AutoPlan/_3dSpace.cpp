#include "stdafx.h"
#include "_3dSpace.h"


int Line::PassThrough(Point* P)
{
	Vector V = Vector(&p,P);
	return Vector(0,0,0) == V*v;
}

Point Line::ClosestPointTo(Point* P)
{
	return Point(Vector(&p,P).Product(v)/pow(v.Abs(),2)*v + p);
}

int Line::Intersect(Line* L, Point* P)
{
	Vector df = Vector(&p,&L->p);
	Vector nv = v*L->v;
	if(nv == Vector(0,0,0) || df.Product(nv) != 0) return 0; //Check the correctness
	Vector projection1 = df.Product(v)/pow(v.Abs(),2)*v;
	Point P1 = projection1 + p;
	Vector normal = Vector(&P1,&L->p);
	double t = -(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z)/normal.Product(L->v); 
	*P = Point(t*L->v + L->p);
	if((PassThrough(P) != 0) && (L->PassThrough(P) != 0)) return 1;
	return 0;
}

int Ray::PassThrough(Point* P)
{
	Vector V = Vector(&p,P);
	if(Vector(0,0,0) == V*v)
	{
		if(V.Product(v) > 0) return 2;
		if(V.Product(v) == 0) return 1;
	}
	return 0;
}

Point Ray::ClosestPointTo(Point* P)
{
	Point P1 = Line::ClosestPointTo(P);
	if(PassThrough(&P1)) return P1;
	return p;

}

int LineSegment::PassThrough(Point* P)
{
	Vector V1 = Vector(&p1,P);
	Vector V2 = Vector(&p2,P);
	if(Vector(0,0,0) == V1*V2)
	{
		if(V1.Product(V2) < 0) return 2;
		if(V1.Product(v) == 0) return 1;
		if(V2.Product(v) == 0) return 3;
	}
	return 0;
}

Point LineSegment::ClosestPointTo(Point* P)
{
	Point P1 = Line::ClosestPointTo(P);
	if(PassThrough(&P1)) return P1;
	if(Vector(&P1,&p1).Product(v) > 0) return p1;
	return p2;

}

int Plane::PassThrough(Point* P)
{
	Vector r = Vector(P,&p);
	return (fabs(r.Product(n)) < 0.000001);
}

int Plane::Intersect(Line* L, Point* P)
{
	if(fabs(n.Product(L->v)) < 0.000001) return 0;
	double t = ((p.x - L->p.x)*n.x + (p.y - L->p.y)*n.y + (p.z - L->p.z)*n.z)/(L->v.x*n.x + L->v.y*n.y + L->v.z*n.z);
	*P = Point(t*L->v.x + L->p.x, t*L->v.y+ L->p.y, t*L->v.z + L->p.z);
	if(PassThrough(P) && L->PassThrough(P)) return 1;
	return 0;
}

int Plane::Intersect(Plane* P, Line* L)
{
	if(Vector(0,0,0) == n*P->n)
	{
		double a = n.x;
		double b = n.y;
		double c = P->n.x;
		double d = P->n.y;
		double k = n.x*p.x + n.y*p.y + n.z*p.z;
		double l = P->n.x*P->p.x + P->n.y*P->p.y + P->n.z*P->p.z;
		Point P1 = Point((d*k - b*l)/(a*d - b*c),(a*l - c*k)/(a*d - b*c),0);
		*L = Line(P1,n*P->n);
		return 1;
	}
	else return 0;
}

void VerticalRect::SetPosition(Point2d point1, Point2d point2)
{
	SetRectangle(Point(point1.x, point1.y, p.z), Vector2d(&point1, &point2), h);
}

int VerticalRect::PassThrough(Point* P)
{
	if(Plane::PassThrough(P) == 0) return 0;
	return ((P->x <= p.x + 0.000001 && P->x >= p.x+d.x - 0.000001 || P->x >= p.x - 0.000001 && P->x <= p.x+d.x + 0.000001) && 
			(P->y <= p.y + 0.000001 && P->y >= p.y+d.y - 0.000001 || P->y >= p.y - 0.000001 && P->y <= p.y+d.y + 0.000001) &&
			(P->z <= p.z + 0.000001 && P->z >= p.z+h - 0.000001 || P->z >= p.z - 0.000001 && P->z <= p.z+h + 0.000001)	);
}

Point2d VerticalRect::ClosestPoint2dTo(Point2d* P)
{
	LineSegment2d L = LineSegment2d(Point2d(p.x, p.y), Point2d(p.x + d.x, p.y + d.y));
	return L.ClosestPointTo(P);
}

int VerticalRect::Intersect2d(Line2d* L, Point2d* P)
{
	LineSegment2d L2d = LineSegment2d(Point2d(p.x, p.y), Point2d(p.x + d.x, p.y + d.y));

	return L2d.Intersect(L, P);
}

int Parallelogram::PassThrough(Point* P)
{
	if(!Plane::PassThrough(P)) return 0;
	Vector v, q1, q2;
	double vq1, vq2, v1q1, v2q1, v2q2;
	q1 = v1/v1.Abs();
	v1q1 = q1.Product(v1);
	v2q1 = q1.Product(v2);
	q2 = v2 - v2q1*q1;
	q2 = q2/q2.Abs();
	v2q2 = q2.Product(v2);
	v = Vector(&p,P);
	vq1 = q1.Product(v);
	vq2 = q2.Product(v);
	return vq1 <= v2q1*vq2/v2q2 + v1q1 && vq1 >= v2q1*vq2/v2q2 && vq2 <= v2q2 && vq2 >= 0;
}

/*
Point* Parallelogram::Intersect(Line* L)
{
	Point* P = Plane::Intersect(L);
	if(!P) return 0;
	if(PassThrough(P)) return P;
	delete P;
	return 0;
}
*/

