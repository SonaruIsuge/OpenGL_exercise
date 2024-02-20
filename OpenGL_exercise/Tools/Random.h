#pragma once

#include <glm/glm.hpp>

using namespace glm;


class Random
{
private:
	unsigned seed;

public:

	Random();
	~Random();

	int randInt(int min, int max);
	float randFloat(float min, float max);
	float rand01();
	vec3 randPointInRound(float radius);
};