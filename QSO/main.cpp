#include <iostream>
#include "Shader.h"
#include "Window.h"
#include "glfwWindow.h"
#include "openGLHandler.h"
#include "Clock.h"
#include "TextureManager.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "glfwInputHandler.h"
#include "Terrain.h"
#include "Mesh.h"
#include "Polygon.h"
#include "PhysicsHandler.h"
using namespace std;

glfwInputHandler inputHandler;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	MouseInput* mouse = inputHandler.getMouse();
	mouse->setScrollOffset(vec2(xoffset, yoffset));
}


//Closing the application
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	KeyboardInput* keyboard = inputHandler.getKeyboard();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		inputHandler.setExit(true);
		cout << "Exit Pressed" << endl;
	}
		
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS) {
			keyboard->setKey(key, true);
			//cout << "key pressed" << endl;
		}
		else if (action == GLFW_RELEASE) {
			keyboard->setKey(key, false);
			//cout << "key released" << endl;
		}
			
	}
}

// Mouse control

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	
	//Check if this is the first time receiving the mouse input and if so, we first update the initial mouse position
	// to the new xpos and ypos values; the resuling mouse movement will then use the entered mouse's position
	// coordinates to calculate it's offset. - Helps avoid large offsets and movement jump when mouse enters the 
	// program display for the first time. 
	MouseInput* mouse = inputHandler.getMouse();
	if (firstMouse) {
		mouse->setPosition(vec2(xpos, ypos));
		firstMouse = false;
	}
	//Calcualate the offset movement between the last and current frames.
	vec2 mousePosition = mouse->getPosition();
	GLfloat xOffset = xpos - mousePosition.x;
	GLfloat yOffset = mousePosition.y - ypos; //Reverse since y-coordinates go from bottom to left
	mouse->setOffset(vec2(xOffset, yOffset));
	mouse->setPosition(vec2(xpos, ypos));
}

int main(int argc, char *argv[]) {

	glfwWindow *window = new glfwWindow(800, 600);
	openGLHandler graphicsHandler(window);
	//Physics World
	PhysicsHandler * _world = new PhysicsHandler();
	_world->setGravity(vec3(0, -10, 0));

	graphicsHandler.init(); // Initialize Rendering Library

	inputHandler = glfwInputHandler(window->getWindow());
	
	// Set the required callback functions to register
	glfwSetKeyCallback(window->getWindow(), key_callback);
	glfwSetCursorPosCallback(window->getWindow(), mouse_callback);
	glfwSetScrollCallback(window->getWindow(), scroll_callback);

	//GLFW Options
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Setup Camera

	Camera playerCamera (vec3(0,0,10.0f), vec3(0,1,0), 0.0f, 0.0f);
	playerCamera.setPerspectiveProjection(glm::radians(45.0f), float(Window::screenWIDTH) / float(Window::screenHEIGHT), 0.1f, 100.0f);
	playerCamera.setView(vec3(0.0f, 0.0f, -10.0f)); // Adjust our Camera back by changing Z value
	
	// Testing Texture Manager
	TextureManager textureManager;
	
	textureManager.saveTexture("lava.jpg", "lava");

	// Testing Shaders
	Shader minShaderProgram("minVertex.shader", "minFrag.shader"); // Initialize minShader Programs using selected shaders.

	// Testing Cube Renderer

	Transform transform;
	Transform terrainTransform;
	Material material;
	material.texture = "lava";
	
	//Mesh Objects
	MeshRenderer MeshRenderer1(material, &textureManager, &terrainTransform, &minShaderProgram, &playerCamera);
	MeshRenderer MeshRenderer2(material, &textureManager, &transform, &minShaderProgram, &playerCamera);
	
	Polygon cube;
	cube.init();

	// Testing Terrain Triangle Strips

	Terrain terrain("terrain", 50, 50, 1.0f);
	terrain.init();
	Mesh terrainMesh = Mesh("terrain");
	mapData terrainData = terrain.getData();
	terrainMesh.mesh.vertices = (GLfloat*)terrainData.vertices;
	terrainMesh.mesh.indices = terrainData.indices;
	terrainMesh.mesh.normals = (GLfloat*)terrainData.normals;
	terrainMesh.mesh.indexCount = terrainData.indexCount;
	terrainMesh.mesh.vertexCount = terrainData.vertexCount;
	terrainMesh.mesh.mode = GL_TRIANGLE_STRIP;
	terrainMesh.generateMesh();

	// Set Frame Rate
	Clock frameClock;
	frameClock.startClock();
	frameClock.setDelay(1000.0f / 60.0f); //60 FPS

	double previousTime = 0.0f;
	double currentTime = 0.0f;

	// Testing Clock

	Clock clock;
	clock.startClock();

	KeyboardInput* keyboard = inputHandler.getKeyboard();

	terrainTransform.translate(0, 1, 0);
	terrainTransform.calculateModelMatrix();
	/* Physics Stuff  Temp */


	RigidBody *groundRigidBody = new RigidBody();
	groundRigidBody->addCollider(new btStaticPlaneShape(btVector3(0, 1, 0), 1));
	groundRigidBody->addMotionState(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0))));
	groundRigidBody->init();

	_world->addRigidBody(groundRigidBody);
	RigidBody *fallBody = new RigidBody();;
	fallBody->setMass(1);
	fallBody->addCollider(new btSphereShape(1));
	fallBody->addMotionState(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, -10))));
	fallBody->calculateLocalInertia();
	fallBody->init();

	_world->addRigidBody(fallBody);
	/* End of Physics Stuff Temp */

	// Game Loop
	while (!inputHandler.quitApplication()) {

		//Checks and calls events
		inputHandler.pollEvent();

		frameClock.updateClock(); // Ticks our Frame Clock
		clock.updateClock(); //Ticks App Clock

		// Calculates Delta Time
		
		currentTime = clock.getMilliseconds();
		double dt = (currentTime - previousTime) * 0.001f; //Convert DT to seconds

		//End of DeltaTime
		if (frameClock.alarm()) {

			// Process Inputs & Camera controls
			_world->stepSimulation(dt, 10);
			vec3 trans = fallBody->getMotionState();

			transform.setPosition(trans);

			playerCamera.processMouseScroll(*inputHandler.getMouse(), dt);
			playerCamera.processCameraMouseMovement(*inputHandler.getMouse(), dt);
			playerCamera.processKeyBoard(*inputHandler.getKeyboard(), dt);
			
			playerCamera.GetViewMatrix();
			inputHandler.getMouse()->setLastPosition(inputHandler.getMouse()->getPosition());
			inputHandler.getMouse()->setLastScrollOffset(inputHandler.getMouse()->getScrollOffset());

			// End of Process Inputs

			// Update Function
			
			graphicsHandler.start();  // Sets up Rendering Loop
			
			// Render Function
			MeshRenderer1.renderObject(&terrainMesh); 

			MeshRenderer2.renderObject(&cube);

			// End of Render

			graphicsHandler.end(); // Swaps scene buffers
			frameClock.resetClock(); // Once frame is done reset to 0
			previousTime = currentTime;
		}
	}
	_world->removeRigidBody(groundRigidBody);
	groundRigidBody->destroy();
	_world->removeRigidBody(fallBody);
	fallBody->destroy();
	_world->destroy();
	/* End of Physics THing*/
	MeshGenerator::destroy();
	graphicsHandler.destroy();

	return 0;
}
