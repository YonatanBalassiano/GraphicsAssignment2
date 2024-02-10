//
// Created by Yonatan Balassiano on 30/01/2024.
//

#include "ImageConstructor.h"
#include "../Object/Plane.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <corecrt_math_defines.h>

Image ImageConstructor::constructImage(const string& fileName, const int width, const int height){
    configReader = new ConfigReader();
    configReader->readConfigFile(fileName, width, height);
    Image image = Image(width, height);

    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++) {
            Ray ray = constructRayThroughPixel(y, x, configReader->getEye());
            Intersection intersection = FindIntersection(ray, -1);
            glm::vec4 color = getColor(intersection, ray, 0);
            image.setColorToPixel(y,x,color);
        }
    }
    return image;
}

Ray ImageConstructor::constructRayThroughPixel(const int x, const int y, const glm::vec3& eye) {
    float width = configReader->getPixelWidth();
    float height = configReader->getPixelHeight();    

    glm::vec3 hit = glm::vec3(-1+(width / 2), 1-(height / 2), 0) + glm::vec3(x*width, -1*(y * height), 0);
    glm::vec3 direction = normalizeVec(hit - eye);
    return {eye, direction};
}

Intersection ImageConstructor::FindIntersection(const Ray& ray, int index) {
        float minT = std::numeric_limits<float>::infinity();
        Object* minPrimitive = new Plane(glm::vec4(1,1,1,1),NONE,glm::vec3(0,0,0),-1);

        for (auto & obj :  configReader->getObjectsData()) {
            if (obj->index == index) continue;
            float t = obj->FindIntersection(ray);
            if ((t >= 0) && (t < minT)) {
                minPrimitive = obj;
                minT = t;
            }
        }
        return {minPrimitive, ray.point + ray.direction * (minPrimitive->index == -1 ? 0 : minT)};
}

glm::vec4 ImageConstructor::getColor(const Intersection& intersection, const Ray& ray, int depth) {
    glm::vec3 color;
    if (intersection.hittedObject->type == REGULAR) {
        color = GetColorRegular(intersection, ray);
    } else if (depth == 5) {
        return glm::vec4(0,0,0,0);
    } else if (intersection.hittedObject->type == REFLECTIVE) {
        color = GetColorReflective(intersection, ray, depth);
    } else {
        color = GetColorTransparent(intersection, ray, depth);
    }
    return glm::vec4(color.r, color.g, color.b, 0.0);
}

glm::vec3 ImageConstructor::GetColorRegular(const Intersection& intersection, const Ray& ray) {
    glm::vec3 color = intersection.hittedObject->getColor(intersection.hit) * glm::vec3(configReader->getAmbient().r, configReader->getAmbient().g, configReader->getAmbient().b);
    glm::vec3 ZERO = glm::vec3(0,0,0);
    for (auto & light : configReader->getLightData()) {
        if (isLightVisible(intersection, light)) {
            color += glm::max(ZERO,calcDiffuseColor(light, intersection));
            color +=glm::max(ZERO, calcSpecularColor(ray, light, intersection));
        }
    }
    return glm::min(color, glm::vec3(1.0,1.0,1.0));
}

glm::vec3 ImageConstructor::GetColorReflective(const Intersection& intersection, const Ray& ray, int depth) {
        glm::vec3 rayDirection = ray.direction - 2.0f * intersection.hittedObject->getNormal(intersection.hit) * glm::dot(ray.direction, intersection.hittedObject->getNormal(intersection.hit));
        Ray reflectionRey = Ray( intersection.hit,rayDirection);
        Intersection reflectionIntersection = FindIntersection(reflectionRey, intersection.hittedObject->index);

        if (reflectionIntersection.hittedObject->type == NONE) {
            return {0,0,0};
        }

        glm::vec4 color = getColor(reflectionIntersection,reflectionRey, depth + 1);
        return glm::min (glm::vec3(color.r, color.g, color.b), glm::vec3(1,1,1));
}

glm::vec3 ImageConstructor::GetColorTransparent(const Intersection& intersection, const Ray& ray, int depth) {
    if (intersection.hittedObject -> objectData.a < 0.0) return getTransparentPlaneColor(intersection, ray,depth);

    glm::vec3 rayDirection = getTransparentRayDirection(intersection, ray);
    Ray transparentRay = Ray(intersection.hit,rayDirection);
    Intersection transparencyHit = FindIntersection(transparentRay, -1);

    glm::vec4 color = (transparencyHit.hittedObject->index != intersection.hittedObject->index) ? getColor(transparencyHit,transparentRay, depth + 1) : getTransparentSelfObjectColor(intersection, transparentRay, depth);
    return glm::min(glm::vec3(color.r, color.g, color.b), glm::vec3(1.0f, 1.0f, 1.0f));
}

glm::vec3 ImageConstructor :: getTransparentPlaneColor(const Intersection& intersection, const Ray& ray, int depth) {
    Ray rayThrowPlane = Ray( intersection.hit,ray.direction);
    Intersection planeIntersection = FindIntersection(rayThrowPlane, intersection.hittedObject->index);
    if (planeIntersection.hittedObject->type == NONE) return {0,0,0};
    glm::vec4 color = getColor(planeIntersection, rayThrowPlane, depth + 1);
    return glm::min(glm::vec3(color.r, color.g, color.b), glm::vec3(1.0f, 1.0f, 1.0f));
}

bool ImageConstructor::isLightVisible( const Intersection intersection, const Light* light) {
    glm::vec3 rayDirection = normalizeVec(light->direction);
    float minT = std::numeric_limits<float>::infinity();

    if (light->type == SPOT) {
        glm::vec3 virtualSpotlightRay = normalizeVec(intersection.hit - light->position);
        if (glm::dot(virtualSpotlightRay, rayDirection) < light->angle) return false;
        rayDirection = virtualSpotlightRay;
        minT = -(glm::dot(intersection.hit, light->position)) / abs(glm::dot(-rayDirection, light->position));
    }

    for (auto & obj : configReader->getObjectsData()) {
        if (obj->index != intersection.hittedObject->index) {
            Ray ray = Ray(intersection.hit, -rayDirection);
            float t = obj->FindIntersection(ray);
            if ((t > 0) && (t < minT)) return false;
        }
    }

    return true;
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
    glm::vec3 objectNormal = intersection.hittedObject->getNormal(intersection.hit);
    glm::vec3 reflectedLightRay = normalizedRay - 2.0f * objectNormal * glm::dot(normalizedRay, objectNormal);
    glm::vec3 ray_to_viewer = normalizeVec(ray.point - intersection.hit);
    float cosAngleValue = pow(glm::max(0.0f , glm::dot(ray_to_viewer,reflectedLightRay)),intersection.hittedObject->colorAlpha);
    glm::vec3 specularColor = 0.7f * cosAngleValue * light->rgbIntensity;

    return isHittingAnObject(light,intersection,1,normalizedRay) ? specularColor : glm::vec3(0, 0, 0);
}



bool ImageConstructor::isHittingAnObject(const Light *light, const Intersection &intersection, float factor,
                                  const glm::vec3 &normlizedRay) { return glm::dot(normalizeVec(intersection.hit - light->position), factor * normlizedRay) >= light->angle; }

glm::vec3 ImageConstructor::calcNormalizeRay(const Light* light, const Intersection intersection, const float factor) {
    return (light->type == SPOT) ? factor * normalizeVec(intersection.hit - light->position): factor * normalizeVec(light->direction);
}

glm::vec4 ImageConstructor::getTransparentSelfObjectColor(Intersection intersection, Ray transparentRay, int depth) {
    float t = intersection.hittedObject->FindIntersection(transparentRay);
    glm::vec3 hitPoint = transparentRay.point + transparentRay.direction * t;

    float cosFrom = glm::dot(-intersection.hittedObject->getNormal(hitPoint), -transparentRay.direction);
    float REVERSE_SNELL = (1.5f / 1.0f);
    float cosTo = cos(asin(REVERSE_SNELL * sin(acos(cosFrom) * (180.0f / M_PI) * (M_PI / 180.0f)))) * (180.0f / M_PI);

    glm:: vec3 rayDirection = normalizeVec((REVERSE_SNELL * cosFrom - cosTo) * -intersection.hittedObject->getNormal(intersection.hit) - REVERSE_SNELL * (-transparentRay.direction));
    Ray outsideRay = Ray(hitPoint,rayDirection);

    Intersection transparencyOutside = FindIntersection(outsideRay, intersection.hittedObject->index);
    if (transparencyOutside.hittedObject->type == NONE) {
        return glm::vec4(0.f, 0.f, 0.f,0.f);
    }
    return getColor(transparencyOutside,outsideRay, depth + 1);
};

glm::vec3 ImageConstructor::getTransparentRayDirection (Intersection intersection , Ray ray) {
        float SNELL = (1.0f / 1.5f);
        float cosStartingPoint = glm::dot(intersection.hittedObject->getNormal(intersection.hit), -ray.direction);
        float sinEndingPoint = SNELL * sqrt(1.0f - cosStartingPoint * cosStartingPoint);
        float cosEndingPoint = sqrt(1.0f - sinEndingPoint * sinEndingPoint);
        return normalizeVec((SNELL * cosStartingPoint - cosEndingPoint) * intersection.hittedObject->getNormal(intersection.hit) - SNELL * (-ray.direction));
};
