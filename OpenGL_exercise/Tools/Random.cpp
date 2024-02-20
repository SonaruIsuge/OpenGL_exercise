#include <time.h>
#include "Random.h"


Random::Random()
{
	seed = (unsigned)time(NULL);
}


Random::~Random()
{

}


int Random::randInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}


float Random::randFloat(float min, float max)
{
	float randF = (float)rand() / (RAND_MAX);
	return (max - min) * randF + min;
}


float Random::rand01()
{
	return (float)rand() / (RAND_MAX);
}


vec3 Random::randPointInRound(float radius)
{
	float theta = randFloat(0, 2 * 3.1415926f);
	float lengthSquare = randFloat(0, radius * radius);
	vec3 result;
	result.x = sqrtf(lengthSquare) * cosf(theta);
	result.y = sqrtf(lengthSquare) * sinf(theta);
	result.z = 0;
	return result;
}