#include "Shapes.h"



Shapes::Shapes(TextureManager* textureManager, string name) : Component(name)
{
	Shapes::textureManager = textureManager;
}


Shapes::~Shapes()
{
	for (int i = 0; i < meshes.size(); i++) {

		delete meshes[i];
	}	
}

vector<Mesh*> Shapes::getMesh(int & numMeshs)
{
	numMeshs = Shapes::numberOfMeshs;
	return Shapes::meshes;
}

void Shapes::setTextureMaps(string diffuse, string specular, string emission)
{
	textureMaps.diffuse = diffuse;
	textureMaps.specular = specular;
	textureMaps.emission = emission;
}