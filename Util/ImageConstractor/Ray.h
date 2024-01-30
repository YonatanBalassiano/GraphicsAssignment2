//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_RAY_H
#define GAME_RAY_H

#include "glm/glm.hpp"


class Ray {
public:
    glm::vec3 point;
    glm::vec3 direction;
    Ray(glm::vec3 point, glm::vec3 direction);
    ~Ray() = default;

};

#endif //GAME_RAY_H
