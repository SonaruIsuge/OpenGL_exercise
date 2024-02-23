#define GLEW_STATIC

#include <iostream>
#include <Windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Systems/BulletManager.h"
#include "Systems/EnemyManager.h"
#include "Systems/LevelManager.h"
#include "Systems/Time.h"
#include "Systems/Camera.h"
#include "Systems/Input.h"
#include "Systems/Background.h"
#include "Tools/GameSettings.h"
#include "GameObjects/Player.h"
#include "Shapes/GDShape.h"

using namespace glm;

GLFWwindow* window = nullptr;
Time* gameTime;
Camera* camera;
Input* input;
Player* player;
Background* bg;

bool set_environment();
void initGame();
void endGame(bool gameOver, bool gameClear);
void printGameData(bool gameOver, bool gameClear);
void destroy();
vec3 GetTimeHMS(float time);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);


int main()
{
	if (!set_environment())
		return -1;

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	initGame();
	LevelManager levelManager(*player, *camera);
	levelManager.Init();

	// Game loop
	while (!glfwWindowShouldClose(window)) {
		// first check if game over
		if (LevelManager::GAME_OVER || levelManager.CheckGameClear() ) {
			endGame(LevelManager::GAME_OVER, levelManager.CheckGameClear());
			break;
		}

		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		gameTime->Update();
		bg->Update(gameTime->deltaTime);
		levelManager.Update(gameTime->deltaTime);
		BulletManager::GetInstance()->Update(gameTime->deltaTime);
		EnemyManager::GetInstance()->Update(gameTime->deltaTime);
		player->Update(gameTime->deltaTime);

		// Swap the screen buffers (Double buffers)
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

void initGame() {
	camera = new Camera(ORTHOGONAL);
	gameTime = new Time;
	input = new Input;
	player = new Player(new GDShape("GeometryData/Plane.gd"), camera, input);
	player->position = vec3(0, -9, 0);
	bg = new Background(camera);
}

void endGame(bool gameOver, bool gameClear) {
	printGameData(gameOver, gameClear);
	destroy();
	glfwSetWindowShouldClose(window, GL_TRUE);
}


void printGameData(bool gameOver, bool gameClear) {
	if(gameClear)
		std::cout << ">>>>>>>>>>GAME CLEAR<<<<<<<<<<" << std::endl;

	if (gameOver) 
		std::cout << ">>>>>>>>>>GAME OVER<<<<<<<<<<" << std::endl;
	else
		std::cout << "Player Health: " << player->GetHealth() << std::endl;

	std::cout << "Killed Enemy: " << EnemyManager::GetInstance()->GetKilledEnemyCount() << std::endl;
	std::cout << "Player Level: " << player->GetLevel() << std::endl;
	std::cout << "Player Fire Number: " << player->GetTotalFireCount() << std::endl;
	vec3 hms = GetTimeHMS(gameTime->GetTime());
	std::cout << "Game Time: " << hms.x << ":" << hms.y << ":" << hms.z << std::endl;
}


vec3 GetTimeHMS(float time) {
	vec3 hms = vec3(0.0f);
	float sec = (int)time % 60 + (time - (int)time);
	float min = (int)time / 60;
	float hr = (int)time / 3600;
	if (min > 60) min =(int)min % 60;
	return vec3(hr, min, sec);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		printGameData(false, false);
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
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
	int max_width = GetSystemMetrics(SM_CXSCREEN);
	int max_hieght = GetSystemMetrics(SM_CYSCREEN);
	glfwSetWindowMonitor(window, NULL, (max_width / 2) - (WIDTH / 2), (max_hieght / 2) - (HEIGHT / 2), WIDTH, HEIGHT, GLFW_DONT_CARE);
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


void destroy() {
	EnemyManager::GetInstance()->Destroy();
	BulletManager::GetInstance()->Destroy();
	delete bg;
	delete player;
	delete input;
	delete gameTime;
	delete camera;
}