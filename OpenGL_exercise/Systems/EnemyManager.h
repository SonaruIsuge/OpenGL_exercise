#pragma once
#include <map>
#include "../Tools/ObjectPool.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Enemy/Enemy.h"


class EnemyManager {
private:
	static EnemyManager* _instance;

	Player* player;

	std::map<EnemyType, std::unique_ptr<ObjectPool<Enemy>>> allTypeEnemies;
	
public:

	static EnemyManager* GetInstance();
	
	std::vector<Enemy*> activeEnemyList;

	EnemyManager();
	~EnemyManager();

	void SetPlayerRef(Player& player);
	void AddEnemyTypeToPool(EnemyType type, Enemy& prototype, int numInPool);
	Enemy* RequestEnemy(EnemyType type);
	void Update(float deltaTime);
	void Destroy();
};