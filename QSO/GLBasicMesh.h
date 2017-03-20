#pragma once
#include "GLMesh.h"
class GLBasicMesh : public GLMesh
{
public:
	GLBasicMesh(GLfloat *vertices, GLuint vertexCount, GLfloat *uv, GLuint *indices, GLuint indexCount, GLuint textureID);
	void setUpMesh();
	void drawMesh();
};

