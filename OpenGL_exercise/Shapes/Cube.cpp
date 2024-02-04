#include "Cube.h"


Cube::Cube(Shape* parent) : Shape(parent) {
	vtxNum = 6;

	points = new vec4[vtxNum];

	points[0] = vec4(-0.5f,  0.5f, 0.0f, 1.0f);
	points[1] = vec4( 0.5f,  0.5f, 0.0f, 1.0f);
	points[2] = vec4( 0.5f, -0.5f, 0.0f, 1.0f);
	points[3] = vec4(-0.5f,  0.5f, 0.0f, 1.0f);
	points[4] = vec4( 0.5f, -0.5f, 0.0f, 1.0f);
	points[5] = vec4(-0.5f, -0.5f, 0.0f, 1.0f);

	colors = new vec4[vtxNum];

	colors[0] = vec4(1.0f);
	colors[1] = vec4(1.0f);
	colors[2] = vec4(1.0f);
	colors[3] = vec4(1.0f);
	colors[4] = vec4(1.0f);
	colors[5] = vec4(1.0f);

	CreateBuffers();

	if (parent != nullptr) {
		this->parent = parent;
	}
	else this->parent = nullptr;

}


Cube::~Cube() {

}


void Cube::Update(float deltaTime) {
	
}
