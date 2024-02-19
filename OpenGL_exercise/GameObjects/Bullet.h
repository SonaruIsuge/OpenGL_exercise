#pragma once
#include "Object.h"
#include "../Components/Collider.h"


class Bullet : public Object {
protected:
	int damage;
	float speed;
	vec3 direction;
	Camp camp;

	float recycleTimer;
	bool active;


public:
	Collider* collider;
	
	Bullet(Shape* shape, Camera* camera);
	~Bullet();

	void Update(float deltaTime);
	void Fire(int damage, vec3 position, vec3 direction, float speed);
	void Reset();
	void SetCamp(Camp camp);
	Camp GetCamp();
	int GetAttackValue();
	bool IsActive();
};