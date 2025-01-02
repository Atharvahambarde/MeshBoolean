#include "Transformation.h"
#include "Matrix4x4.h"
#include <map>
#include <cmath>
#define TOLERANCE 0.0000001
#define PI 3.14159265359

using namespace Geometry;

bool Transformations::Transformation::operator()(double a, double b) const
{
    return fabs(a - b) > TOLERANCE ? a < b : false;
}

Triangulation Transformations::Transformation::scaling(Triangulation& triangulation, double scaleX, double scaleY, double scaleZ)
{
    Geometry::Matrix4x4 matrix;
    std::vector<double> nmatrix{ 0.0,0.0,0.0,0.0 };
    std::vector<Point> vertices;
    matrix.matrix[0][0] = scaleX;
    matrix.matrix[1][1] = scaleY;
    matrix.matrix[2][2] = scaleZ;
    std::map<double, int, Transformation> uniqueMap;
    Triangulation newtriangulation;

    for (Triangle tri : triangulation.Triangles)
    {
        std::vector<Point> tempvect;
        tempvect = tri.Points();
        tempvect.push_back(tri.Normal());
        for (Point pt : tempvect)
        {
            double xm = triangulation.UniqueNumbers[pt.X()];
            double ym = triangulation.UniqueNumbers[pt.Y()];
            double zm = triangulation.UniqueNumbers[pt.Z()];
            nmatrix = matrix.multiply(xm, ym, zm);
            int pts[3];
            for (size_t i = 0; i < 3; i++)
            {
                auto pair = uniqueMap.find(nmatrix[i]);
                if (pair == uniqueMap.end())
                {
                    newtriangulation.UniqueNumbers.push_back(nmatrix[i]);
                    uniqueMap[nmatrix[i]] = newtriangulation.UniqueNumbers.size() - 1;
                    pts[i] = newtriangulation.UniqueNumbers.size() - 1;

                }
                else
                {
                    pts[i] = pair->second;

                }
            }
            vertices.push_back(Point(pts[0], pts[1], pts[2]));
        }
        newtriangulation.Triangles.push_back(Triangle(vertices[3], vertices[0], vertices[1], vertices[2]));
        vertices.clear();
    }
    return newtriangulation;
}

Triangulation Transformations::Transformation::translation(Triangulation& triangulation, double translateX, double translateY, double translateZ)
{
    std::vector<double> nmatrix{ 0.0,0.0,0.0,0.0 };
    std::vector<Point> vertices;
    Geometry::Matrix4x4 matrix;
    matrix.matrix[0][3] = translateX;
    matrix.matrix[1][3] = translateY;
    matrix.matrix[2][3] = translateZ;
    std::map<double, int, Transformation> uniqueMap;
    Triangulation newtriangulation;

    for (Triangle tri : triangulation.Triangles)
    {
        std::vector<Point> tempvect;
        tempvect = tri.Points();
        tempvect.push_back(tri.Normal());
        for (Point pt : tempvect)
        {
            double xm = triangulation.UniqueNumbers[pt.X()];
            double ym = triangulation.UniqueNumbers[pt.Y()];
            double zm = triangulation.UniqueNumbers[pt.Z()];
            nmatrix = matrix.multiply(xm, ym,zm);
            int pts[3];
            for (size_t i = 0; i < 3; i++)
            {
                auto pair = uniqueMap.find(nmatrix[i]);
                if (pair == uniqueMap.end())
                {
                    newtriangulation.UniqueNumbers.push_back(nmatrix[i]);
                    uniqueMap[nmatrix[i]] = newtriangulation.UniqueNumbers.size() - 1;
                    pts[i] = newtriangulation.UniqueNumbers.size() - 1;

                }
                else
                {
                    pts[i] = pair->second;

                }
            }
            vertices.push_back(Point(pts[0], pts[1], pts[2]));
        }
        newtriangulation.Triangles.push_back(Triangle(vertices[3], vertices[0], vertices[1], vertices[2]));
        vertices.clear();
    }
    return newtriangulation;
}

Triangulation Transformations::Transformation::rotationX(Triangulation& triangulation, double rotateX)
{
    std::vector<double> nmatrix{ 0.0,0.0,0.0,0.0 };
    std::vector<Point> vertices;
    Geometry::Matrix4x4 matrix;
    matrix.matrix[1][1] = cos((rotateX * PI) / 180);
    matrix.matrix[1][2] = -sin((rotateX * PI) / 180);
    matrix.matrix[2][1] = sin((rotateX * PI) / 180);
    matrix.matrix[2][2] = cos((rotateX * PI) / 180);
    std::map<double, int, Transformation> uniqueMap;
    Triangulation newtriangulation;

    for (Triangle tri : triangulation.Triangles)
    {
        std::vector<Point> tempvect;
        tempvect = tri.Points();
        tempvect.push_back(tri.Normal());
        for (Point pt : tempvect)
        {
            double xm = triangulation.UniqueNumbers[pt.X()];
            double ym = triangulation.UniqueNumbers[pt.Y()];
            double zm = triangulation.UniqueNumbers[pt.Z()];
            nmatrix = matrix.multiply(xm, ym, zm);
            int pts[3];
            for (size_t i = 0; i < 3; i++)
            {
                auto pair = uniqueMap.find(nmatrix[i]);
                if (pair == uniqueMap.end())
                {
                    newtriangulation.UniqueNumbers.push_back(nmatrix[i]);
                    uniqueMap[nmatrix[i]] = newtriangulation.UniqueNumbers.size() - 1;
                    pts[i] = newtriangulation.UniqueNumbers.size() - 1;

                }
                else
                {
                    pts[i] = pair->second;

                }
            }
            vertices.push_back(Point(pts[0], pts[1], pts[2]));
        }
        newtriangulation.Triangles.push_back(Triangle(vertices[3], vertices[0], vertices[1], vertices[2]));
        vertices.clear();
    }
    return newtriangulation;
}