#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 direction) {
    this->direction = direction;
    this->type = SPOT;
}