#include "../Shapes/GDShape.h"
#include "Player.h"
#include <GLFW/glfw3.h>
#include "../Tools/GameSettings.h"


Player::Player(Shape* shape, Camera* camera, Input* input) : Character(shape, camera), input(input) {
	camp = PLAYER;
	level = 1;
	killedEnemy = 0;
	changeDamagedColor = false;
	colorChangeTimer = 0.0f;

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
	
	// Change color when be hit
	if (changeDamagedColor) {
		SetColor(PLAYER_GET_DAMAGE_COLOR);
		colorChangeTimer += deltaTime;
		
		if (colorChangeTimer > 0.1f) {
			SetColor(PLAYER_COLOR);
			changeDamagedColor = false;
			colorChangeTimer = 0;
		}
	}
}


void Player::KillEnemy() {
	killedEnemy++;

	switch (level) {
	case 1:
		if (killedEnemy >= 20)
			LevelUp();
		break;
	case 2:
		if (killedEnemy >= 42)
			LevelUp();
		break;
	default:
		break;
	}
}


int Player::GetLevel() {
	return level;
}


int Player::GetTotalFireCount() {
	int result = 0;
	for (auto& shootingPart : shootingParts) {
		result += shootingPart->GetTotalFireCount();
	}
	return result;
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
	position.x = clamp(position.x, -VIEWPORT_HALF_WIDTH, VIEWPORT_HALF_WIDTH);
	position.y = clamp(position.y, -VIEWPORT_HALF_HEIGHT, VIEWPORT_HALF_HEIGHT);
	if (this->input->IsMouseClick(GLFW_MOUSE_BUTTON_1)) {
		Shooting();
	}
}


void Player::LevelUp() {
	level++;
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


void Player::BeDamaged(int damage) {
	Character::BeDamaged(damage);

	changeDamagedColor = true;
	colorChangeTimer = 0;
}