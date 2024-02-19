#pragma once

#include "Object.h"
#include "../Components/Collider.h"

class Character: public Object {
protected:
	Camp camp;

	int health;
	int attack;

	int remainHealth;
	bool beHit;


public:
	Collider* collider;

	Character(Shape* shape, Camera* camera);
	virtual ~Character();

	void SetInitialData(int health, int attack);
	void Update(float deltaTime);
	void GetDamage(int damage);

	int GetHealth();
	int GetAttackValue();
};