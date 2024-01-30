//
// Created by Yonatan Balassiano on 30/01/2024.
//
#include "Plane.h"

Plane::Plane(const glm::vec4& position, objectTypes type) {
    this ->type = type;
    this ->objectData = position;
}

glm::vec3 Plane::normal() {
    return glm::vec3(objectData.x, objectData.y, objectData.z);
}

float Plane::distance() {
    return objectData.w;
}

/////////// CHECK THIS
float Plane::FindIntersection(Ray ray) {
    glm::vec3 rayDirection = ray.direction;
    glm::vec3 rayStartPoint = ray.point;
    float normalDotRayDirection = glm::dot(this->normal(), rayDirection);
    if (normalDotRayDirection == 0) // ray is parallel to plane
        return -1;
    
    float normalDotrayStartPoint = glm::dot(this->normal(), rayStartPoint);
    float t = -(normalDotrayStartPoint + this->distance()) / normalDotRayDirection;
    if (t < 0) // plane is behind ray
        return -1;

    return t;
}

/////////// CHECK THIS
glm::vec3 Plane::getColor(const glm::vec3& hit) const {
    float param = (std::floor((hit.x < 0 ? (0.5 - hit.x) : hit.x) / 0.5f)
                    + std::floor((hit.y < 0 ? (0.5 - hit.y) : hit.y) / 0.5f));

    param = (std::fmod(param * 0.5, 1.0) * 2);
    return (param > 0.5) ? 0.5f * color : color;
}


glm::vec3 Plane::getNormal(glm::vec3 hit) {
    return normalizeVec(this->normal());    
}
