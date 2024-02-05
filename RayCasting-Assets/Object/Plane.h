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

    glm::vec3 normal();
    float distance();
    float FindIntersection(Ray ray) override;
    glm::vec3 getColor(const glm::vec3& hit) const;
    glm::vec3 getNormal(glm::vec3 hit) override;
};

#endif //GAME_PLANE_H
