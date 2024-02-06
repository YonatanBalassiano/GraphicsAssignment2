//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_IMAGECONSTRACTOR_H
#define GAME_IMAGECONSTRACTOR_H

#include <vector>
#include <string>
#include "../Components/Image.h"
#include "../Reader/ConfigReader.h"
#include "../Components/Intersection.h"




using namespace std;


class ImageConstructor {
private:
    ConfigReader *configReader;
    Ray constructRayThroughPixel(const int x, const int y,const glm::vec3& eye);
    Intersection FindIntersection(const Ray& ray, int index);
    glm::vec4 getColorOld(Intersection hit,Ray ray, int depth);
    glm::vec4 getColor(const Intersection& intersection, const Ray& ray, int depth);
    glm::vec3 calcEmissionColor();
    glm::vec3 calcAmbientColor();
    bool isLightVisible(const Ray lightRay,const Light* light);
    Ray constructRayToLight(const Light* light, Intersection intersection);
    glm::vec3 calcDiffuseColor(const Light* light, const Intersection intersection);
    glm::vec3 calcSpecularColor(const Ray ray,const Light* light, const Intersection);
    glm::vec3 normalizeRay(const Light* light, const Intersection, const float factor);
    glm::vec3 GetColorRegular(const Intersection& intersection, const Ray& ray);
    glm::vec3 GetColorReflective(const Intersection& intersection, const Ray& ray,int depth);
    glm::vec3 GetColorTransparent(const Intersection& intersection, const Ray& ray, int depth);
    float calcShadow( const Intersection intersection, const Light* light);
    glm::vec3 getTransparentPlaneColor(const Intersection& intersection,  const Ray& ray, int depth);

public:
    ImageConstructor() = default;
    ~ImageConstructor() = default;
    Image constructImage(const string& fileName, int width, const int height);
    glm::vec3 calcNormalizeRay (const Light* light, const Intersection intersection, const float factor);
    bool isHittingAnObject(const Light *light, const Intersection &intersection, float factor, const glm::vec3 &normlizedRay) const;
    Image getImage();
};
#endif //GAME_IMAGECONSTRACTOR_H
