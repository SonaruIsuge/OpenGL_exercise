#pragma once
#include "Component.h"
#include"../Tools/GameEnum.h"
#include "../GameObjects/Object.h"


class ShootingPart : public Component {
private:
	BulletType bulletType;
	float coolDownTime;
	bool isShoot;

	float newRecycleTime;
	bool changeRecycleTime;

public:
	float coolDownTimer;

	ShootingPart(BulletType bulletType, float coolDownTime);
	~ShootingPart();

	void Fire(Camp camp, vec3 position, vec3 direction, float speed, int damage);
	void Fire(Object& target, Camp camp, vec3 position, float speed, int damage);
	void Update(float deltaTime);
	void SetBulletRecycleTime(float recycleTime);
};