#pragma once
#include "Triangulation.h"
#include "Matrix4x4.h"
using namespace Geometry;

namespace Transformations
{
	class Transformation
	{
	public:
		bool operator()(double a, double b) const;
		Triangulation scaling(Triangulation& triangulation, double scaleX = 2.0, double scaleY = 2.0, double scaleZ = 1.0);
		Triangulation translation(Triangulation& triangulation, double translateX = 10.0, double translateY = 10.0, double translateZ = 1.0);
		Triangulation rotationX(Triangulation& triangulation, double rotateX = 0);
	};
}