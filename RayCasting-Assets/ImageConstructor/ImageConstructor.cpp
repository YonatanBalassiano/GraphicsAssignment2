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
            Ray ray = constructRayThroughPixel(x, y, configReader->getEye());
            Intersection intersection = FindIntersection(ray, -1);
            glm::vec4 color = getColor(intersection, ray, 0);
            image.setColorToPixel(x, y, color);
        }
    }
    return image;
}

Ray ImageConstructor::constructRayThroughPixel(const int x, const int y, const glm::vec3& eye) {
    float width = configReader->getPixelWidth();
    float height = configReader->getPixelHeight();    

    glm::vec3 hit = glm::vec3(-1+(width / 2), 1-(height / 2), 0) + glm::vec3(y*width, -1*(x * height), 0);
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

float DegreesToRadians(float deg) {
    return deg * (M_PI/180);
}

float RadiansToDegrees(float rad) {
    return rad * (180/M_PI);
}

glm::vec3 calcTransparency(float snell, const Intersection& intersection, const Ray& ray, int depth) {

    float cosTheta_i = glm::dot(intersection.hittedObject->getNormal(intersection.hit), -ray.direction);
    float theta_i = RadiansToDegrees(acos(cosTheta_i));
    float sinTheta_i = sin(DegreesToRadians(theta_i));
    float sinTheta_r = snell * sinTheta_i;
    float theta_r = RadiansToDegrees(asin(sinTheta_r));
    float cosTheta_r = cos(DegreesToRadians(theta_r));

    glm::vec3 N = intersection.hittedObject->getNormal(intersection.hit);
    if (snell > 1) N = -N; 
    glm::vec3 L = -ray.direction;

    glm::vec3 T = (snell * cosTheta_i - cosTheta_r) * N - snell * L;
    return normalizeVec(T);

}

glm::vec3 ImageConstructor::GetColorTransparent(const Intersection& intersection, const Ray& ray, int depth){
    glm::vec4 transColor = glm::vec4(0, 0, 0, 0);
    float snell = (1 / 1.5);
    glm::vec3 rayInDirection = calcTransparency(snell, intersection, ray, depth);
    Ray rayIn = Ray(intersection.hit, rayInDirection);

    Intersection transparencyInter = FindIntersection(rayIn, -1);

    if (transparencyInter.hittedObject->index != intersection.hittedObject->index) {
        transColor = getColor(transparencyInter, rayIn, depth+1);
    }
    else {
        glm::vec3 secondInter = rayIn.point + rayIn.direction * (intersection.hittedObject->FindIntersection(rayIn));
        glm::vec3 rayOutDirection = calcTransparency(1 / snell, intersection, rayIn, depth);
        Ray rayOut = Ray(secondInter, rayOutDirection);

        Intersection transparencyHitOut = FindIntersection(rayOut, intersection.hittedObject->index);

        if (transparencyHitOut.hittedObject->type == NONE) {
            return glm::vec3(0, 0, 0);
        }

        transColor = getColor(transparencyHitOut,rayOut, depth + 1);
    }
    return glm::min({transColor.r, transColor.g, transColor.b}, glm::vec3(1, 1, 1));
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
