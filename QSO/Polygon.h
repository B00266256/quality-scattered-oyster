#pragma once

#include "Mesh.h"
#include "Shapes.h"

class Polygon : public Shapes
{
public:
	Polygon();
	virtual ~Polygon();

	
	void init();

	void buildFace(Mesh *mesh, vec3 corner, vec3 up, vec3 right, bool reverse);

};

