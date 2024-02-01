#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

class Shape {
protected:
	Shader* shader;
	GLuint VAO;
	GLuint VBO;

	GLuint modelViewLoc;
	GLuint projLoc;

	mat4 model;
	mat4 view;
	mat4 modelView;
	mat4 projection;

	bool updateProjMat;

	void SetShader(mat4 viewMat, mat4 projectionMat);
	void CreateBuffers();

	mat4 GetTRSMatrix();

public:
	vec4* points;
	vec4* colors;

	int vtxNum;
	
	vec3 position;
	vec3 rotation;
	vec3 scale;


	Shape();
	virtual ~Shape();

	void Init(vec4 vColor, mat4 view, mat4 projection);
	void Draw();
	virtual void Update(float deltaTime) = 0;
	
	void SetSingleColor(vec4 color);
	void SetViewMatrix(mat4& viewMat);
	void SetProjectionMatrix(mat4& projMat);

};