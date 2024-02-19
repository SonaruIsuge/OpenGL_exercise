#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

using namespace glm;


typedef struct GeometryFileData {
	int vertexNum;
	std::vector<vec4> points;
	std::vector<vec4> colors;
	float boundRadius;
} GeometryData;


class GeometryFileReader {
private:


public:

	GeometryFileReader();
	~GeometryFileReader();

	GeometryData ReadDataFromFile(const char* filePath, bool& success);
};