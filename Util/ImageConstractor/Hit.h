//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_HIT_H
#define GAME_HIT_H

#include "glm/glm.hpp"
#include "../Object/Object.h"

class Hit {
public:
    Object * hittedObject;
    glm::vec3 hit;
    Hit(Object * hittedObject, const glm::vec3& hit);
    ~Hit() = default;
};

#endif //GAME_HIT_H
