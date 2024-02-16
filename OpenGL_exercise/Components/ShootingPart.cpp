#include "ShootingPart.h"
#include "../Shapes/GDShape.h"
#include "../Systems/ObjectInteractHandler.h"

ShootingPart::ShootingPart(Bullet* prototype, Object* owner, float coolDownTime) : prototype(prototype), owner(owner), coolDownTime(coolDownTime) {
	coolDownTimer = 0;
	isShoot = false;
	isActive = true;

	for (int i = 0; i < BULLET_IN_POOL; i++) {
		Bullet* newBullet = new Bullet(new Shape(*prototype->shape), owner->camera);
		bulletPool.AddNode(newBullet);
	}
}


ShootingPart::~ShootingPart() {

}


void ShootingPart::Fire(Camp camp, vec3 direction, float speed, int damage) {
	if (isShoot) return;

	Node<Bullet>* node = bulletPool.GetNode();
	if (node == nullptr) return;

	node->data->Fire(damage, this->owner->position, direction, speed);

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

	Node<Bullet>* node = bulletPool.using_first;
	while (node != nullptr) {
		node->data->Update(deltaTime);
		node = node->next;
	}
}