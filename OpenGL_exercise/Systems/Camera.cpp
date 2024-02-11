#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(PROJECTION_TYPE type) {
	viewMat = mat4(1.0f);
	projMat = mat4(1.0f);
	projType = type;

	UpdateMat();
}


Camera::~Camera() {

}


mat4 Camera::GetViewMatrix() {
	return viewMat;
}


mat4 Camera::GetProjMatrix() {
	return projMat;
}


void Camera::UpdateMat() {
	viewMat = mat4(1.0f);
	
	if (projType == ORTHOGONAL) {
		projMat = ortho(-ORTHO_WIDTH, ORTHO_WIDTH, -ORTHO_HEIGHT, ORTHO_HEIGHT, -1.0f, 1.0f);
	}
	else {
		projMat = perspective(PERSP_FOV, ASPECT, 0.1f, 100.0f);
	}
}


void Camera::SetProjType(PROJECTION_TYPE type) {
	projType = type;
	UpdateMat();	
}