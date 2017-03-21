#include "Polygon.h"



void Polygon::createMesh()
{
	Mesh* mesh0 = buildFace("leftFace", mesh0, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), false);

	Mesh* mesh1 = buildFace("rightFace", mesh1, vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), true);

	Mesh* mesh2 = buildFace("bottomFace", mesh2, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), false);

	Mesh* mesh3 = buildFace("topFace", mesh3, vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), true);

	Mesh* mesh4 = buildFace("bottomFace", mesh4, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), true);

	Mesh* mesh5 = buildFace("frontFace", mesh5, vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), false);
	
	Shapes::numberOfMeshs = 6;
	Shapes::meshes.push_back(mesh0);
	Shapes::meshes.push_back(mesh1);
	Shapes::meshes.push_back(mesh2);
	Shapes::meshes.push_back(mesh3);
	Shapes::meshes.push_back(mesh4);
	Shapes::meshes.push_back(mesh5);
}

Polygon::Polygon(std::string polygonName, std::string textureName, TextureManager *textureManager) : Shapes(textureManager, polygonName)
{
	Shapes::textureName = textureName;
	createMesh();
}

Shapes * Polygon::instantiate()
{
	string instance = to_string(instance_id + 1);
	Shapes *shape = new Polygon(string(name + instance), Shapes::textureName, Shapes::textureManager);
	return shape;
}

Polygon::~Polygon()
{
}

Mesh *Polygon::buildFace(string name, Mesh * mesh, vec3 corner, vec3 up, vec3 right, bool reverse)
{
	GLfloat vertex[12];
	vertex[0] = corner.x;
	vertex[1] = corner.y;
	vertex[2] = corner.z;

	vec3 cVertex = corner + up;
	vertex[3] = cVertex.x;
	vertex[4] = cVertex.y;
	vertex[5] = cVertex.z;

	cVertex = corner + up + right;
	vertex[6] = cVertex.x;
	vertex[7] = cVertex.y;
	vertex[8] = cVertex.z;

	cVertex = corner + right;
	vertex[9] = cVertex.x;
	vertex[10] = cVertex.y;
	vertex[11] = cVertex.z;

	vec3 vertex1(vertex[0], vertex[1], vertex[2]);
	vec3 vertex2(vertex[3], vertex[4], vertex[5]);
	vec3 vertex3(vertex[6], vertex[7], vertex[8]);
	vec3 vertex4(vertex[9], vertex[10], vertex[11]);

	vec3 v1Normal = cross((vertex2 - vertex1), (vertex3 - vertex1));
	
	if (!reverse) {
		v1Normal = -v1Normal;
	}
	
	// Need to check if top/bottom and get correct normals
	if (mesh->toString() == "topFace" || mesh->toString() == "bottomFace") {
	//	v1Normal = -v1Normal;
	}

	GLfloat normal[12]{
		v1Normal.x, v1Normal.y, v1Normal.z,
		v1Normal.x, v1Normal.y, v1Normal.z,

		v1Normal.x, v1Normal.y, v1Normal.z,
		v1Normal.x, v1Normal.y, v1Normal.z

	};

	GLfloat uv[8] = {
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
	};

	GLuint *indices;
	if (reverse) {
		GLuint index[6] = {
			0, 1, 2,
			2, 3, 0
		};

		indices = index;
	}
	else {
		GLuint index[6] = {
			1, 0 ,2,
			3, 2, 0
		};

		indices = index;
	}
	
	return new GLAdvancedMesh(vertex, 6, uv, indices, 6, normal, textureManager->getTexture(Shapes::textureName));
}
