//
// Created by Yonatan Balassiano on 30/01/2024.
//

#include "Sphere.h"

Sphere::Sphere(const glm::vec4& position, objectTypes type) {
    this ->type = type;
    this ->objectData = position;
    this->radius = position.w;
}

float Sphere::getRadius() const {
    return radius;
}
