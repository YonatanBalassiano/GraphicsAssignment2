//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_SPHERE_H
#define GAME_SPHERE_H

#include "Object.h"

class Sphere : public Object {
public:
    float radius;

    float getRadius() const;

    Sphere(const glm::vec4& position, objectTypes type);
    ~Sphere() override = default;
};

#endif //GAME_SPHERE_H
