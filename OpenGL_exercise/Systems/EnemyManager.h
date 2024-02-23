#pragma once
#include <map>
#include "../Tools/ObjectPool.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Enemy/Enemy.h"

template <typename T>
concept IsEnemy = std::is_base_of<Enemy, T>::value;


class EnemyManager {
private:
	static EnemyManager* _instance;

	Player* player;

	std::map<EnemyType, std::unique_ptr<ObjectPool<Enemy>>> allTypeEnemies;

	int activeEnemyCount;
	int deadEnemyCount;
	
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
	int GetKilledEnemyCount();
	int GetActiveEnemyCount();

	template<IsEnemy T>
	void AddEnemyTypeToPool(EnemyType type, T& prototype, int numInPool) {
		if (player == nullptr) {
			std::cout << "ERROR::NEED SET PLAYER TO ENEMY MANAGER" << std::endl;
			return;
		}

		// Chekc if key already exists
		if (allTypeEnemies.find(type) != allTypeEnemies.end())
			return;

		allTypeEnemies[type] = std::make_unique<ObjectPool<Enemy>>();
		for (int i = 0; i < numInPool; i++) {

			T* newEnemy = new T(new Shape(*prototype.shape), prototype.camera, this->player);
			
			allTypeEnemies[type]->AddNode(newEnemy);
		}
	}
};