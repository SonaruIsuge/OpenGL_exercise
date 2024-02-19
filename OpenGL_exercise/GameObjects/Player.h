#pragma once
#include "../Systems/Input.h"
#include "../Components/ShootingPart.h"
#include "Character.h"


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