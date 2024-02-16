#pragma once
#include "../GameObjects/Player.h"
#include "../GameObjects/Bullet.h"


class ObjectInteractHandler {
private:
	static ObjectInteractHandler* _instance;


	void HandleCollide();

public:
	static ObjectInteractHandler* GetInstance();

	ObjectInteractHandler();
	virtual ~ObjectInteractHandler();

	void Update(float deltaTime);
};