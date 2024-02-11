#pragma once

#include <glm/glm.hpp>

using namespace glm;

class Input {
private:
	bool keys[512];
	vec2 mousePos;
	vec2 mouseOffset;
	vec2 scrollOffset;

	vec2 lastMousePos;
	bool firstMouseUpdate;

public:
	Input();
	~Input();
	
	//void Update();
	void OnMouseMove(double xPos, double yPos);
	void OnScrollMove(double xPos, double yPos);
	void OnKeyPress(int key, int action);

	vec2 GetMousePos();
	vec2 GetMouseOffset();
	vec2 GetScrollOffset();
	bool IsKeyPress(int key);

};