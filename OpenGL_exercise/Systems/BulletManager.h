#pragma once
#include <map>
#include "../Tools/ObjectPool.h"
#include "../GameObjects/Bullet.h"


enum BulletType {
	PlayerBullet,
	EnemyBullet,
	BossBullet,
};

class BulletManager {
private:
	static BulletManager* _instance;

	std::map<BulletType, ObjectPool<Bullet>*> allTypeBullets;

	void CheckCollide();

public:
	static BulletManager* GetInstance();

	BulletManager();
	~BulletManager();

	void AddBulletTypeToPool(BulletType type, const Bullet& prototype, int numInPool);
	Bullet* RequestBullet(BulletType type);
	void Update(float deltaTime);
	void Destroy();
};