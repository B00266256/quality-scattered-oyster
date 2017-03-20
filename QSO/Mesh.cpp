#include "Mesh.h"


Mesh::Mesh() : Component("")
{

}

Mesh::Mesh(std::string name): Component(name)
{

}


Mesh::~Mesh()
{
}

void Mesh::destroy()
{
}

void Mesh::updateModelMatrix(glm::mat4 modelMatrix)
{
	Mesh::modelMatrix = modelMatrix;
}

glm::mat4 Mesh::getModelMatrix()
{
	return Mesh::modelMatrix;
}

