#include "../Shapes/GDShape.h"
#include "Player.h"
#include <GLFW/glfw3.h>
#include "../Tools/GameSettings.h"


Player::Player(Shape* shape, Camera* camera, Input* input) : Character(shape, camera), input(input) {
	camp = PLAYER;
	level = 1;
	killedEnemy = 0;

	SetInitialData(PLAYER_HEALTH, PLAYER_ATTACK);
	SetColor(PLAYER_COLOR);

	AddComponent<ShootingPart>(ArrowBullet, PLAYER_SHOOTING_COOLDOWN);
	shootingParts = GetComponents<ShootingPart>();
}


Player::~Player() {
	
}


void Player::Update(float deltaTime) {
	HandleInput(deltaTime);

	Character::Update(deltaTime);
}


void Player::KillEnemy() {
	killedEnemy++;

	switch (level) {
	case 1:
		if (killedEnemy >= 15)
			LevelUp();
		break;
	case 2:
		if (killedEnemy >= 32)
			LevelUp();
		break;
	default:
		break;
	}
}


void Player::HandleInput(float deltaTime) {

	if (this->input->IsKeyPress(GLFW_KEY_W))
		position += vec3(0.0f, 1.0f, 0.0f) * PLAYER_MOVESPEED * deltaTime;
	if (this->input->IsKeyPress(GLFW_KEY_S))
		position += vec3(0.0f, -1.0f, 0.0f) * PLAYER_MOVESPEED * deltaTime;
	if (this->input->IsKeyPress(GLFW_KEY_A))
		position += vec3(-1.0f, 0.0f, 0.0f) * PLAYER_MOVESPEED * deltaTime;
	if (this->input->IsKeyPress(GLFW_KEY_D))
		position += vec3(1.0f, 0.0f, 0.0f) * PLAYER_MOVESPEED * deltaTime;

	if (this->input->IsMouseClick(GLFW_MOUSE_BUTTON_1)) {
		Shooting();
	}
}


void Player::LevelUp() {
	level++;
	std::cout << "Level Up!" << std::endl;
	AddComponent<ShootingPart>(ArrowBullet, PLAYER_SHOOTING_COOLDOWN);
	shootingParts = GetComponents<ShootingPart>();
}


void Player::Shooting() {
	switch (level) {
	case 1:
		shootingParts[0]->Fire(this->camp, position + vec3(0, 0.5f, 0), vec3(0, 1, 0), PLAYER_BULLET_SPEED, PLAYER_ATTACK);
		break;
	case 2:
		shootingParts[0]->Fire(this->camp, position + vec3(0.15f, 0.5f, 0), vec3(0, 1, 0), PLAYER_BULLET_SPEED, PLAYER_ATTACK);
		shootingParts[1]->Fire(this->camp, position + vec3(-0.15f, 0.5f, 0), vec3(0, 1, 0), PLAYER_BULLET_SPEED, PLAYER_ATTACK);
		break;
	case 3:
		shootingParts[0]->Fire(this->camp, position + vec3(0.3f, 0.5f, 0), vec3(0, 1, 0), PLAYER_BULLET_SPEED, PLAYER_ATTACK);
		shootingParts[1]->Fire(this->camp, position + vec3(0.0f, 0.5f, 0), vec3(0, 1, 0), PLAYER_BULLET_SPEED, PLAYER_ATTACK);
		shootingParts[2]->Fire(this->camp, position + vec3(-0.3f, 0.5f, 0), vec3(0, 1, 0), PLAYER_BULLET_SPEED, PLAYER_ATTACK);
		break;
	}
}