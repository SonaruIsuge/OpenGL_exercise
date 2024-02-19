#pragma once
#include "../../Components/ShootingPart.h"
#include "../Character.h"



class Enemy : public Character {
protected:
	Object* target;
	bool active;

	void UpdateShooting(float deltaTime);
	void UpdateMove(float deltaTime);
	
public:
	ShootingPart* shootingPart;

	Enemy(Shape* shape, Camera* camera, Object* fireTarget);
	~Enemy();

	void Init(vec3 position);
	void Update(float deltaTime);
	void Dead();
	void SetActive(bool active);
	bool IsActive();
};