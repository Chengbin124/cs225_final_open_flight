#include "Image.h"
#include "../lib/cs225/HSLAPixel.h"
#include <cmath>

using namespace cs225;
    
void Image::lighten() {
    for (unsigned int w = 0; w < this->width(); w++) {
        for (unsigned int h = 0; h < this->height(); h++) {
            HSLAPixel& pixel = this->getPixel(w, h);
            pixel.l += 0.1;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int w = 0; w < this->width(); w++) {
        for (unsigned int h = 0; h < this->height(); h++) {
            HSLAPixel& pixel = this->getPixel(w, h);
            pixel.l += amount;
            if (pixel.l > 1) {
                pixel.l = 1;
            }
        }
    }
}

void Image::darken() {
    for (unsigned int w = 0; w < this->width(); w++) {
        for (unsigned int h = 0; h < this->height(); h++) {
            HSLAPixel& pixel = this->getPixel(w, h);
            pixel.l -= 0.1;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int w = 0; w < this->width(); w++) {
        for (unsigned int h = 0; h < this->height(); h++) {
            HSLAPixel& pixel = this->getPixel(w, h);
            pixel.l -= amount;
            if (pixel.l < 0) {
                pixel.l = 0;
            }
        }
    }
}

void Image::saturate() {
    for (unsigned int w = 0; w < this->width(); w++) {
        for (unsigned int h = 0; h < this->height(); h++) {
            HSLAPixel& pixel = this->getPixel(w, h);
            pixel.s += 0.1;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int w = 0; w < this->width(); w++) {
        for (unsigned int h = 0; h < this->height(); h++) {
            HSLAPixel& pixel = this->getPixel(w, h);
            pixel.s += amount;
            if (pixel.s > 1) {
                pixel.s = 1;
            }
        }
    }
}

void Image::desaturate() {
    for (unsigned int w = 0; w < this->width(); w++) {
        for (unsigned int h = 0; h < this->height(); h++) {
            HSLAPixel& pixel = this->getPixel(w, h);
            pixel.s -= 0.1;
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for (unsigned int w = 0; w < this->width(); w++) {
        for (unsigned int h = 0; h < this->height(); h++) {
            HSLAPixel& pixel = this->getPixel(w, h);
            pixel.s -= amount;
            if (pixel.s < 0) {
                pixel.s = 0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned int w = 0; w < this->width(); w++) {
        for (unsigned int h = 0; h < this->height(); h++) {
            HSLAPixel& pixel = this->getPixel(w, h);
            pixel.s -= 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int w = 0; w < this->width(); w++) {
        for (unsigned int h = 0; h < this->height(); h++) {
            HSLAPixel& pixel = this->getPixel(w, h);
            pixel.h += degrees;
            if (pixel.h > 360) {
                pixel.h -= 360;
            } else if (pixel.h < 0) {
                pixel.h += 360;
            }
        }
    }
}

void Image::scale(double factor) {
    PNG* copy = new PNG(*this);
    this->resize((unsigned)(this->width()*factor), (unsigned)(this->height()* factor));
    for (unsigned int i = 0; i < this->width();i ++) {
        for (unsigned int j = 0; j < this->height(); j++) {
            this->getPixel(i,j) = copy->getPixel((unsigned)(floor(i/factor)),(unsigned)(floor(j/factor)));
        }
    }
    delete(copy);
}

void Image::scale(unsigned w, unsigned h) {
    double newWidth = (double)w / (double)width();
    double newHeight = (double)h / (double)height();
    //trying < instead of >
    (newHeight < newWidth)?scale(newHeight):scale(newWidth);
}

void Image::setXY(unsigned x, unsigned y) {
    x_ = x;
    y_ = y;
}

unsigned Image::getX(){
    return x_;
}
    
unsigned Image::getY(){
    return y_;
}
