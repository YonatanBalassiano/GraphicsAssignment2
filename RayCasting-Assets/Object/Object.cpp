//
// Created by Yonatan Balassiano on 30/01/2024.
//
#include <cmath>
#include "Object.h"
#include "glm/glm.hpp"

void Object::setColor(glm::vec4 color) {
    this->color = glm::vec3(color.r, color.g, color.b);
    this->colorAlpha = color.a;
}

float calculateVectorSize(const glm::vec3& vec) {
    return std::sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

glm::vec3 normalizeVec(const glm::vec3& vec) {
    float size = calculateVectorSize(vec);
    return { vec.x / size, vec.y / size, vec.z / size };
}
