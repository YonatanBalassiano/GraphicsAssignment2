//
// Created by Yonatan Balassiano on 30/01/2024.
//
#include "Hit.h"

Hit::Hit(Object *hittedObject, const glm::vec3& hit) {
    this->hittedObject = hittedObject;
    this->hit = hit;
}

