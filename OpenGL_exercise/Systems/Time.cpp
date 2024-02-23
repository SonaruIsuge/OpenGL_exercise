#include <GLFW/glfw3.h>
#include "Time.h"


Time::Time() {
	currentTime = 0;
	lastTime = 0;
	deltaTime = 0;
}


Time::~Time() {

}


void Time::Update() {
	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}


float Time::GetTime() {
	return (float)glfwGetTime();
}