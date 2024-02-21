#include "BulletManager.h"
#include "EnemyManager.h"
#include "../GameObjects/Enemy/NormalEnemy.h"
#include "../GameObjects/Enemy/StrongEnemy.h"
#include "../GameObjects/Enemy/ExpertEnemy.h"
#include "../Shapes/GDShape.h"
#include "../Tools/Random.h"
#include "LevelManager.h"


Random random;

LevelManager::LevelManager(Player& player, Camera& camera) : playerRef(player), cameraRef(camera) {
	currentWave = 1;
	coolDownTimer = 0.0f;
	generateEnemyCount = 0;
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
	Bullet needleBullet(new GDShape("GeometryData/Needle.gd"), &cameraRef);
	needleBullet.SetColor(vec4(1.0f, 0.9f, 0.2f, 1.0f));
	
	BulletManager::GetInstance()->AddBulletTypeToPool(ArrowBullet, arrowBullet, 300);
	BulletManager::GetInstance()->AddBulletTypeToPool(ThornBullet, thornBullet, 1000);
	BulletManager::GetInstance()->AddBulletTypeToPool(CircleBullet, circleBullet, 300);
	BulletManager::GetInstance()->AddBulletTypeToPool(ShurikenBullet, shurikenBullet, 300);
	BulletManager::GetInstance()->AddBulletTypeToPool(NeedleBullet, needleBullet, 1000);

	NormalEnemy enemy(new GDShape("GeometryData/Rhombic.gd"), &cameraRef, &playerRef);
	StrongEnemy strongEnemy(new GDShape("GeometryData/Rhombic.gd"), &cameraRef, &playerRef);
	ExpertEnemy expertEnemy(new GDShape("GeometryData/Rhombic.gd"), &cameraRef, &playerRef);
	EnemyManager::GetInstance()->AddEnemyTypeToPool<NormalEnemy>(Normal, enemy, 20);
	EnemyManager::GetInstance()->AddEnemyTypeToPool<StrongEnemy>(Strong, strongEnemy, 20);
	EnemyManager::GetInstance()->AddEnemyTypeToPool<ExpertEnemy>(Expert, expertEnemy, 10);
}


void LevelManager::Update(float deltaTime) {
	switch (currentWave) {
	case 1:
		wave1(deltaTime, 30, 1.2f);
		break;
	case 2:
		wave2(deltaTime, 15, 2.0f);
		break;
	case 3:
		wave3(deltaTime, 10, 4.0f);
		break;
	}
	
}



void LevelManager::wave1(float dt, int enemyNum, float enemyInitCoolDown) {
	if (generateEnemyCount == enemyNum) {
		ChangeWave(2);
		return;
	}
	
	coolDownTimer += dt;
	if (coolDownTimer >= enemyInitCoolDown) {
		Enemy* newEnemy = EnemyManager::GetInstance()->RequestEnemy(Normal);
		newEnemy->Instantiate(vec3(random.randFloat(-8.0f, 8.0f), 10.5f, 0));
		generateEnemyCount++;
		coolDownTimer -= enemyInitCoolDown;
	}
}


void LevelManager::ChangeWave(int wave) {
	this->currentWave = wave;
	generateEnemyCount = 0;
	coolDownTimer = 0;
}


void LevelManager::wave2(float dt, int enemyNum, float enemyInitCoolDown) {
	if (generateEnemyCount == enemyNum) {
		ChangeWave(3);
		return;
	}

	coolDownTimer += dt;
	if (coolDownTimer >= enemyInitCoolDown) {
		Enemy* newEnemy = EnemyManager::GetInstance()->RequestEnemy(Strong);
		newEnemy->Instantiate(vec3(random.randFloat(-5.0f, 5.0f), 10.5f, 0));
		generateEnemyCount++;
		coolDownTimer -= enemyInitCoolDown;
	}
}


void LevelManager::wave3(float dt, int enemyNum, float enemyInitCoolDown) {
	if (generateEnemyCount == enemyNum) {
		ChangeWave(4);
		return;
	}

	coolDownTimer += dt;
	if (coolDownTimer >= enemyInitCoolDown) {
		Enemy* newEnemy = EnemyManager::GetInstance()->RequestEnemy(Expert);
		newEnemy->Instantiate(vec3(8.0f, 10.0f, 0));
		newEnemy = EnemyManager::GetInstance()->RequestEnemy(Expert);
		newEnemy->Instantiate(vec3(-8.0f, 10.0f, 0));
		generateEnemyCount+=2;
		coolDownTimer -= enemyInitCoolDown;
	}
}