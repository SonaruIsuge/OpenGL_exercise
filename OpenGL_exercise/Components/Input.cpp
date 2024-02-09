#include <GLFW/glfw3.h>
#include "Input.h"


Input::Input() {
	mousePos = vec2(0.0f);
	mouseOffset = vec2(0.0f);
	scrollOffset = vec2(0.0f);
	lastMousePos = vec2(0.0f);
	
	for (int i = 0; i < 512; ++i)
		keys[i] = false;

	firstMouseUpdate = true;
}


Input::~Input() {

}


void Input::OnKeyPress(int key, int action) {
	if (key >= 0 && key < 512) {
		if (action == GLFW_PRESS) 
			keys[key] = true;
		if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}


void Input::OnMouseMove(double xPos, double yPos) {
	if (firstMouseUpdate) {
		lastMousePos = vec2(xPos, yPos);
	}

	mouseOffset = vec2(xPos - lastMousePos.x, lastMousePos.y - yPos);
	lastMousePos = vec2(xPos, yPos);
}


void Input::OnScrollMove(double xOffset, double yOffset) {
	scrollOffset = vec2(xOffset, yOffset);
}


vec2 Input::GetMousePos() {
	return mousePos;
}


vec2 Input::GetMouseOffset() {
	return mouseOffset;
}


vec2 Input::GetScrollOffset() {
	return scrollOffset;
}


bool Input::IsKeyPress(int key) {
	if (key < 0 || key >= 512)
		return false;

	return keys[key];
}