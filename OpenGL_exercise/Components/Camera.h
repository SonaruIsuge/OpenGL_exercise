#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

const vec3 WORLD_UP = vec3(0.0f, 1.0f, 0.0f);

const float DEFAULT_YAW = -90.0f;
const float DEFAULT_PITCH = 0.0f;
const float DEFAULT_FOV = 45.0f;

const float MIN_FOV_ANGLE = 1.0f;
const float MAX_FOV_ANGLE = 45.0f;
const bool CONSTRAIN_CAMERA_ANGLE = true;
const float CAMERA_MIN_ANGLE = -89.0f;
const float CAMERA_MAX_ANGLE = 89.0f;

const float MOVESPEED = 2.0f;
const float ROTATESPEED = 0.05f;
const float SCALESPEED = 1.0f;


enum MoveDir {
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

class Camera {
private:
	float moveSpeed;
	float rotateSpeed;
	float scaleSpeed;

	void updateCameraVectors();

public:
	vec3 position;
	vec3 front;
	vec3 up;
	vec3 right;
	float camYaw;
	float camPitch;
	float FOV;

	Camera(vec3 position, float yaw = DEFAULT_YAW, float pitch = DEFAULT_PITCH);
	virtual ~Camera();

	mat4 GetViewMatrix();
	void MoveCamera(MoveDir direction, float deltaTime);
	void RotateCamera(float xOffset, float yOffset, float deltaTime);
	void ChangeCameraFOV(float angleOffset);
};