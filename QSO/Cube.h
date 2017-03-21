#pragma once

#include "Shapes.h"
#include "GLAdvancedMesh.h"

class Cube : public Shapes
{
private:
	void createMesh();
public:
	Cube(std::string cubeName, std::string textureName, TextureManager *textureManager);

	Shapes* instantiate();
	void buildCube();
};

