#pragma once
#include <glm/glm.hpp>

// Window dimensions
const int WIDTH = 720, HEIGHT = 720;
const float VIEWPORT_HALF_WIDTH = 10.0f;
const float VIEWPORT_HALF_HEIGHT = 10.0f;

// Bullet
const float RECYCLE_TIME = 5.0f;

// Player
const float PLAYER_MOVESPEED = 8.0f;
const int PLAYER_HEALTH = 100;
const int PLAYER_ATTACK = 10;
const float PLAYER_SHOOTING_COOLDOWN = 0.1f;
const float PLAYER_BULLET_SPEED = 10.0f;
const glm::vec4 PLAYER_COLOR = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

// Enemy
const float NORMAL_E_MOVESPEED = 4.0f;
const int NORMAL_E_HEALTH = 50;
const int NORMAL_E_DAMAGE = 2;
const float NORMAL_E_BULLET_COOLDOWN = 1.5f;
const float NORMAL_E_BULLET_SPEED = 8.0f;
const glm::vec4 NORMAL_E_COLOR = glm::vec4(0.4f, 0.8f, 0.3f, 1.0f);

const float STRONG_E_MOVESPEED = 1.0f;
const int STRONG_E_HEALTH = 150;
const int STRONG_E_DAMAGE = 2;
const float STRONG_E_BULLET_COOLDOWN = 2.0f;
const float STRONG_E_BULLET_SPEED = 12.0f;
const glm::vec4 STRONG_E_COLOR = glm::vec4(0.4f, 0.6f, 0.9f, 1.0f);

const float EXPERT_E_MOVESPEED = 1.0f;
const int EXPERT_E_HEALTH = 400;
const int EXPERT_E_DAMAGE = 2;
const float EXPERT_E_BULLET_COOLDOWN = 6.0f;
const float EXPERT_E_BULLET_SHORT_COOLDOWN = 0.5f;
const int EXPERT_E_BULLET_WAVE_PER_COOLDOWN = 3;
const float EXPERT_E_BULLET_SPEED = 2.5f;
const glm::vec4 EXPERT_E_COLOR = glm::vec4(0.8f, 0.4f, 0.9f, 1.0f);

// Boss
const float BOSS_MOVESPEED = 4.0f;
const int BOSS_HEALTH = 3000;
const int BOSS_DAMAGE = 2;
const int BOSS_SHOOTINGPART = 28;
const float BOSS_BULLET_COOLDOWN = 0.2f;
const float BOSS_BULLET_SPEED = 2.0f;
const glm::vec4 BOSS_COLOR = glm::vec4(1.0f, 0.3f, 0.1f, 1.0f);

// Boss State
const float BOSS_NORMAL_STATE_ROTATE = 3.0f;
const float BOSS_NORMAL_STATE_BULLET_COOLDOWN = 0.2f;

const float BOSS_ADVANCE_STATE_MOVE = 5.0f;
const float BOSS_ADVANCE_STATE_ROTATE = 2.0f;
const float BOSS_ADVANCE_STATE_BULLET_COOLDOWN = 0.5f;
const float BOSS_ADVANCE_STATE_BULLET_SHORT_COOLDOWN = 0.02f;
const float BOSS_ADVANCE_BULLET_COUNT_PER_WAVE = 200;

const float BOSS_LAST_STATE_MOVE_TIME = 1.5f;
const float BOSS_LAST_STATE_MOVE_SPEED = 3.0f;
const float BOSS_LAST_STATE_ROTATE = 1.2f;
const float BOSS_LAST_STATE_BULLET_SPEED = 6.0f;
const float BOSS_LAST_STATE_BULLET_COOLDOWN = 0.5f;
const float BOSS_SUB_BULLET_COOLDOWN = 1.0f;
const float BOSS_SUB_SHOOT_PART_MOVE_SPEED = 4.0f;
const float BOSS_SUB_BULLET_SPEED = 6.0f;
