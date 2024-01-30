//
// Created by Yonatan Balassiano on 30/01/2024.
//

#include "Object.h"
#include "glm/glm.hpp"


void Object::setColor(glm::vec4 color) {
    this->color = glm::vec3(color.r, color.g, color.b);
    this->colorAlpha = color.a;
}