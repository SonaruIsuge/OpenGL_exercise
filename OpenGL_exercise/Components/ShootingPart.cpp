#include "ShootingPart.h"
#include "../Shapes/GDShape.h"
#include "../Systems/BulletManager.h"

ShootingPart::ShootingPart(BulletType bulletType, float coolDownTime) : bulletType(bulletType), coolDownTime(coolDownTime) {
	coolDownTimer = 0;
	isShoot = false;
	isActive = true;
}


ShootingPart::~ShootingPart() {

}


void ShootingPart::Fire(Camp camp, vec3 position, vec3 direction, float speed, int damage) {
	if (isShoot) return;

	Bullet* bullet = BulletManager::GetInstance()->RequestBullet(PlayerBullet);
	if (bullet == nullptr) return;

	bullet->SetCamp(camp);
	bullet->Fire(damage, position, direction, speed);

	isShoot = true;
}


void ShootingPart::Fire(Object& target, Camp camp, vec3 position, float speed, int damage) {
	if (isShoot) return;
	Bullet* bullet = BulletManager::GetInstance()->RequestBullet(bulletType);
	if (bullet == nullptr) return;

	bullet->SetCamp(camp);
	vec3 direction = normalize(target.position - position);
	bullet->Fire(damage, position, direction, speed);

	isShoot = true;
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


void ShootingPart::HandleCollide() {

}