#pragma once
#include "GLMesh.h"

class GLAdvancedMesh : public GLMesh
{
public:
	GLAdvancedMesh();
	GLAdvancedMesh(GLfloat *vertices, GLuint vertexCount, GLfloat *uv, GLuint *indices, GLuint indexCount, GLfloat *normals, GLuint textureID);
	void setupMesh();
	void drawMesh();
};

