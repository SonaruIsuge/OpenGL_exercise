#pragma once
#include <map>
#include "../Tools/ObjectPool.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Bullet.h"


class BulletManager {
private:
	static BulletManager* _instance;

	Player* player;

	std::map<BulletType, ObjectPool<Bullet>*> allTypeBullets;

	void CheckCollide(Bullet& bullet);

public:
	static BulletManager* GetInstance();

	BulletManager();
	~BulletManager();

	void SetPlayerRef(Player& player);
	void AddBulletTypeToPool(BulletType type, const Bullet& prototype, int numInPool);
	Bullet* RequestBullet(BulletType type);
	void Update(float deltaTime);
	void Destroy();
};