#include <string>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/detail/type_vec4.hpp"
#include "../Light/Light.h"
#include "../Object/Object.h"


using namespace std;

class ConfigReader
{
private:
    void objectMaker(const float lineData[4], objectTypes type);
    void setColorsToObjects();
    void setSpotlightPosition();
    vector<vector<string>> sceneData;
    float boundFlag;
    glm::vec3 eye;
    glm::vec4 ambient;
    vector<Light *> lightData;
    vector<glm::vec4> positionData;
    vector<glm::vec4> intensityData;
    vector<Object *> objectsData;
    vector<glm::vec4> colorsData;
    float pixelWidth , pixelHeight;
    int imageWidth, imageHeight;

public :
    void readFile (string fileName,int width, int height);
    const vector<vector<string>> &getSceneData() const;
    float getBoundFlag() const;
    const glm::vec3 &getEye() const;
    const glm::vec4 &getAmbient() const;
    const vector<Light *> &getLightData() const;
    const vector<glm::vec4> &getPositionData() const;
    const vector<glm::vec4> &getIntensityData() const;
    const vector<Object *> &getObjectsData() const;
    const vector<glm::vec4> &getColorsData() const;
    float getPixelWidth() const;
    float getPixelHeight() const;
    int getImageWidth() const;
    int getImageHeight() const;

};