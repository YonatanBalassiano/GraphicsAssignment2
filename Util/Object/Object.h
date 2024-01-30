//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "glm/glm.hpp"
#include "../Util/ImageConstractor/Ray.h"

enum objectTypes {
    REGULAR = 0,
    TRANSPARENT = 1,
    REFLECTIVE = 2,
};

class Object {
public:
    glm::vec4 objectData;
    glm::vec3 color;
    float colorAlpha;
    int index;
    glm::vec4 direction;
    objectTypes type;
    void setColor(glm::vec4 color);
    virtual ~Object() = 0;
};

float calculateVectorSize(const glm::vec3& vec);
glm::vec3 normalizeVec(const glm::vec3& vec);

#endif //GAME_OBJECT_H
