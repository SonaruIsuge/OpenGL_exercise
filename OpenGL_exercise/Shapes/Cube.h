#pragma once

#include "../Components/Shape.h"


class Cube : public Shape {
private:


public:

	Cube(Shape* parent = nullptr);
	~Cube();
};