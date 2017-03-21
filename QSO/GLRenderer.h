#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "Shader.h"
#include "GLMesh.h"
#include "Shapes.h"

class GLRenderer : public Renderer
{
private:
	Shader *program;

public:
	GLRenderer(Shader *program);
	virtual ~GLRenderer();

	void renderObject(Shapes *shape);
};

