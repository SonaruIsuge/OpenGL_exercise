#pragma once
#include "Character.h"


const float moveSpeed = 1.0f;

class Player : public Character {
private:
	Input* input;

	void HandleMove(float deltaTime);

public:


	Player(Shape* shape, Camera* camera, Input* input);
	~Player();

	void Update(float deltaTime);
};