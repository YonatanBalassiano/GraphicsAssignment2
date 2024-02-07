//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "glm/glm.hpp"
#include "../Components/Ray.h"

enum objectTypes {
    REGULAR = 0,
    TRANSPARENT = 1,
    REFLECTIVE = 2,
    NONE = 3
};

class Object {
public:
    glm::vec4 objectData;
    glm::vec3 color;
    float colorAlpha;
    int index;
    objectTypes type;
    void setColor(glm::vec4 color);
    virtual ~Object() = default;
    virtual float FindIntersection(Ray ray) = 0;
    virtual glm::vec3 getColor(const glm::vec3& color) const = 0;
    virtual glm::vec3 getNormal(glm::vec3 hit) = 0;

};

float calculateVectorSize(const glm::vec3& vec);
glm::vec3 normalizeVec(const glm::vec3& vec);

#endif //GAME_OBJECT_H
