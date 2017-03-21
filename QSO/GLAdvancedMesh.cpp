#include "GLAdvancedMesh.h"

GLAdvancedMesh::~GLAdvancedMesh()
{
}

GLAdvancedMesh::GLAdvancedMesh()
{
}

GLAdvancedMesh::GLAdvancedMesh(GLfloat * vertices, GLuint vertexCount, GLfloat * uv, GLuint * indices, GLuint indexCount, GLfloat * normals, GLuint textureID, GLenum mode)
{
	GLMesh::vertices = vertices;
	GLMesh::uv = uv;
	GLMesh::indices = indices;
	GLMesh::vertexCount = vertexCount;
	GLMesh::indexCount = indexCount;
	GLMesh::normals = normals;
	GLMesh::mode = mode;

	GLMesh::textureID = textureID;
	setupMesh();
}

void GLAdvancedMesh::setupMesh()
{
	MeshData data = {
		GLMesh::vertices,
		GLMesh::normals,
		nullptr, // Color
		GLMesh::uv,
		GLMesh::indices,
		GLMesh::vertexCount,
		GLMesh::indexCount,
		GLMesh::mode
	};

	GLMesh::VAO = MeshGenerator::createMesh(data);
}

void GLAdvancedMesh::drawMesh()
{
	glBindVertexArray(GLMesh::VAO);
	glDrawElements(GLMesh::mode, GLMesh::indexCount, GL_UNSIGNED_BYTE, 0);
	glBindVertexArray(0);
}

void GLAdvancedMesh::setEmission(GLuint mapID)
{
	material.emission = mapID;
}

void GLAdvancedMesh::setDiffusion(GLuint mapID)
{
	material.diffuse = mapID;
}

void GLAdvancedMesh::setSpecular(GLuint mapID)
{
	material.specular = mapID;
}

void GLAdvancedMesh::setMaps(GLuint emissionID, GLuint diffusionID, GLuint specularID)
{
	material.emission = emissionID;
	material.diffuse = diffusionID;
	material.specular = specularID;

}
