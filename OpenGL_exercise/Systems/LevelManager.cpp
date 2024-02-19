#include "BulletManager.h"
#include "EnemyManager.h"
#include "../Shapes/GDShape.h"
#include "LevelManager.h"


void wave1(float dt, int enemyNum, float enemyInitCoolDown);

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

	
}


void LevelManager::Update(float deltaTime) {
	wave1(deltaTime, 10, 2.0f);
}

float coolDownTimer = 0.0f;
int initEnemyCount = 0;
void wave1(float dt, int enemyNum, float enemyInitCoolDown) {
	if (initEnemyCount == enemyNum)
		return;

	coolDownTimer += dt;
	if (coolDownTimer >= enemyInitCoolDown) {
		Enemy* newEnemy = EnemyManager::GetInstance()->RequestEnemy(NormalEnemy);
		newEnemy->Init(vec3(0, 11, 0));
		initEnemyCount++;
		coolDownTimer -= enemyInitCoolDown;
	}
}