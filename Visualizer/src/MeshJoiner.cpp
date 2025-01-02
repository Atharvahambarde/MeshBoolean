#include "MeshJoiner.h"
#include "Triangulation.h"
using namespace Geometry;

MeshJoiner::MeshJoiner()
{

}

MeshJoiner::~MeshJoiner()
{

}

std::vector<Triangulation> MeshJoiner::performTransformations(std::vector<Triangulation>& triangulations)
{

    Transformations::Transformation transformer;
    Triangulation triangulationOne = triangulations[0];
    Triangulation triangulationTwo = triangulations[1];

    //from triangultions select first triangle
    Triangle triangle1 = triangulationOne.Triangles[0];
    Triangle triangle2 = triangulationTwo.Triangles[0];

    Point firstNormalPoint = triangle1.Normal();
    RealPoint firstNormal = triangulationOne.getRealPoint(firstNormalPoint);

    Point secondNormalPoint = triangle2.Normal();
    RealPoint secondNormal = triangulationTwo.getRealPoint(secondNormalPoint);


    double angle1 = firstNormal.getAngleBetweenNormalAndXAxis();
    double angle2 = secondNormal.getAngleBetweenNormalAndXAxis();

    // First Triangle avg
    Point firstTriangleP1 = triangle1.P1();
    Point firstTriangleP2 = triangle1.P2();
    Point firstTriangleP3 = triangle1.P3();
    //RealPoint of First Triangle avg
    RealPoint firstRealPoint1 = triangulationOne.getRealPoint(firstTriangleP1);
    RealPoint firstRealPoint2 = triangulationOne.getRealPoint(firstTriangleP2);
    RealPoint firstRealPoint3 = triangulationOne.getRealPoint(firstTriangleP3);
    Geometry::RealPoint avgFirstTriangle = triangle1.triangleCentroid(firstRealPoint1, firstRealPoint2, firstRealPoint3);

    // Align the first triangulation's to the origin and normalize its orientation
    triangulationOne = transformer.translation(triangulationOne, -(avgFirstTriangle.X()), -(avgFirstTriangle.Y()), -(avgFirstTriangle.Z()));
    triangulationOne = transformer.rotationX(triangulationOne, -angle1);

    // Second Triangle average
    Point secondTriangleP1 = triangle2.P1();
    Point secondTriangleP2 = triangle2.P2();
    Point secondTriangleP3 = triangle2.P3();
    //RealPoint of Second Triangle average
    RealPoint secondRealPoint1 = triangulationTwo.getRealPoint(secondTriangleP1);
    RealPoint secondRealPoint2 = triangulationTwo.getRealPoint(secondTriangleP2);
    RealPoint secondRealPoint3 = triangulationTwo.getRealPoint(secondTriangleP3);
    Geometry::RealPoint avgSecondTriangle = triangle2.triangleCentroid(secondRealPoint1, secondRealPoint2, secondRealPoint3);

    // Align the Second triangulation's to the origin and normalize its orientation
    triangulationTwo = transformer.translation(triangulationTwo, -(avgSecondTriangle.X()), -(avgSecondTriangle.Y()), -(avgSecondTriangle.Z()));
    triangulationTwo = transformer.rotationX(triangulationTwo, -angle2);

    // Restore and align both triangulations' orientations.
    triangulationOne = transformer.rotationX(triangulationOne, angle1);
    triangulationTwo = transformer.rotationX(triangulationTwo, angle1);

    // Translate both triangulations back according to the first triangle's centroid.
    triangulationOne = transformer.translation(triangulationOne, (avgFirstTriangle.X()), (avgFirstTriangle.Y()), (avgFirstTriangle.Z()));
    triangulationTwo = transformer.translation(triangulationTwo, (avgFirstTriangle.X()), (avgFirstTriangle.Y()), (avgFirstTriangle.Z()));

    std::vector<Triangulation> resultTriangulation;
    resultTriangulation.push_back(triangulationOne);
    resultTriangulation.push_back(triangulationTwo);

    return resultTriangulation;
}
