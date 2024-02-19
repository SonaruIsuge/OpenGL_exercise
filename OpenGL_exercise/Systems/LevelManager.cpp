#include "BulletManager.h"
#include "EnemyManager.h"
#include "../Shapes/GDShape.h"
#include "LevelManager.h"


LevelManager::LevelManager(Player& player, Camera& camera) : playerRef(player), cameraRef(camera) {

}


LevelManager::~LevelManager() {

}


void LevelManager::Init() {
	BulletManager::GetInstance()->SetPlayerRef(playerRef);
	EnemyManager::GetInstance()->SetPlayerRef(playerRef);

	Bullet playerBullet(new GDShape("GeometryData/BulletA.gd"), &cameraRef);
	Bullet enemyBullet(new GDShape("GeometryData/Circle.gd"), &cameraRef);
	BulletManager::GetInstance()->AddBulletTypeToPool(PlayerBullet, playerBullet, 100);
	BulletManager::GetInstance()->AddBulletTypeToPool(EnemyBullet, enemyBullet, 300);

	Enemy enemy(new GDShape("GeometryData/NormalEnemyShape.gd"), &cameraRef, &playerRef);
	EnemyManager::GetInstance()->AddEnemyTypeToPool(NormalEnemy, enemy, 10);

	Enemy* newEnemy = EnemyManager::GetInstance()->RequestEnemy(NormalEnemy);
	newEnemy->Init(vec3(0, 5, 0));
}


void LevelManager::Update(float deltaTime) {

}