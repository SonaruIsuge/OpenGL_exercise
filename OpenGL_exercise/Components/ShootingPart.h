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

	int totalFireCount;

public:
	float coolDownTimer;

	ShootingPart(BulletType bulletType, float coolDownTime);
	~ShootingPart();

	bool Fire(Camp camp, vec3 position, vec3 direction, float speed, int damage);
	bool Fire(Object& target, Camp camp, vec3 position, float speed, int damage);
	void Update(float deltaTime);
	void SetBulletRecycleTime(float recycleTime);
	void ChangeCoolDown(float coolDown);
	void ChangeBulletType(BulletType type);
	int GetTotalFireCount();
};