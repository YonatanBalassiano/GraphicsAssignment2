//
// Created by Yonatan Balassiano on 30/01/2024.
//

#include "ImageConstructor.h"
#include "../Object/Plane.h"
#include <iostream>



Image ImageConstructor::constructImage(const string& fileName, const int width, const int height){
    configReader = new ConfigReader();
    configReader->readConfigFile(fileName, width, height);
    Image image = Image(width, height);

    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++) {
            Ray testRay = Ray(glm::vec3(7,7,7), glm::vec3(3,3,3));
            Ray ray = constructRayThroughPixel(x, y, configReader->getEye());
            Intersection intersection = FindIntersection(ray, -1);
            glm::vec4 color = getColor(intersection, ray, 0);
            image.setColorToPixel(x,y,color);
        }
    }
    return image;
}

Ray ImageConstructor::constructRayThroughPixel(const int x, const int y, const glm::vec3& eye) {
    glm::vec3 topLeftPoint = glm::vec3(-1+(configReader->getPixelWidth()/2), 1-(configReader->getPixelHeight()/2), 0);
    glm::vec3 hitVector = topLeftPoint + glm::vec3(x*configReader->getPixelWidth(), -1*(y*configReader->getPixelHeight()), 0);
    return {eye, normalizeVec(hitVector - eye)};
}


Intersection ImageConstructor::FindIntersection(const Ray& ray, int index) {
        float minT = INFINITY;
        Object* minPrimitive = new Plane(glm::vec4(0,0,0,0), NONE);
        minPrimitive->index = -1;
        minPrimitive->setColor(glm::vec4(0,0,0,0));
        vector<Object*> objects = configReader->getObjectsData();
        for (auto & object : objects) {
            if (object->index == index) {
                continue;
            }
            float t = object-> FindIntersection(ray);
            if (t < minT) {
                minT = t;
                minPrimitive = object;
            }
        }
        return (minT==INFINITY) ? Intersection(minPrimitive, ray.direction + ray.point) : Intersection(minPrimitive, ray.direction + ray.point * minT); 
}

glm::vec4 ImageConstructor::getColor(const Intersection& intersection, const Ray& ray, int depth) {
    glm::vec3 phong;
    if (intersection.hittedObject->type == REGULAR) {
        phong = GetColorRegular(intersection, ray);
    } else if (depth == 5) {
        return glm::vec4(0,0,0,0);
    } else if (intersection.hittedObject->type == REFLECTIVE) {
        phong = GetColorReflective(intersection, ray, depth);
    } else {
        phong = GetColorTransparent(intersection, ray, depth);
    }

    return glm::vec4(phong.r, phong.g, phong.b, 0.0);
}

glm::vec3 ImageConstructor::GetColorRegular(const Intersection& intersection, const Ray& ray) {
    glm::vec3 color = intersection.hittedObject->getColor(intersection.hit) * glm::vec3(configReader->getAmbient().r, configReader->getAmbient().g, configReader->getAmbient().b);
    for (auto & light : configReader->getLightData()) {
        //need to refactor according to scheme
        Ray lightRay = constructRayToLight(light, intersection);
        if (isLightVisible(lightRay,light)) {
            float shadowFactor = calcShadow(intersection, light);
            color += calcDiffuseColor(light, intersection) * shadowFactor;
            color += calcSpecularColor(ray, light, intersection) * shadowFactor;
        }
    }
    return glm::min(color, glm::vec3(1,1,1));

}

//todo: Refactor
glm::vec3 ImageConstructor::GetColorReflective(const Intersection& intersection, const Ray& ray, int depth) {
        glm::vec3 reflection_ray_direction = ray.direction - 2.0f * intersection.hittedObject->getNormal(intersection.hit) *
                                                        glm::dot(ray.direction, intersection.hittedObject->getNormal(intersection.hit));
        Ray reflection_ray = Ray(reflection_ray_direction, intersection.hit);
        Intersection reflected_hit = FindIntersection(reflection_ray, intersection.hittedObject->index);

        if (reflected_hit.hittedObject->type == NONE) {
            return {0,0,0};
        }

        glm::vec4 reflection_color = getColor(reflected_hit,reflection_ray, depth + 1);
        return glm::min (glm::vec3(reflection_color.r, reflection_color.g, reflection_color.b), glm::vec3(1,1,1));
}


//todo: Refactor
glm::vec3 ImageConstructor::GetColorTransparent(const Intersection& intersection, const Ray& ray, int depth) {
    glm::vec4 color;
    if (intersection.hittedObject -> objectData.a < 0.0) return getTransparentPlaneColor(intersection, ray,depth);
    // Snell's law
    float pi = 3.14159265;
            float snellFrac = (1.0f / 1.5f);

            float cosFrom = glm::dot(intersection.hittedObject->getNormal(intersection.hit), -ray.direction);
            float thetaFrom = acos(cosFrom) * (180.0f / pi);
            float sinFrom = sin(thetaFrom * (pi / 180.0f));
            float sinTo = snellFrac * sinFrom;
            float thetaTo = asin(sinTo) * (180.0f / pi);
            float cosTo = cos(thetaTo * (pi / 180.0f));

            glm::vec3 rayDirection =
                    (snellFrac * cosFrom - cosTo) * intersection.hittedObject->getNormal(intersection.hit) - snellFrac * (-ray.direction);
            rayDirection = normalizeVec(rayDirection);
            Ray rayIn = Ray(rayDirection, intersection.hit);

            Intersection transparencyHit = FindIntersection(rayIn, -1);

            if (transparencyHit.hittedObject->index != intersection.hittedObject->index) {
                color = getColor(transparencyHit,rayIn, depth + 1);
            }
            else {
                float t = intersection.hittedObject->FindIntersection(rayIn);
                glm::vec3 secondHitPoint = rayIn.point + rayIn.direction * t;

                cosFrom = glm::dot(-intersection.hittedObject->getNormal(secondHitPoint), -rayIn.direction);
                thetaFrom = acos(cosFrom) * (180.0f / pi);
                snellFrac = (1.5f / 1.0f);
                sinFrom = sin(thetaFrom * (pi / 180.0f));
                sinTo = snellFrac * sinFrom;
                thetaTo = asin(sinTo) * (180.0f / pi);
                cosTo = cos(thetaTo * (pi / 180.0f));

                glm::vec3 rayOutDirection = (snellFrac * cosFrom - cosTo) * -intersection.hittedObject->getNormal(intersection.hit) - snellFrac * (-rayIn.direction);
                rayOutDirection = normalizeVec(rayOutDirection);
                Ray ray_out = Ray(rayOutDirection, secondHitPoint);

                Intersection transparencyHitOut = FindIntersection(ray_out, intersection.hittedObject->index);

                if (transparencyHitOut.hittedObject->type == NONE) {
                    return glm::vec3(0.f, 0.f, 0.f);
                }

                color = getColor(transparencyHitOut,ray_out, depth + 1);
            }
        
    return glm::min(glm::vec3(color.r, color.g, color.b), glm::vec3(1.0f, 1.0f, 1.0f));

}

glm::vec3 ImageConstructor :: getTransparentPlaneColor(const Intersection& intersection, const Ray& ray, int depth) {
    Ray rayThrowPlane = Ray(ray.direction, intersection.hit);
    Intersection planeIntersection = FindIntersection(rayThrowPlane, intersection.hittedObject->index);
    if (planeIntersection.hittedObject->type == NONE) {
        return {0,0,0};
    }
    glm::vec4 color = getColor(planeIntersection, rayThrowPlane, depth + 1);
}

// //todo: implement
// glm::vec3 ImageConstructor::calcAmbientColor() {
//     return {0,0,0};
// }

// //todo: implement
// glm::vec3 ImageConstructor::calcEmissionColor() {
//     return {0,0,0};
// }

//todo: implement
bool ImageConstructor::isLightVisible(const Ray lightRay,const Light* light){
    return true;
}

//todo: implement
Ray ImageConstructor::constructRayToLight(const Light* light, Intersection intersection) {
    return {glm::vec3(0,0,0), glm::vec3(0,0,0)};
}

glm::vec3  ImageConstructor::calcDiffuseColor(const Light* light, const Intersection intersection){
    float factor = intersection.hittedObject->objectData.a < 0 ? -1 : 1;
    glm::vec3 normalizedRay = calcNormalizeRay(light, intersection, factor);
    glm::vec3 objectNormal = intersection.hittedObject->getNormal(intersection.hit);
    float hitCosValue = glm::dot(objectNormal, -normalizedRay);
    glm::vec3 diffuse_color = intersection.hittedObject->getColor(intersection.hit) * hitCosValue * light->rgbIntensity;

    return isHittingAnObject(light,intersection,factor,normalizedRay) ? diffuse_color : glm::vec3(0, 0, 0);
}


glm::vec3 ImageConstructor::calcSpecularColor(const Ray ray, const Light* light, const Intersection intersection) {
    glm::vec3 normalizedRay = calcNormalizeRay(light, intersection, 1);
    glm::vec3 object_normal = intersection.hittedObject->getNormal(intersection.hit);
    glm::vec3 reflected_light_ray = normalizedRay - 2.0f * object_normal * glm::dot(normalizedRay, object_normal);
    glm::vec3 ray_to_viewer = normalizeVec(ray.point - intersection.hit);
    float cosAngleValue = pow(glm::max(0.0f , glm::dot(ray_to_viewer,reflected_light_ray)),intersection.hittedObject->colorAlpha);
    glm::vec3 specularColor = 0.7f * cosAngleValue * light->rgbIntensity;

    return isHittingAnObject(light,intersection,1,normalizedRay) ? specularColor : glm::vec3(0, 0, 0);
}

float ImageConstructor::calcShadow( const Intersection intersection, const Light* light) {
    glm::vec3 normalizedRayDirection = normalizeVec(light->direction);
    float minT = INFINITY;

    // Spotlight
    if (light->type == SPOT) {
        glm::vec3 virtualSpotlightRay = normalizeVec(intersection.hit - light->position);
        float lightCosValue = glm::dot(virtualSpotlightRay, normalizedRayDirection);

        // Checks if hit the object
        if (lightCosValue < light->angle) {
            return 0.0;
        }
        normalizedRayDirection = virtualSpotlightRay;
        // Update minT
        minT = -(glm::dot(intersection.hit, light->position)) / abs(glm::dot(-normalizedRayDirection, light->position));
    }

    vector<Object *> objectsData = configReader->getObjectsData();

    // Checks other objects
    for (int i = 0; i < objectsData.size(); i++) {
        if (i != intersection.hittedObject->index) {
            Ray ray = Ray(-normalizedRayDirection, intersection.hit);
            float t = objectsData[i]->FindIntersection(ray);

            if ((t > 0) && (t < minT)) {
                return 0.0;
            }
        }
    }
    return 1.0;
}


bool ImageConstructor::isHittingAnObject(const Light *light, const Intersection &intersection, float factor,
                                  const glm::vec3 &normlizedRay) const { return glm::dot(normalizeVec(intersection.hit - light->position), factor * normlizedRay) >= light->angle; }

glm::vec3 ImageConstructor::calcNormalizeRay(const Light* light, const Intersection intersection, const float factor) {
    return (light->type == SPOT) ? factor * normalizeVec(intersection.hit - light->position): factor * normalizeVec(light->direction);
}

glm::vec4 ImageConstructor::getColorOld(Intersection hit,Ray ray, int depth) {
    glm::vec3 phongModelColor = glm::vec3(0, 0, 0);

    // Regular
    if (hit.hittedObject->type == REGULAR) {
        glm::vec3 color = hit.hittedObject->getColor(hit.hit);
        phongModelColor = color * glm::vec3(configReader->getAmbient().r, configReader->getAmbient().g, configReader->getAmbient().b); // Ambient

        vector<Light *> lights = configReader->getLightData();
        // Checks lights
        for (int i = 0; i < lights.size(); i++) {
            glm::vec3 diffuseColor = glm::max(calcDiffuseColor(lights[i],hit), glm::vec3(0, 0, 0)); // Diffuse
            glm::vec3 specularColor = glm::max(calcSpecularColor(ray,lights[i],hit), glm::vec3(0, 0, 0)); // Specular
            float shadowTerm = calcShadow(hit, lights[i]); // Shadow
            phongModelColor += (diffuseColor + specularColor) * shadowTerm;
        }
        phongModelColor = glm::min(phongModelColor, glm::vec3(1.0, 1.0, 1.0));
    }

    // Reflective
    if (hit.hittedObject->type == REFLECTIVE) {
        if (depth == 5) { // MAX_LEVEL=5
            return glm::vec4(0.f, 0.f, 0.f, 0.f);
        }

        glm::vec3 reflection_ray_direction = ray.direction - 2.0f * hit.hittedObject->getNormal(hit.hit) *
                                                        glm::dot(ray.direction, hit.hittedObject->getNormal(hit.hit));
        Ray reflection_ray = Ray(reflection_ray_direction, hit.hit);

        Intersection reflected_hit = FindIntersection(reflection_ray, hit.hittedObject->index);

        if (reflected_hit.hittedObject->type == NONE) {
            return glm::vec4(0.f, 0.f, 0.f, 0.f);
        }

        glm::vec4 reflection_color = getColor(reflected_hit,reflection_ray, depth + 1);
        phongModelColor = glm::vec3(reflection_color.r, reflection_color.g, reflection_color.b);
        phongModelColor = glm::min(phongModelColor, glm::vec3(1.0, 1.0, 1.0));
    }

    // Transparent
    if (hit.hittedObject->type == TRANSPARENT) {
        if (depth == 5) {
            return glm::vec4(0.f, 0.f, 0.f, 0.f);
        }

        glm::vec4 transparencyColor = glm::vec4(0.f, 0.f, 0.f, 0.f);

        // Transparent Plane
        if (hit.hittedObject->objectData.w < 0.0) {
            Ray rayThrough = Ray(ray.direction, hit.hit);

            Intersection transparency_hit = FindIntersection(rayThrough, hit.hittedObject->index);

            if (transparency_hit.hittedObject->type == NONE) {
                return glm::vec4(0.f, 0.f, 0.f, 0.f);
            }

            transparencyColor = getColor(transparency_hit,rayThrough, depth + 1);
        }
            // Transparent Sphere
        else {
            // Snell's law
            float pi = 3.14159265;
            float snellFrac = (1.0f / 1.5f);

            float cosFrom = glm::dot(hit.hittedObject->getNormal(hit.hit), -ray.direction);
            float thetaFrom = acos(cosFrom) * (180.0f / pi);
            float sinFrom = sin(thetaFrom * (pi / 180.0f));
            float sinTo = snellFrac * sinFrom;
            float thetaTo = asin(sinTo) * (180.0f / pi);
            float cosTo = cos(thetaTo * (pi / 180.0f));

            glm::vec3 rayDirection =
                    (snellFrac * cosFrom - cosTo) * hit.hittedObject->getNormal(hit.hit) - snellFrac * (-ray.direction);
            rayDirection = normalizeVec(rayDirection);
            Ray rayIn = Ray(rayDirection, hit.hit);

            Intersection transparencyHit = FindIntersection(rayIn, -1);

            if (transparencyHit.hittedObject->index != hit.hittedObject->index) {
                transparencyColor = getColor(transparencyHit,rayIn, depth + 1);
            }
            else {
                float t = hit.hittedObject->FindIntersection(rayIn);
                glm::vec3 secondHitPoint = rayIn.point + rayIn.direction * t;

                cosFrom = glm::dot(-hit.hittedObject->getNormal(secondHitPoint), -rayIn.direction);
                thetaFrom = acos(cosFrom) * (180.0f / pi);
                snellFrac = (1.5f / 1.0f);
                sinFrom = sin(thetaFrom * (pi / 180.0f));
                sinTo = snellFrac * sinFrom;
                thetaTo = asin(sinTo) * (180.0f / pi);
                cosTo = cos(thetaTo * (pi / 180.0f));

                glm::vec3 rayOutDirection = (snellFrac * cosFrom - cosTo) * -hit.hittedObject->getNormal(hit.hit) -
                                       snellFrac * (-rayIn.direction);
                rayOutDirection = normalizeVec(rayOutDirection);
                Ray ray_out = Ray(rayOutDirection, secondHitPoint);

                Intersection transparencyHitOut = FindIntersection(ray_out, hit.hittedObject->index);

                if (transparencyHitOut.hittedObject->type == NONE) {
                    return glm::vec4(0.f, 0.f, 0.f, 0.f);
                }

                transparencyColor = getColor(transparencyHitOut,ray_out, depth + 1);
            }
        }
        phongModelColor = glm::vec3(transparencyColor.r, transparencyColor.g, transparencyColor.b);
        phongModelColor = glm::min(phongModelColor, glm::vec3(1.0, 1.0, 1.0));
    }
    return glm::vec4(phongModelColor.r, phongModelColor.g, phongModelColor.b, 0.0);
}





