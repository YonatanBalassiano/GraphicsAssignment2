//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_SPOTLIGHT_H
#define GAME_SPOTLIGHT_H

#include <glm/glm.hpp>
#include "Light.h"

class SpotLight : public Light {
public:
    SpotLight(glm::vec3 direction);
    SpotLight();
    ~SpotLight();
};

#endif //GAME_SPOTLIGHT_H
