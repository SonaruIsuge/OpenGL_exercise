#pragma once
#include "../GameObjects/Player.h"


class LevelManager {
private:
	Player& playerRef;
	Camera& cameraRef;

	int currentWave;
	float coolDownTimer;
	int generateEnemyCount;

	void ChangeWave(int wave);
	void wave1(float dt, int enemyNum, float enemyInitCoolDown);
	void wave2(float dt, int enemyNum, float enemyInitCoolDown);
	void wave3(float dt, int enemyNum, float enemyInitCoolDown);

public:

	LevelManager(Player& player, Camera& camera);
	~LevelManager();

	void Init();
	void Update(float deltaTime);
};