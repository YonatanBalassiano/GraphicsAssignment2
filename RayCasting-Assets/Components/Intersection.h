//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_INTERSECTION_H
#define GAME_INTERSECTION_H

#include "glm/glm.hpp"
#include "../Object/Object.h"

class Intersection {
public:
    Object * hittedObject;
    glm::vec3 hit;
    Intersection(Object * hittedObject, const glm::vec3& hit);
    ~Intersection() = default;
};

#endif //GAME_INTERSECTION_H
