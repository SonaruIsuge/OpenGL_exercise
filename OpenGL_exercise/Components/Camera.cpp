
#include "Camera.h"


Camera::Camera(vec3 pos, float yaw, float pitch) : 
	front(vec3(0.0f, 0.0f, -1.0f)), moveSpeed(MOVESPEED), rotateSpeed(ROTATESPEED), scaleSpeed(SCALESPEED), FOV(DEFAULT_FOV) {

	this->position = pos;
	this->camYaw = yaw;
	this->camPitch = pitch;

	updateCameraVectors();
}


Camera::~Camera() {

}


mat4 Camera::GetViewMatrix() {
	return lookAt(this->position, this->position + this->front, this->up);
}


void Camera::MoveCamera(MoveDir direction, float deltaTime) {
	float velocity = moveSpeed * deltaTime;

	if (direction == FRONT) 
		position += normalize(front) * velocity;
	if (direction == BACK) 
		position -= normalize(front) * velocity;
	if (direction == LEFT) 
		position -= normalize(cross(front, up)) * velocity;
	if (direction == RIGHT) 
		position += normalize(cross(front, up)) * velocity;
}


void Camera::RotateCamera(float xOffset, float yOffset, float deltaTime) {
	camYaw += xOffset * rotateSpeed;
	camPitch += yOffset * rotateSpeed;
	
	if(CONSTRAIN_CAMERA_ANGLE)
		camPitch = clamp(camPitch, CAMERA_MIN_ANGLE, CAMERA_MAX_ANGLE);

	updateCameraVectors();
}


void Camera::ChangeCameraFOV(float angleOffset) {
	FOV = clamp(FOV - angleOffset, MIN_FOV_ANGLE, MAX_FOV_ANGLE);
}


void Camera::updateCameraVectors() {
	vec3 _front = vec3(0);
	_front.x = cos(radians(camYaw)) * cos(radians(camPitch));
	_front.y = sin(radians(camPitch));
	_front.z = sin(radians(camYaw)) * cos(radians(camPitch));

	this->front = normalize(_front);
	this->right = normalize(cross(front, WORLD_UP));
	this->up = normalize(cross(this->right, this->front));
}