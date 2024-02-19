#pragma once



#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;


namespace Debug {

	void Print(const mat4& mat) {
		const float* valuePtr = value_ptr(mat);

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				std::cout << valuePtr[i * 4 + j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void Print(const vec3& vec) {
		std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
	}
}
