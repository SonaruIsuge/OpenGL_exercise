#pragma once
#include <glm/glm.hpp>

using namespace glm;


const float ORTHO_WIDTH = 10.0f;
const float ORTHO_HEIGHT = 10.0f;
const float PERSP_FOV = 45.0f;
const float ASPECT = 1.777778f;


enum PROJECTION_TYPE {
	ORTHOGONAL,
	PERSPECTIVE
};


class Camera {
private:
	PROJECTION_TYPE projType;
	mat4 viewMat;
	mat4 projMat;

	void UpdateMat();

public:
	//vec3 position;
	//vec3 rotation;
	//vec3 scale;

	Camera(PROJECTION_TYPE type);
	~Camera();

	mat4 GetViewMatrix();
	mat4 GetProjMatrix();
	void SetProjType(PROJECTION_TYPE type);
};