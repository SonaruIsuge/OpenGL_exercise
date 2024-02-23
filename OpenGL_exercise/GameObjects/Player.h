#pragma once
#include "../Systems/Input.h"
#include "../Components/ShootingPart.h"
#include "Character.h"


class Player : public Character {
private:
	Input* input;
	std::vector<ShootingPart*> shootingParts;
	int killedEnemy;
	int level;

	bool changeDamagedColor;
	float colorChangeTimer;

	void HandleInput(float deltaTime);
	void LevelUp();
	void Shooting();

public:


	Player(Shape* shape, Camera* camera, Input* input);
	~Player();

	void Update(float deltaTime);
	void KillEnemy();

	int GetLevel();
	int GetTotalFireCount();
	void BeDamaged(int damage);
};