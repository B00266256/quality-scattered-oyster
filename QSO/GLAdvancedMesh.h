#pragma once
#include "GLMesh.h"

class GLAdvancedMesh : public GLMesh
{
public:
	GLAdvancedMesh();
	GLAdvancedMesh(GLfloat *vertices, GLuint vertexCount, GLfloat *uv, GLuint *indices, GLuint indexCount, GLfloat *normals, GLuint textureID);
	void setupMesh();
	void drawMesh();
	void setEmission(GLuint mapID);
	void setDiffusion(GLuint mapID);
	void setSpecular(GLuint mapID);
	void setMaps(GLuint diffusionID, GLuint specularID = 0, GLuint emissionID = 0);
};

