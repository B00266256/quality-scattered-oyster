#pragma once

#include "Shapes.h"
#include "GLAdvancedMesh.h"

class Polygon : public Shapes
{
private:
	void createMesh();
public:
	Polygon(std::string PolygonName, std::string textureName, TextureManager *textureManager);
	Mesh* buildFace(string name, vec3 corner, vec3 up, vec3 right, bool reverse);
	Shapes* instantiate();
};

