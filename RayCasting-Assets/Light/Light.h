//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_LIGHT_H
#define GAME_LIGHT_H
#include "glm/glm.hpp"


enum lightTypes {
    AMBIENT = 0,
    DIRECTIONAL = 1,
    SPOT = 2
};
class Light{
public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 rgbIntensity;
    float angle;
    lightTypes type;
    float shiness;
    void setIntensity(glm::vec4 intensity);
    // Light() = default;
    // ~Light() = default;
};

#endif


