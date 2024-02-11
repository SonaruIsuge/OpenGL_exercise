#include "GDShape.h"
#include "../Tools/GeometryFileReader.h"

GDShape::GDShape(const char* dataPath, Shape* parent) : Shape(parent) {
	GeometryFileReader reader;
	GeometryData data;
	bool readSuccess = false;

	data = reader.ReadDataFromFile(dataPath, readSuccess);
	if (!readSuccess) return;

	vtxNum = data.vertexNum;
	points = new vec4[vtxNum];
	colors = new vec4[vtxNum];
	for (int i = 0; i < vtxNum; i++) {
		points[i] = data.points[i];
		colors[i] = data.colors[i];
	}

	CreateBuffers();

	if (parent != nullptr) {
		this->parent = parent;
	}
	else this->parent = nullptr;
}