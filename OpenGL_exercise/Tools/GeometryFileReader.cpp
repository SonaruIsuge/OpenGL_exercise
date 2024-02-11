#include "GeometryFileReader.h"

#include <fstream>

GeometryFileReader::GeometryFileReader() {

}


GeometryFileReader::~GeometryFileReader() {

}


GeometryData GeometryFileReader::ReadDataFromFile(const char* filePath, bool& success) {
    GeometryData result;
    ifstream file(filePath);

    if (!file.is_open()) {
        cout << "ERROR: CAN'T OPEN FILE: " << filePath << endl;
        success = false;
        return result;
    }

    string line;
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
    }

    result.vertexNum = result.points.size();
    success = true;
    return result;
}
