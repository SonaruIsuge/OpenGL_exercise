#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;


typedef struct GeometryFileData {
	int vertexNum;
	vector<vec4> points;
	vector<vec4> colors;
} GeometryData;


class GeometryFileReader {
private:


public:

	GeometryFileReader();
	~GeometryFileReader();

	GeometryData ReadDataFromFile(const char* filePath, bool& success);
};