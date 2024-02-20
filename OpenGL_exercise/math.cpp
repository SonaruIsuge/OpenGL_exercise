#include "math.h"


namespace gameMath {


    float angleWithSign(glm::vec3 refVec, glm::vec3 vec) {
        return atan2(vec.y, vec.x) - atan2(refVec.y, refVec.x);
    }
}