#include <vector>
#include "Triangle.h"

using namespace Geometry;

Triangle::Triangle(Point normal, Point p1, Point p2, Point p3)
    : p1(p1), p2(p2), p3(p3), normal(normal)
{
}

Triangle::~Triangle()
{

}

Point Triangle::P1()
{
    return p1;
}

Point Triangle::P2()
{
    return p2;
}

Point Triangle::P3()
{
    return p3;
}

std::vector<Point> Triangle::Points()
{
    std::vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    return points;
}

Point Triangle::Normal()
{
    return normal;
}

RealPoint Geometry::Triangle::triangleCentroid(RealPoint& p1, RealPoint& p2, RealPoint& p3)
{
    double avgX = (p1.X() + p2.X() + p3.X()) / 3;
    double avgY = (p1.Y() + p2.Y() + p3.Y()) / 3;
    double avgZ = (p1.Z() + p2.Z() + p3.Z()) / 3;

    RealPoint avgPoint(avgX, avgY, avgZ);
    return avgPoint;
}