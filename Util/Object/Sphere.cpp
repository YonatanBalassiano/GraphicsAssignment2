//
// Created by Yonatan Balassiano on 30/01/2024.
//

#include "Sphere.h"
#include <utility>

Sphere::Sphere(const glm::vec4& position, objectTypes type) {
    this ->type = type;
    this ->objectData = position;
    this->radius = position.w;
}

float Sphere::getRadius() const {
    return radius;
}

glm::vec3 Sphere::getCenter() const {
    return glm::vec3(objectData.x, objectData.y, objectData.z);
}

float Sphere::FindIntersection(Ray ray) {
    glm::vec3 rayDirection = ray.direction;
    glm::vec3 rayStartPoint = ray.point;
    glm::vec3 sphereCenter = this->getCenter();
    float radius = this->getRadius();
    glm::vec3 rayToSphereCenter = rayStartPoint - sphereCenter;
    float a = glm::dot(rayDirection, rayDirection);
    float b = 2 * glm::dot(rayDirection, rayToSphereCenter);
    float c = glm::dot(rayToSphereCenter, rayToSphereCenter) - radius * radius;
    float discriminant = b*b-4*a*c;

    if (discriminant < 0) // no intersection
        return -1;
    float t1 = (-b - sqrt(discriminant)) / (2*a);
    float t2 = (-b + sqrt(discriminant)) / (2*a);
    if (t1 < 0 && t2 < 0) // sphere is behind ray
        return -1;
    if (t1 < 0) // t2 is the only intersection
        return t2;
    if (t2 < 0) // t1 is the only intersection
        return t1;

    float inter;
    // incase of Transperant spheres
    float threshold = 0.001f;
    (std::min(t1, t2) <= threshold)? inter = glm::max(t1, t2) : inter = std::min(t1, t2);
    return inter;
}

glm::vec3 Sphere::getNormal(glm::vec3 hit) {
    return normalizeVec(hit - this->getCenter());    
}

glm::vec3 Sphere::getColor(const glm::vec3& hit) const {
    return color;
}
