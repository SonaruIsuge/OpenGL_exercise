#include "BulletManager.h"


BulletManager* BulletManager::_instance = nullptr;


BulletManager* BulletManager::GetInstance() {
	if (_instance == nullptr)
		_instance = new BulletManager();

	return _instance;
}


BulletManager::BulletManager() {

}


BulletManager::~BulletManager() {

}


void BulletManager::AddBulletTypeToPool(BulletType type, const Bullet& prototype, int numInPool) {
	// Chekc if key already exists
	if (allTypeBullets.find(type) != allTypeBullets.end())
		return;

	allTypeBullets[type] = new ObjectPool<Bullet>;
	for (int i = 0; i < numInPool; i++) {
		Bullet* newBullet = new Bullet(new Shape(*prototype.shape), prototype.camera);
		allTypeBullets[type]->AddNode(newBullet);
	}
}


Bullet* BulletManager::RequestBullet(BulletType type) {
	if (allTypeBullets.find(type) == allTypeBullets.end())
		return nullptr;

	Node<Bullet>* node = allTypeBullets[type]->GetNode();
	if (node == nullptr) return nullptr;
	
	return node->data;
}


void BulletManager::Update(float deltaTime) {
	Node<Bullet>* currentNode = nullptr;

	for (auto& pool : allTypeBullets) {
		currentNode = pool.second->using_first;
		while (currentNode != nullptr) {

			// handle inactive bullet;
			if (!currentNode->data->IsActive()) {
				pool.second->Recycle(currentNode);
			}

			currentNode->data->Update(deltaTime);
			currentNode = currentNode->next;
		}
	}
}


void BulletManager::Destroy() {
	for (std::map<BulletType, ObjectPool<Bullet>*>::iterator itr = allTypeBullets.begin(); itr != allTypeBullets.end(); itr++)
	{
		delete (itr->second);
	}
	allTypeBullets.clear();

	if (_instance != nullptr) delete _instance;
}


void BulletManager::CheckCollide() {

}