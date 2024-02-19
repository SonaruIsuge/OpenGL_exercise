#include "../Shapes/GDShape.h"
#include "Player.h"
#include <GLFW/glfw3.h>




Player::Player(Shape* shape, Camera* camera, Input* input) : Character(shape, camera), input(input) {
	camp = PLAYER;

	SetInitialData(HEALTH, ATTACK);

	AddComponent<ShootingPart>(PlayerBullet, SHOOTING_COOLDOWN);
	shootingPart = GetComponent<ShootingPart>();
}


Player::~Player() {
	
}


void Player::Update(float deltaTime) {
	HandleInput(deltaTime);

	Character::Update(deltaTime);
}


void Player::HandleInput(float deltaTime) {

	if (this->input->IsKeyPress(GLFW_KEY_W))
		position += vec3(0.0f, 1.0f, 0.0f) * MOVESPEED * deltaTime;
	if (this->input->IsKeyPress(GLFW_KEY_S))
		position += vec3(0.0f, -1.0f, 0.0f) * MOVESPEED * deltaTime;
	if (this->input->IsKeyPress(GLFW_KEY_A))
		position += vec3(-1.0f, 0.0f, 0.0f) * MOVESPEED * deltaTime;
	if (this->input->IsKeyPress(GLFW_KEY_D))
		position += vec3(1.0f, 0.0f, 0.0f) * MOVESPEED * deltaTime;

	if (this->input->IsMouseClick(GLFW_MOUSE_BUTTON_1)) {
		shootingPart->Fire(this->camp, position + vec3(0, 0.5f, 0), vec3(0, 1, 0), 10, 1);
	}
}