#pragma once
#include "../GameObjects/Player.h"


class LevelManager {
private:
	Player& playerRef;
	Camera& cameraRef;

public:

	LevelManager(Player& player, Camera& camera);
	~LevelManager();

	void Init();
	void Update(float deltaTime);
};