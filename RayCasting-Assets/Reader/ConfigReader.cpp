#include "ConfigReader.h"
#include "../Light/SpotLight.h"
#include "../Light/DirectionalLight.h"
#include "../Object/Sphere.h"
#include "../Object/Plane.h"


#include <fstream>
#include <vector>
#include <sstream>


void ConfigReader::readConfigFile(string fileName, const int width,const int height){
    int index = -1;
    string currentLine, currentArgInLine;
    vector<string> lineValues;
    ifstream sceneFile(fileName);

    while (getline(sceneFile, currentLine)) {
        stringstream textLineStream(currentLine);

        while (getline(textLineStream, currentArgInLine, ' ')) {
            lineValues.push_back(currentArgInLine);

            if (++index % 5 == 4) {
                sceneData.push_back(lineValues);
                lineValues.clear();
            }
        }
    }

    for (auto & i : sceneData){
        float lineData[4] = {stof(i[1]), stof(i[2]), stof(i[3]),
                             stof(i[4])};
        char lineChar = i[0][0];
        switch (lineChar) {
            case 'e' : {
                eye = glm::vec3(lineData[0], lineData[1], lineData[2]);
                boundFlag = lineData[3];
                break;
            }
            case 'a' : {
                ambient = glm::vec4(lineData[0], lineData[1], lineData[2], lineData[3]);
                break;
            }
            case 'd' : {
                lineData[3] > 0 ? lightData.push_back(new SpotLight(glm::vec3(lineData[0], lineData[1], lineData[2]))) :
                    lightData.push_back(new DirectionalLight(glm::vec3(lineData[0], lineData[1], lineData[2])));
                break;
            }
            case 'p' : {
                positionData.emplace_back(lineData[0], lineData[1], lineData[2], lineData[3]);
                break;
            }
            case 'i' : {
                intensityData.emplace_back(lineData[0], lineData[1], lineData[2], lineData[3]);
                break;
            }
            case 'o' : {
                objectMaker(lineData, REGULAR);
                break;
            }
            case 'r' : {
                objectMaker(lineData, REFLECTIVE);
                break;
            }
            case 't' : {
                objectMaker(lineData, TRANSPARENT);
                break;
            }
            case 'c' : {
                colorsData.emplace_back(lineData[0], lineData[1], lineData[2], lineData[3]);
                break;
            }
        }

        setColorsToObjects();
        setSpotlightPosition();

        pixelWidth = 2.0 / float(width);
        pixelHeight = 2.0 / float(height);
        imageWidth = width;
        imageHeight = height;
    }
};


void ConfigReader::objectMaker( const float lineData[4], const objectTypes type)  {
        lineData[3] > 0 ? objectsData.push_back(new Sphere({lineData[0], lineData[1], lineData[2], lineData[3]}, type))
                        : objectsData.push_back(new Plane({lineData[0], lineData[1], lineData[2], lineData[3]}, type));
};

void ConfigReader::setColorsToObjects(){
    for (int i = 0; i < objectsData.size(); i++) {
        objectsData[i]-> index = i;
        objectsData[i]-> setColor(colorsData[i]);
    }
};

void ConfigReader::setSpotlightPosition() {
    int positionIndex = 0;
    for (int i = 0; i < lightData.size(); i++) {
        if (lightData[i]->type == SPOT) {
            glm::vec4 currPosition = positionData[positionIndex++];
            glm::vec3 point = glm::vec3(currPosition.x, currPosition.y, currPosition.z);
            lightData[i]-> position = point;
            lightData[i]-> angle = currPosition.w;
        }
        lightData[i]->setIntensity(intensityData[i]);
    }
}

const vector<vector<string>> &ConfigReader::getSceneData() const {
    return sceneData;
}

float ConfigReader::getBoundFlag() const {
    return boundFlag;
}

const glm::vec3 &ConfigReader::getEye() const {
    return eye;
}

const glm::vec4 &ConfigReader::getAmbient() const {
    return ambient;
}

const vector<Light *> &ConfigReader::getLightData() const {
    return lightData;
}

const vector<glm::vec4> &ConfigReader::getPositionData() const {
    return positionData;
}

const vector<glm::vec4> &ConfigReader::getIntensityData() const {
    return intensityData;
}

const vector<Object *> &ConfigReader::getObjectsData() const {
    return objectsData;
}

const vector<glm::vec4> &ConfigReader::getColorsData() const {
    return colorsData;
}

float ConfigReader::getPixelWidth() const {
    return pixelWidth;
}

float ConfigReader::getPixelHeight() const {
    return pixelHeight;
}

int ConfigReader::getImageWidth() const {
    return imageWidth;
}

int ConfigReader::getImageHeight() const {
    return imageHeight;
}
