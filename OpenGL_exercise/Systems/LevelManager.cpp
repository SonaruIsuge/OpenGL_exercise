#include "BulletManager.h"
#include "EnemyManager.h"
#include "../GameObjects/Enemy/NormalEnemy.h"
#include "../GameObjects/Enemy/StrongEnemy.h"
#include "../GameObjects/Enemy/ExpertEnemy.h"
#include "../GameObjects/Enemy/Boss.h"
#include "../Shapes/GDShape.h"
#include "../Tools/Random.h"
#include "LevelManager.h"

bool LevelManager::GAME_OVER = false;
Random random;
bool generateBoss = false;

LevelManager::LevelManager(Player& player, Camera& camera) : playerRef(player), cameraRef(camera) {
	currentWave = 0;
	coolDownTimer = 0.0f;
	generateEnemyCount = 0;
	boss = nullptr;
}


LevelManager::~LevelManager() {
	if (boss != nullptr) delete boss;
}


void LevelManager::Init() {
	BulletManager::GetInstance()->SetPlayerRef(playerRef);
	EnemyManager::GetInstance()->SetPlayerRef(playerRef);

	Bullet arrowBullet(new GDShape("GeometryData/Arrow.gd"), &cameraRef);
	arrowBullet.SetColor(vec4(0.6f, 1.0f, 1.0f, 1.0f));
	Bullet thornBullet(new GDShape("GeometryData/Thorn.gd"), &cameraRef);
	thornBullet.SetColor(vec4(1.0f, 0.9f, 0.2f, 1.0f));
	Bullet circleBullet(new GDShape("GeometryData/Circle.gd"), &cameraRef);
	circleBullet.SetColor(vec4(1.0f, 0.9f, 0.2f, 1.0f));
	Bullet shurikenBullet(new GDShape("GeometryData/Shuriken.gd"), &cameraRef);
	shurikenBullet.SetColor(vec4(1.0f, 0.9f, 0.2f, 1.0f));
	Bullet needleBullet(new GDShape("GeometryData/Needle.gd"), &cameraRef);
	needleBullet.SetColor(vec4(1.0f, 0.9f, 0.2f, 1.0f));
	
	BulletManager::GetInstance()->AddBulletTypeToPool(ArrowBullet, arrowBullet, 300);
	BulletManager::GetInstance()->AddBulletTypeToPool(ThornBullet, thornBullet, 600);
	BulletManager::GetInstance()->AddBulletTypeToPool(CircleBullet, circleBullet, 300);
	BulletManager::GetInstance()->AddBulletTypeToPool(ShurikenBullet, shurikenBullet, 1200);
	BulletManager::GetInstance()->AddBulletTypeToPool(NeedleBullet, needleBullet, 600);

	NormalEnemy enemy(new GDShape("GeometryData/Rhombic.gd"), &cameraRef, &playerRef);
	StrongEnemy strongEnemy(new GDShape("GeometryData/Rhombic.gd"), &cameraRef, &playerRef);
	ExpertEnemy expertEnemy(new GDShape("GeometryData/Rhombic.gd"), &cameraRef, &playerRef);
	Boss boss(new GDShape("GeometryData/Boss.gd"), &cameraRef, &playerRef);
	EnemyManager::GetInstance()->AddEnemyTypeToPool<NormalEnemy>(Normal, enemy, 20);
	EnemyManager::GetInstance()->AddEnemyTypeToPool<StrongEnemy>(Strong, strongEnemy, 20);
	EnemyManager::GetInstance()->AddEnemyTypeToPool<ExpertEnemy>(Expert, expertEnemy, 10);
	EnemyManager::GetInstance()->AddEnemyTypeToPool<Boss>(BossEnemy, boss, 1);
}


void LevelManager::Update(float deltaTime) {
	
	if (playerRef.IsDead()) {
		GAME_OVER = true;
		return;
	}
	
	switch (currentWave) {
	case 0:
		prepareTime(deltaTime, 3.0f);
		break;
	case 1:
		wave1(deltaTime, 30, 1.2f);
		break;
	case 2:
		wave2(deltaTime, 15, 2.0f);
		break;
	case 3:
		wave3(deltaTime, 8, 4.0f);
		break;
	case 4:
		BossFight(deltaTime, 2.0f);
		break;
	}
	
}


void LevelManager::ChangeWave(int wave) {
	this->currentWave = wave;
	generateEnemyCount = 0;
	coolDownTimer = 0;
}


void LevelManager::prepareTime(float dt, float time) {
	if (coolDownTimer >= time) {
		ChangeWave(1);
		return;
	}

	coolDownTimer += dt;
}


void LevelManager::wave1(float dt, int enemyNum, float enemyInitCoolDown) {
	if (generateEnemyCount == enemyNum) {
		ChangeWave(2);
		return;
	}
	
	coolDownTimer += dt;
	if (coolDownTimer >= enemyInitCoolDown) {
		Enemy* newEnemy = EnemyManager::GetInstance()->RequestEnemy(Normal);
		newEnemy->Instantiate(vec3(random.randFloat(-8.0f, 8.0f), 10.0f, 0));
		generateEnemyCount++;
		coolDownTimer -= enemyInitCoolDown;
	}
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


void LevelManager::BossFight(float dt, float breakTime) {
	if (EnemyManager::GetInstance()->GetActiveEnemyCount() > 0)
		return;
	
	if (coolDownTimer < breakTime) {
		coolDownTimer += dt;
		return;
	}
	
	if (generateBoss) return;
	
	boss = EnemyManager::GetInstance()->RequestEnemy(BossEnemy);
	boss->Instantiate(vec3(0.0f, 10.0f, 0));
	generateBoss = true;
}


bool LevelManager::CheckGameClear() {
	return boss != nullptr && boss->IsDead();
}


int LevelManager::GetBossHealth() {
	if (boss == nullptr) return 0;
	return boss->GetHealth();
}