#pragma once
#include "Component.h"
#include "../GameObjects/Object.h"
#include "../GameObjects/Bullet.h"
#include "../Tools/ObjectPool.h"

const int BULLET_IN_POOL = 400;

class ShootingPart : public Component {
private:
	Object* owner;
	float coolDownTime;
	bool isShoot;
	Bullet* prototype;
	ObjectPool<Bullet> bulletPool;

public:
	float coolDownTimer;

	ShootingPart(Bullet* prototype, Object* owner, float coolDownTime);
	~ShootingPart();

	void Fire(Camp camp, vec3 direction, float speed, int damage);
	void Update(float deltaTime);
};