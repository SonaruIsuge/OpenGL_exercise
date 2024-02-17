#pragma once
#include "Component.h"
#include "../GameObjects/Object.h"


class ShootingPart : public Component {
private:
	float coolDownTime;
	bool isShoot;

	void HandleCollide();

public:
	float coolDownTimer;

	ShootingPart(float coolDownTime);
	~ShootingPart();

	void Fire(Camp camp, vec3 position, vec3 direction, float speed, int damage);
	void Update(float deltaTime);
};