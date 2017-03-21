#pragma once

#include <string>
#include <vector>

#include "Mesh.h"
#include "TextureManager.h"
#include "Component.h"

using namespace std;

class Shapes : public Component
{
protected:
	virtual void createMesh() = 0;
	vector<Mesh*> meshes;
	int numberOfMeshs;
	string textureName;
	TextureManager *textureManager;
public:
	Shapes(TextureManager *textureManager, string name);
	virtual ~Shapes();
	virtual Shapes* instantiate() = 0;
	vector<Mesh*> getMesh(int &numMeshs);
	
};

