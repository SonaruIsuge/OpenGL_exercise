#pragma once
#include "../GameObjects/Player.h"


class LevelManager {
private:
	Player& playerRef;
	Camera& cameraRef;

	int currentWave;
	float coolDownTimer;
	int generateEnemyCount;

	Enemy* boss;

	void ChangeWave(int wave);
	void prepareTime(float dt, float time);
	void wave1(float dt, int enemyNum, float enemyInitCoolDown);
	void wave2(float dt, int enemyNum, float enemyInitCoolDown);
	void wave3(float dt, int enemyNum, float enemyInitCoolDown);
	void BossFight(float dt, float breakTime);

public:
	static bool GAME_OVER;
	LevelManager(Player& player, Camera& camera);
	~LevelManager();

	void Init();
	void Update(float deltaTime);
	bool CheckGameClear();
	int GetBossHealth();
};