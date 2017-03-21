#include "GLMesh.h"



GLMesh::GLMesh()
{
}

void GLMesh::destroy()
{
	delete vertices;
	delete indices;
	delete uv;
	delete normals;
}

GLuint GLMesh::getTextureID()
{
	return GLMesh::textureID;
}

Materials GLMesh::getMaterial()
{
	return material;
}


GLMesh::~GLMesh()
{
	destroy();
}
