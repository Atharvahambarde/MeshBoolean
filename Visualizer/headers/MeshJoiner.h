#pragma once
#include "Triangulation.h"
#include "Transformation.h"
using namespace Geometry;


class MeshJoiner
{
public:
	MeshJoiner();
	~MeshJoiner();

	std::vector<Triangulation> performTransformations(std::vector<Triangulation>& triangulations);

};
