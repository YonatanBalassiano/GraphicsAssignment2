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
    glm::vec3 rgbIntensity;
    float intensityAlpha;
    float direction;
    lightTypes type;
    Light(glm::vec4 position, glm::vec4 color, glm::vec4 direction, float angle1, float angle2, float falloff, float radious, float type);
    void setIntensity(glm::vec4 intensity);
    Light();
    ~Light();
}


#endif //GAME_LIGHT_H


