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
    return { objectData.x, objectData.y, objectData.z };
}

float Sphere::FindIntersection(Ray ray) {
   glm::vec3 rayToSphereCenter = ray.point - getCenter();
   float a = glm::dot(ray.direction, ray.direction);
   float b = 2 * glm::dot(ray.direction, rayToSphereCenter);
   float c = glm::dot(rayToSphereCenter, rayToSphereCenter) - getRadius() * getRadius();
   float discriminant = pow(b, 2)-4*a*c;

   if (discriminant < 0)
       return -1;
   float t1 = (-b - sqrt(discriminant)) / (2*a);
   float t2 = (-b + sqrt(discriminant)) / (2*a);
   if (t1 < 0 && t2 < 0)
       return -1;
   if (t1 < 0)
       return t2;
   if (t2 < 0)
       return t1;

   float inter;
   float threshold = 0.0001;
   (std::fmin(t1, t2) <= threshold)? inter = std::fmax(t1, t2) : inter = std::fmin(t1, t2);
   return inter;
}

glm::vec3 Sphere::getNormal(glm::vec3 hit) {
    return normalizeVec(hit - getCenter());
}

glm::vec3 Sphere::getColor(const glm::vec3& hit) const {
    return color;
}
