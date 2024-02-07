//
// Created by Yonatan Balassiano on 30/01/2024.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction){
    this->direction = direction;
    this->type = DIRECTIONAL;
}