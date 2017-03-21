#pragma once

#include <string>
#include <vector>

#include "Mesh.h"
#include "TextureManager.h"
#include "Component.h"

using namespace std;

struct TextureMaps {
	string diffuse;
	string specular;
	string emission;
};

class Shapes : public Component
{
protected:
	virtual void createMesh() = 0;
	vector<Mesh*> meshes;
	int numberOfMeshs;
	string textureName;
	TextureManager *textureManager;
	TextureMaps textureMaps;
public:
	Shapes(TextureManager *textureManager, string name);
	virtual ~Shapes();
	virtual Shapes* instantiate() = 0;
	vector<Mesh*> getMesh(int &numMeshs);
	void setTextureMaps(string diffuse, string specular = "", string emission = "");
	
};

