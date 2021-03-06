#pragma once

#include "Mesh.h"
#include "Shape.h"

class Polygon : public Shape
{
public:
	Polygon();
	virtual ~Polygon();

	
	void init();

	void buildFace(Mesh *mesh, vec3 corner, vec3 up, vec3 right, bool reverse);

};

