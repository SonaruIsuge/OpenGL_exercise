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
const glm::vec4 NORMAL_E_COLOR = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

const float STRONG_E_MOVESPEED = 1.0f;
const int STRONG_E_HEALTH = 100;
const int STRONG_E_DAMAGE = 2;
const float STRONG_E_BULLET_COOLDOWN = 2.0f;
const float STRONG_E_BULLET_SPEED = 12.0f;
const glm::vec4 STRONG_E_COLOR = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
