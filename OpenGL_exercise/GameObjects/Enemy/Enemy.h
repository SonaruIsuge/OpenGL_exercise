#pragma once
#include "../../Components/ShootingPart.h"
#include "../Character.h"



class Enemy : public Character {
private:

protected:
	Object* target;
	bool active;
	vec3 recordInitPos;

	virtual void UpdateShooting(float deltaTime) { };
	virtual void UpdateMove(float deltaTime) { };
	
public:

	Enemy(Shape* shape, Camera* camera, Object* fireTarget);
	virtual ~Enemy();

	virtual void Init() { };
	void Update(float deltaTime);
	void Instantiate(vec3 position);
	void SetActive(bool active);
	bool IsActive();
};