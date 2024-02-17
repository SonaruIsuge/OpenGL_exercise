#pragma once
#include "../Systems/Input.h"
#include "../Components/ShootingPart.h"
#include "Character.h"


const float MOVESPEED = 5.0f;
const int HEALTH = 100;
const int ATTACK = 10;
const float SHOOTING_COOLDOWN = 0.1f;
const float BULLET_SPEED = 10.0f;

class Player : public Character {
private:
	Input* input;
	ShootingPart* shootingPart;

	void HandleInput(float deltaTime);

public:


	Player(Shape* shape, Camera* camera, Input* input);
	~Player();

	void Update(float deltaTime);
};