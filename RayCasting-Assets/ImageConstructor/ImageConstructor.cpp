//
// Created by Yonatan Balassiano on 30/01/2024.
//

#include "ImageConstructor.h"


void ImageConstructor::constructImage(const string& fileName, const int width, const int height){
    configReader.readConfigFile(fileName, width, height);
    Image image(width, height);

    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            Ray ray = constructRayThroughPixel(x, y, configReader.getEye());
            Intersection intersection = FindIntersection(ray);
            glm::vec4 color = getColor(intersection, ray);
            image.setColorToPixel(x,y,color);
        }
    }
}

Ray ImageConstructor::constructRayThroughPixel(const int x, const int y, const glm::vec3& eye) {
    glm::vec3 topLeftCorner, hitVector;
    topLeftCorner = glm::vec3(-1 + (configReader.getImageWidth() / 2), 1 - (configReader.getImageHeight() / 2), 0);
    hitVector = topLeftCorner + glm::vec3(x * configReader.getImageHeight(), -1 * (y * configReader.getImageWidth()), 0);
    return {eye, normalizeVec(hitVector - eye)};
}


Intersection ImageConstructor::FindIntersection(const Ray& ray) {
        float minT = INFINITY;
        Object* minPrimitive = nullptr;
        vector<Object*> objects = configReader.getObjectsData();
        for (auto & object : objects) {
            float t = object-> FindIntersection(ray);
            if (t < minT) {
                minT = t;
                minPrimitive = object;
            }
        }
        return {minPrimitive, ray.direction + ray.point * minT};
}

glm::vec4 ImageConstructor::getColor(const Intersection& intersection, const Ray& ray) {
    glm::vec3 color = calcEmissionColor() + calcAmbientColor();
    for (auto & light : configReader.getLightData()) {
        Ray lightRay = constructRayToLight(light, intersection);
        if (isLightVisible(lightRay,light)) {
            color += calcDiffuseColor(light, intersection);
            color += calcSpecularColor(light, intersection);
        }
    }
    return glm::vec4( color.r,color.g ,color.b, 0.0 );
}

//todo: implement
glm::vec3 ImageConstructor::calcAmbientColor() {
    return {0,0,0};
}

//todo: implement
glm::vec3 ImageConstructor::calcEmissionColor() {
    return {0,0,0};
}

//todo: implement
bool ImageConstructor::isLightVisible(const Ray lightRay,const Light* light){
    return true;
}

//todo: implement
Ray ImageConstructor::constructRayToLight(const Light* light, Intersection intersection) {
    return {intersection.hit, normalizeVec(light->position - intersection.hit)};
}

//todo: implement
glm::vec3  ImageConstructor::calcDiffuseColor(const Light* light, const Intersection intersection){
    return {0,0,0};
}

//todo: implement
glm::vec3 ImageConstructor::calcSpecularColor(const Light* light, const Intersection) {
    return {0,0,0};
}







