#pragma once

#include "Object.h"


enum Camp {
	PLAYER,
	ENEMY,
	OTHER
};


class Character: public Object {
protected:
	Camp camp;

	int health;
	int attack;

	int remainHealth;
	bool beHit;

public:

	Character(Shape* shape, Camera* camera);
	~Character();

	void SetInitialData(int health, int attack);
	void Update(float deltaTime);
	void GetDamage(int damage);

	int GetHealth();
	int GetAttackValue();
};