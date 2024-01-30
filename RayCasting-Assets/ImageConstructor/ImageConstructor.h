//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_IMAGECONSTRACTOR_H
#define GAME_IMAGECONSTRACTOR_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "../Components/Image.h"
#include "../Reader/ConfigReader.h"
#include "../Components/Intersection.h"



using namespace std;


class ImageConstructor {
private:
    ConfigReader configReader;
    Ray constructRayThroughPixel(const int x, const int y,const glm::vec3& eye);
    Intersection FindIntersection(const Ray& ray);
    glm::vec4 getColor(const Intersection& intersection, const Ray& ray);
    glm::vec3 calcEmissionColor();
    glm::vec3 calcAmbientColor();
    bool isLightVisible(const Ray lightRay,const Light* light);
    Ray constructRayToLight(const Light* light, Intersection intersection);
    glm::vec3 calcDiffuseColor(const Light* light, const Intersection intersection);
    glm::vec3 calcSpecularColor(const Light* light, const Intersection);

public:
    ImageConstructor() = default;
    ~ImageConstructor() = default;
    void constructImage(const string& fileName, const int width, const int height);
};
#endif //GAME_IMAGECONSTRACTOR_H
