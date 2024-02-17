//
// Created by Yonatan Balassiano on 30/01/2024.
//
#include "Image.h"

#include "glm/glm.hpp"

Image::Image(int width, int height) {
    this->width = width;
    this->height = height;
    data = new unsigned char[width * height * 4];
}

void Image::setColorToPixel(int x, int y, const glm::vec4& color) const {
    int baseIndex = (this->width * x + y) * 4;
    data[baseIndex] = static_cast<unsigned char>(color.r * 255);
    data[baseIndex + 1] = static_cast<unsigned char>(color.g * 255);
    data[baseIndex + 2] = static_cast<unsigned char>(color.b * 255);
    data[baseIndex + 3] = static_cast<unsigned char>(color.a * 255);
}
