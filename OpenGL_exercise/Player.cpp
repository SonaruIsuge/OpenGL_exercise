#include "Components/Input.h"
#include "Player.h"

#include <GLFW/glfw3.h>


Player::Player(Shape* shape, Camera* camera, Input* input) : Character(shape, camera), input(input) {
	
}


Player::~Player() {
	
}


void Player::Update(float deltaTime) {
	Character::Update(deltaTime);

	HandleMove(deltaTime);
}


void Player::HandleMove(float deltaTime) {

	if (this->input->IsKeyPress(GLFW_KEY_W))
		position += vec3(0.0f, 1.0f, 0.0f) * moveSpeed * deltaTime;
	if (this->input->IsKeyPress(GLFW_KEY_S))
		position += vec3(0.0f, -1.0f, 0.0f) * moveSpeed * deltaTime;
	if (this->input->IsKeyPress(GLFW_KEY_A))
		position += vec3(-1.0f, 0.0f, 0.0f) * moveSpeed * deltaTime;
	if (this->input->IsKeyPress(GLFW_KEY_D))
		position += vec3(1.0f, 0.0f, 0.0f) * moveSpeed * deltaTime;
}