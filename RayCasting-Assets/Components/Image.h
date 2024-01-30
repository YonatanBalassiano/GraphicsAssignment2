//
// Created by Yonatan Balassiano on 30/01/2024.
//

#ifndef GAME_IMAGE_H
#define GAME_IMAGE_H

#include <string>
#include "glm/detail/type_vec4.hpp"

using namespace std;

class Image {
public:
    unsigned char* data;
    int width, height;
    Image(int width, int height);
    void setColorToPixel(int x, int y, const glm::vec4& color) const;
    ~Image() = default;

};



#endif //GAME_IMAGE_H
