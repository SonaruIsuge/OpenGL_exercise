#pragma once
#include "Component.h"
#include "../GameObjects/Object.h"

class Collider : public Component {
private:
	vec3 center;
	float radius;
	Object* owner;

public:

	Collider(Object* owner, vec3 center, float radius);
	~Collider() override;

	void SetRadius(float radius);
	void Update(float deltaTime);
	bool IsCollide(const Collider* other);
};