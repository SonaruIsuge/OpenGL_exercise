#pragma once
#include "Camera.h"
#include "../Shapes/Shape.h"
#include "../Tools/ObjectPool.h"
#include "../Tools/GameSettings.h"
#include "../Tools/Random.h"


class Background
{
private:
	Random random;
	Shape* stars[STAR_NUMBER];
	float starsSpeed[STAR_NUMBER];

public:

	Background(Camera* camera);
	~Background();
	void Update(float deltaTime);

};