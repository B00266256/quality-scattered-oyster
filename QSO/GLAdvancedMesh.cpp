#include "GLAdvancedMesh.h"

GLAdvancedMesh::~GLAdvancedMesh()
{
}

GLAdvancedMesh::GLAdvancedMesh(GLfloat * vertices, GLuint vertexCount, GLfloat * uv, GLuint * indices, GLuint indexCount, GLfloat * normals, GLuint textureID)
{
	GLMesh::vertices = vertices;
	GLMesh::uv = uv;
	GLMesh::indices = indices;
	GLMesh::vertexCount = vertexCount;
	GLMesh::indexCount = indexCount;
	GLMesh::normals = normals;
	GLMesh::mode = GL_TRIANGLES;

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
}

void GLAdvancedMesh::drawMesh()
{
	glBindVertexArray(GLMesh::VAO);
	glDrawElements(GLMesh::mode, GLMesh::indexCount, GL_UNSIGNED_BYTE, 0);
	glBindVertexArray(0);
}
