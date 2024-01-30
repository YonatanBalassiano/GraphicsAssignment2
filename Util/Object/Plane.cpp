//
// Created by Yonatan Balassiano on 30/01/2024.
//
#include "Plane.h"

Plane::Plane(const glm::vec4& position, objectTypes type) {
    this ->type = type;
    this ->objectData = position;
}

