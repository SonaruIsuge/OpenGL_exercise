#pragma once

#include "../Components/Shape.h"


class GDShape : public Shape {
public:
	GDShape(const char* dataPath, Shape* parent = nullptr);
};