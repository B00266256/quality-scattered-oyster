#pragma once

#include <glm\glm.hpp>
#include "Component.h"
#include "MeshGenerator.h"


class Mesh : public Component
{
protected:
	glm::mat4 modelMatrix;
public:
	Mesh();
	Mesh(std::string name);
	virtual ~Mesh();

	virtual void setUpMesh() = 0;
	virtual void drawMesh() = 0;
	virtual void destroy();

	void updateModelMatrix(glm::mat4 modelMatrix);
	glm::mat4 getModelMatrix();
};

