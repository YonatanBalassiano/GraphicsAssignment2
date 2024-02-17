//
// Created by Yonatan Balassiano on 30/01/2024.
//
#include "Plane.h"

Plane::Plane(const glm::vec4& position, objectTypes type) {
    this ->type = type;
    this ->objectData = position;
}

Plane::Plane(glm::vec4 position, objectTypes type, glm::vec3 color, int index) {
    this ->type = type;
    this ->objectData = position;
    this ->color = color;
    this ->index = index;
}

glm::vec3 Plane::normal() {
    return glm::vec3(objectData.x, objectData.y, objectData.z);
}
float Plane::distance() {
    return objectData.w;
}

float Plane::FindIntersection(Ray ray) {
   if (glm::dot(normal(), ray.direction) == 0)
       return -1;

   float t = -(glm::dot(normal(), ray.point) + distance()) / glm::dot(normal(), ray.direction);
   (t < 0) ? -1 : t;
}

glm::vec3 Plane::getColor(const glm::vec3& hit) const {
    float param = std::floor((hit.x < 0 ? (0.5 - hit.x) : hit.x) / 0.5f)
            + std::floor((hit.y < 0 ? (0.5 - hit.y) : hit.y) / 0.5f);

    param = std::fmod(param * 0.5, 1.0) * 2;
    return (param > 0.5) ? 0.5f * color : color;
}

glm::vec3 Plane::getNormal(glm::vec3 hit){
    return normalizeVec(this->normal());
}

