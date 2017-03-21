#include "GLRenderer.h"

GLRenderer::GLRenderer(Shader *program)
{
	GLRenderer::program = program;
}

GLRenderer::~GLRenderer()
{
}

float hueshift = 0.0f;
void GLRenderer::renderObject(Shapes *shape)
{
	/*Draw Cube*/
	/*Use Material*/
	GLuint VAO, textureID;
	GLRenderer::program->Use();

	int numberOfMeshs;
	vector<Mesh*> meshes = shape->getMesh(numberOfMeshs);

	Transform lampPos;
	Transform sunPos;

	mat4 model;
	lampPos.translate(vec3(0.0f, 25.0f, 0.0f));
	lampPos.calculateModelMatrix();

	sunPos.translate(vec3(0.0f, 100.0f, 0.0f));
	sunPos.calculateModelMatrix();

	// Don't forget to 'use' the corresponding shader program first (to set the uniform)
	GLint objectColorLoc = glGetUniformLocation(GLRenderer::program->program, "objectColor");
	GLint lightColorLoc = glGetUniformLocation(GLRenderer::program->program, "lightColor");
	GLint lightPosLoc = glGetUniformLocation(GLRenderer::program->program, "lightPos"); // Depreciated Code soon. May need deleting
	GLint lightPositionLoc = glGetUniformLocation(GLRenderer::program->program, "light.position");
	GLint viewPosLoc = glGetUniformLocation(GLRenderer::program->program, "viewPos");
	GLint matAmbientLoc = glGetUniformLocation(GLRenderer::program->program, "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(GLRenderer::program->program, "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(GLRenderer::program->program, "material.specular");
	GLint matShineLoc = glGetUniformLocation(GLRenderer::program->program, "material.shininess");
	GLint lightAmbientLoc = glGetUniformLocation(GLRenderer::program->program, "light.ambient");
	GLint lightDiffuseLoc = glGetUniformLocation(GLRenderer::program->program, "light.diffuse");
	GLint lightSpecularLoc = glGetUniformLocation(GLRenderer::program->program, "light.specular");
	GLint lightDirPos = glGetUniformLocation(GLRenderer::program->program, "light.direction");
	GLint lightConstantPos = glGetUniformLocation(GLRenderer::program->program, "light.constant");
	GLint lightLinearPos = glGetUniformLocation(GLRenderer::program->program, "light.linear");
	GLint lightQuadraticPos = glGetUniformLocation(GLRenderer::program->program, "light.quadratic");
	GLint ourImageLoc = glGetUniformLocation(GLRenderer::program->program, "ourImage"); 
	GLint hueShiftLoc = glGetUniformLocation(GLRenderer::program->program, "hueShift");
	GLint satBoostLoc = glGetUniformLocation(GLRenderer::program->program, "satBoost");
	

	glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.0f);
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f); // Also set light's color (white)
	glUniform3f(lightPosLoc, lampPos.getPosition().x, lampPos.getPosition().y, lampPos.getPosition().z);
	glUniform3f(viewPosLoc, camera->Position.x, camera->Position.y, camera->Position.z);
	// Set Material Properties
	glUniform3f(matAmbientLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matDiffuseLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
	glUniform1f(matShineLoc, 32.0f);
	// Set Light Properties
	glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f); // Darken the light a bit to fit the scene
	glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(lightDirPos, lampPos.getPosition().x, lampPos.getPosition().y, lampPos.getPosition().z);
	glUniform3f(lightPositionLoc, lampPos.getPosition().x, lampPos.getPosition().y, lampPos.getPosition().z);
	// Set Light attenuation properties <- See for value reference: http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	glUniform1f(lightConstantPos, 1.0f);
	glUniform1f(lightLinearPos, 0.09f);
	glUniform1f(lightQuadraticPos, 0.032f);
	// Set HSV properties
	glUniform3f(ourImageLoc, 1.0f, 1.0f, 0.0f);
	glUniform1f(hueShiftLoc, hueshift);
	glUniform1f(satBoostLoc, 1.0f);
	hueshift += 0.0005f;

	// Create camera transformations
	mat4 view = camera->getView();
	mat4 projection = camera->getProjection();

	// Get matrix's uniform location, get and set matrix
	GLuint modelLoc = glGetUniformLocation(GLRenderer::program->program, "model");
	GLuint viewLoc = glGetUniformLocation(GLRenderer::program->program, "view");
	GLuint projectionLoc = glGetUniformLocation(GLRenderer::program->program, "projection");
	GLuint alphaLoc = glGetUniformLocation(GLRenderer::program->program, "ourAlpha");
	GLuint normalMatrixLoc = glGetUniformLocation(GLRenderer::program->program, "normalMatrix");

	// Pass to Shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform1f(alphaLoc, 1.0f);
	
	// glBindTexture call will bind that texture to the currently active texture unit.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, glMesh->getTextureID());
	glUniform1i(glGetUniformLocation(program->program, "ourUV"), 0);
	//By setting them via glUniform1i we make sure each uniform sampler corresponds to the proper texture unit.
	
	for (int i = 0; i < numberOfMeshs; i++) {
		GLMesh *glMesh = dynamic_cast<GLMesh*>(meshes[i]);

		// Get Model Matrix
		model = glMesh->getModelMatrix();
		mat3 normalMatrix = transpose(inverse(mat3(model)));
		glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		Materials material = glMesh->getMaterial();



		if (material.diffuse != 0) {
			//Bind Diffuse map
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, material.diffuse);
			glUniform1i(glGetUniformLocation(program->program, "material.diffuse"), POSITION);
		}

		//if (material.color != "") {
		//	glUniform1i(glGetUniformLocation(program->program, "material.color"), COLOR);
		//}

		if (material.emission != 0) {

			//Bind Emission map
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, material.emission);
			glUniform1i(glGetUniformLocation(program->program, "material.emission"), UV);
		}

		if (material.specular != 0) {

			//Bind Specular map
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, material.specular);
			glUniform1i(glGetUniformLocation(program->program, "material.specular"), NORMAL);
		}

		// Draw Mesh
		glMesh->drawMesh();
	}
}