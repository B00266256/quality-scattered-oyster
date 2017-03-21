#pragma once

#include "GL\glew.h"
#include "Mesh.h"

struct Materials {
	GLuint ambient;
	GLuint diffuse;
	GLuint specular;
	GLfloat *color;
	GLuint emission;
	GLuint shininess;
};

class GLMesh : public Mesh
{
protected:
	GLuint VAO;
	GLuint textureID;

	GLfloat *vertices;
	GLfloat *normals;
	GLuint *indices;
	GLfloat *uv;
	GLuint vertexCount;
	GLuint indexCount;
	GLenum mode;

	Materials material;

public:
	GLMesh(); 
	virtual void setupMesh() = 0;
	virtual void drawMesh() = 0;
	virtual void destroy();

	GLuint getTextureID();
	Materials getMaterial();
};

