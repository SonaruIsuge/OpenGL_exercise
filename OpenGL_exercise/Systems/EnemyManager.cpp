#include "EnemyManager.h"
#include "LevelManager.h"

EnemyManager* EnemyManager::_instance = nullptr;


EnemyManager* EnemyManager::GetInstance() {
	if (_instance == nullptr)
		_instance = new EnemyManager();

	return _instance;
}


EnemyManager::EnemyManager() {
	player = nullptr;
	deadEnemyCount = 0;
}


EnemyManager::~EnemyManager() {

}


void EnemyManager::SetPlayerRef(Player& player) {
	this->player = &player;
}


void EnemyManager::AddEnemyTypeToPool(EnemyType type, Enemy& prototype, int numInPool) {
	if (player == nullptr) {
		std::cout << "ERROR::NEED SET PLAYER TO ENEMY MANAGER" << std::endl;
		return;
	}

	// Chekc if key already exists
	if (allTypeEnemies.find(type) != allTypeEnemies.end())
		return;

	allTypeEnemies[type] = std::make_unique<ObjectPool<Enemy>>();
	for (int i = 0; i < numInPool; i++) {
		
		Enemy* newEnemy = new Enemy(new Shape(*prototype.shape), prototype.camera, this->player);
		
		allTypeEnemies[type]->AddNode(newEnemy);
	}
}


Enemy* EnemyManager::RequestEnemy(EnemyType type) {
	if (allTypeEnemies.find(type) == allTypeEnemies.end())
		return nullptr;

	Node<Enemy>* node = allTypeEnemies[type]->GetNode();
	if (node == nullptr) return nullptr;

	return node->data;
}


void EnemyManager::Update(float deltaTime) {
	activeEnemyList.clear();
	Node<Enemy>* currentNode = nullptr;

	for (auto& pool : allTypeEnemies) {
		currentNode = pool.second->using_first;
		while (currentNode != nullptr) {

			// handle inactive bullet;
			if (currentNode->data->IsDead()) {
				currentNode->data->SetActive(false);
				// Count dead enemy number
				deadEnemyCount++;
				player->KillEnemy();
			}
			if (!currentNode->data->IsActive()) {
				pool.second->Recycle(currentNode);
			}

			activeEnemyList.push_back(currentNode->data);
			currentNode->data->Update(deltaTime);
			currentNode = currentNode->next;
		}
	}
}


void EnemyManager::Destroy() {
	if (_instance != nullptr) delete _instance;
}


int EnemyManager::GetKilledEnemyCount() {
	return deadEnemyCount;
}