#include "BulletManager.h"
#include "EnemyManager.h"
#include "../GameObjects/Enemy/NormalEnemy.h"
#include "../GameObjects/Enemy/StrongEnemy.h"
#include "../Shapes/GDShape.h"
#include "../Tools/Random.h"
#include "LevelManager.h"


void wave1(float dt, int enemyNum, float enemyInitCoolDown);

LevelManager::LevelManager(Player& player, Camera& camera) : playerRef(player), cameraRef(camera) {
	
}


LevelManager::~LevelManager() {

}


void LevelManager::Init() {
	BulletManager::GetInstance()->SetPlayerRef(playerRef);
	EnemyManager::GetInstance()->SetPlayerRef(playerRef);

	Bullet arrowBullet(new GDShape("GeometryData/Arrow.gd"), &cameraRef);
	arrowBullet.SetColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Bullet thornBullet(new GDShape("GeometryData/Thorn.gd"), &cameraRef);
	thornBullet.SetColor(vec4(1.0f, 0.9f, 0.2f, 1.0f));
	Bullet circleBullet(new GDShape("GeometryData/Circle.gd"), &cameraRef);
	circleBullet.SetColor(vec4(1.0f, 0.9f, 0.2f, 1.0f));
	Bullet shurikenBullet(new GDShape("GeometryData/Shuriken.gd"), &cameraRef);
	shurikenBullet.SetColor(vec4(1.0f, 0.9f, 0.2f, 1.0f));
	
	BulletManager::GetInstance()->AddBulletTypeToPool(ArrowBullet, arrowBullet, 100);
	BulletManager::GetInstance()->AddBulletTypeToPool(ThornBullet, thornBullet, 1000);
	BulletManager::GetInstance()->AddBulletTypeToPool(CircleBullet, circleBullet, 300);
	BulletManager::GetInstance()->AddBulletTypeToPool(ShurikenBullet, shurikenBullet, 300);

	NormalEnemy enemy(new GDShape("GeometryData/Rhombic.gd"), &cameraRef, &playerRef);
	StrongEnemy strongEnemy(new GDShape("GeometryData/Rhombic.gd"), &cameraRef, &playerRef);
	EnemyManager::GetInstance()->AddEnemyTypeToPool<NormalEnemy>(Normal, enemy, 20);
	EnemyManager::GetInstance()->AddEnemyTypeToPool<StrongEnemy>(Strong, strongEnemy, 20);
}


void LevelManager::Update(float deltaTime) {
	
	wave1(deltaTime, 20, 1.5f);
}


float coolDownTimer = 0.0f;
int initEnemyCount = 0;
void wave1(float dt, int enemyNum, float enemyInitCoolDown) {
	if (initEnemyCount == enemyNum)
		return;
	Random random;
	coolDownTimer += dt;
	if (coolDownTimer >= enemyInitCoolDown) {
		Enemy* newEnemy = EnemyManager::GetInstance()->RequestEnemy(Strong);
		newEnemy->Instantiate(vec3(random.randFloat(-5.0f, 5.0f), 11, 0));
		initEnemyCount++;
		coolDownTimer -= enemyInitCoolDown;
	}
}


void wave2(float dt, int enemyNum, float enemyInitCoolDown) {

}