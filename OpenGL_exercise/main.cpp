#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Systems/BulletManager.h"
#include "Systems/Time.h"
#include "Systems/Camera.h"
#include "Systems/Input.h"
#include "GameObjects/Player.h"
#include "Shapes/GDShape.h"

using namespace glm;


// Window dimensions
const int WIDTH = 720, HEIGHT = 720;

mat4 ORTHO_MAT = ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);
mat4 VIEW_MAT = mat4(1.0f);

GLFWwindow* window = nullptr;

Time* gameTime;
Camera* camera;
Input* input;
Player* player;


bool set_environment();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);


int main()
{
	if (!set_environment())
		return -1;

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);


	camera = new Camera(ORTHOGONAL);
	gameTime = new Time;
	input = new Input;

	Bullet* playerBullet = new Bullet(new GDShape("GeometryData/BulletA.gd"), camera);
	BulletManager::GetInstance()->AddBulletTypeToPool(PlayerBullet, *playerBullet, 100);

	player = new Player(new GDShape("GeometryData/PlayerShape.gd"), camera, input);
	

	// Game loop
	while (!glfwWindowShouldClose(window)) {
		
		gameTime->Update();

		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		player->Update(gameTime->deltaTime);
		BulletManager::GetInstance()->Update(gameTime->deltaTime);

		// Swap the screen buffers (Double buffers)
		glfwSwapBuffers(window);
	}

	delete player;
	delete input;
	delete gameTime;
	delete camera;

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	input->OnKeyPress(key, action);
}


void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	input->OnMouseMove(xPos, yPos);
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	input->OnMouseClick(button, action);
}


void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
	input->OnScrollMove(xOffset, yOffset);
}


bool set_environment() {
	// Init GLFW
	glfwInit();

	// Set all requirements for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create GLFWwindow object that can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "TestOpenGL", nullptr, nullptr);
	
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	// Define viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// Enable depth test
	// glEnable(GL_DEPTH_TEST);

	return true;
}