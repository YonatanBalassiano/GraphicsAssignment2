//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_DIRECTIONALLIGHT_H
#define GAME_DIRECTIONALLIGHT_H

#include "glm/glm.hpp"
#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3 direction);
    DirectionalLight();
    ~DirectionalLight();
};

#endif //GAME_DIRECTIONALLIGHT_H
