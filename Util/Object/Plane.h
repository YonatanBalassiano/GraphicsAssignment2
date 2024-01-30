//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_PLANE_H
#define GAME_PLANE_H

#include "Object.h"

class Plane : public Object {
public:
    Plane(const glm::vec4& position, objectTypes type);
    ~Plane() override = default;
};

#endif //GAME_PLANE_H
