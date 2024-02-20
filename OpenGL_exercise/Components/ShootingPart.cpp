#include "ShootingPart.h"
#include "../Shapes/GDShape.h"
#include "../Systems/BulletManager.h"
#include "../math.h"

ShootingPart::ShootingPart(BulletType bulletType, float coolDownTime) : bulletType(bulletType), coolDownTime(coolDownTime) {
	coolDownTimer = 0;
	isShoot = false;
	isActive = true;

	newRecycleTime = 0.0f;
	changeRecycleTime = false;
}


ShootingPart::~ShootingPart() {

}


void ShootingPart::Fire(Camp camp, vec3 position, vec3 direction, float speed, int damage) {
	if (isShoot) return;

	Bullet* bullet = BulletManager::GetInstance()->RequestBullet(bulletType);
	if (bullet == nullptr) return;

	float angle = gameMath::angleWithSign(vec3(0, 1, 0), direction);
	bullet->rotation = vec3(0, 0, degrees(angle));

	bullet->SetCamp(camp);

	if (changeRecycleTime) {
		bullet->SetRecycleTime(newRecycleTime);
		changeRecycleTime = false;
	}

	bullet->Fire(damage, position, direction, speed);

	isShoot = true;
}


void ShootingPart::Fire(Object& target, Camp camp, vec3 position, float speed, int damage) {
	vec3 direction = normalize(target.position - position);
	Fire(camp, position, direction, speed, damage);
}


void ShootingPart::Update(float deltaTime) {
	if (!isActive) return;

	if (isShoot) {
		coolDownTimer += deltaTime;
		
		if (coolDownTimer >= coolDownTime) {
			isShoot = false;
			coolDownTimer = 0.0f;
		}
	}
}


void ShootingPart::SetBulletRecycleTime(float recycleTime) {
	newRecycleTime = recycleTime;
	changeRecycleTime = true;
}