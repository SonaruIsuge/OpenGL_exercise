#include "Cube.h"
#include "../Tools/GeometryFileReader.h"

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

	CreateBuffers();

	if (parent != nullptr) {
		this->parent = parent;
	}
	else this->parent = nullptr;

}


Cube::~Cube() {

}
