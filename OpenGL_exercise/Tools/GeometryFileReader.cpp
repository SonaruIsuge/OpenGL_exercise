#include "GeometryFileReader.h"

#include <fstream>

GeometryFileReader::GeometryFileReader() {
    
}


GeometryFileReader::~GeometryFileReader() {

}


GeometryData GeometryFileReader::ReadDataFromFile(const char* filePath, bool& success) {
    GeometryData result;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "ERROR: CAN'T OPEN FILE: " << filePath << std::endl;
        success = false;
        return result;
    }

    std::string line;
    while (file >> line) {
        if (line == "p") {
            vec4 point(1.0f);
            file >> point.x >> point.y >> point.z;
            result.points.push_back(point);
        }

        if (line == "c") {
            vec4 color(1.0f);
            file >> color.x >> color.y >> color.z >> color.w;
            result.colors.push_back(color);
        }

        if (line == "r") {
            float radius = 0;
            file >> radius;
            result.boundRadius = radius;
        }
    }

    result.vertexNum = result.points.size();
    success = true;
    return result;
}
