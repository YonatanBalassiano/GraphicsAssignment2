//
// Created by Yonatan Balassiano on 30/01/2024.
//

#include "Light.h"

void Light::setIntensity(glm::vec4 intensity) {
    this-> rgbIntensity = glm::vec3(intensity.r, intensity.g, intensity.b);
    this-> shiness = intensity.a;
}


