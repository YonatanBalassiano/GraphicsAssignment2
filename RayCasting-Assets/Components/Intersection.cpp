//
// Created by Yonatan Balassiano on 30/01/2024.
//
#include "Intersection.h"

Intersection::Intersection(Object *hittedObject, const glm::vec3& hit) {
    this->hittedObject = hittedObject;
    this->hit = hit;
}

