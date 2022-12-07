#include "StickerSheet.h"
#include <vector>
using namespace std;

StickerSheet::StickerSheet(const Image& picture, unsigned max) {
    maxStickers = max;

    base = new Image(picture);

    images = new Image*[maxStickers];
    for (unsigned i = 0; i < maxStickers; i++) {
        images[i] = nullptr;
    }

    xCoords = new unsigned[maxStickers];
    yCoords = new unsigned[maxStickers];
    numStickers = 0;
}

StickerSheet::~StickerSheet() {
    clear();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    copy(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other) {
    if (this == &other) {
        return *this;
    }

    clear();
    copy(other);

    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max == maxStickers) {
        return;
    }

    Image** temp = new Image*[max];
    unsigned* xTemp = new unsigned[max];
    unsigned* yTemp = new unsigned[max];

    if (max < maxStickers) {
        for (unsigned i = 0; i < max; i++) {
            temp[i] = images[i];
            images[i] = nullptr;

            xTemp[i] = xCoords[i];
            yTemp[i] = yCoords[i];
        }
    } else {
        for (unsigned i = 0; i < maxStickers; i++) {
            temp[i] = images[i];
            images[i] = nullptr;

            xTemp[i] = xCoords[i];
            yTemp[i] = yCoords[i];
        }
    }

    for (unsigned i = 0; i < maxStickers; i++) {
        if (images[i] != nullptr) {
            delete images[i];
            images[i] = nullptr;
        }
    }

    delete[] images;
    images = new Image*[max];

    for (unsigned i = 0; i < max; i++) {
        images[i] = nullptr;
    }

    delete[] xCoords;
    xCoords = new unsigned[max];

    delete[] yCoords;
    yCoords = new unsigned[max];

    if (max < maxStickers) {
        for (unsigned i = 0; i < max; i++) {
            images[i] = temp[i];
            temp[i] = nullptr;

            xCoords[i] = xTemp[i];
            yCoords[i] = yTemp[i];
        }

        numStickers = max;
    } else {
        for (unsigned i = 0; i < maxStickers; i++) {
            images[i] = temp[i];
            temp[i] = nullptr;
            
            xCoords[i] = xTemp[i];
            yCoords[i] = yTemp[i];
        }
    }

    maxStickers = max;

    delete[] temp;
    delete[] xTemp;
    delete[] yTemp;

    temp = nullptr;
    xTemp = nullptr;
    yTemp = nullptr;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    if (numStickers < maxStickers) {
        for (unsigned i = 0; i < maxStickers; i++) {
            if (images[i] == nullptr) {
                images[i] = new Image(sticker);
                xCoords[i] = x;
                yCoords[i] = y;
                numStickers++;
                return i;
            }
        }
    }

    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < maxStickers) {
        if (images[index] != nullptr) {
            xCoords[index] = x;
            yCoords[index] = y;
            return true;
        }
    }

    return false;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < maxStickers && index >= 0) {
        delete images[index];
        images[index] = nullptr;

        if (maxStickers > 1) {
            unsigned nextIndex = index + 1;
            unsigned currIndex = index;
            while (nextIndex == maxStickers - 1 || images[nextIndex] != nullptr) {
                images[currIndex] = new Image(*images[nextIndex]);
                xCoords[currIndex] = xCoords[nextIndex];
                yCoords[currIndex] = yCoords[nextIndex];

                delete images[nextIndex];
                images[nextIndex] = nullptr;

                xCoords[nextIndex] = 0;
                yCoords[nextIndex] = 0;

                currIndex++;
                nextIndex++;
            }
        }
        

        numStickers--;
    }
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index < maxStickers) {
        return images[index];
    }

    return nullptr;
}

Image StickerSheet::render() const {
    Image stickersheet(*base);
    unsigned xMax = stickersheet.width();
    unsigned yMax = stickersheet.height();

    for (unsigned i = 0; i < numStickers; i++) {
        if (images[i] != nullptr) {
            unsigned x = xCoords[i] + images[i]->width();
            unsigned y = yCoords[i] + images[i]->height();

            if (x > xMax) {
                xMax = x;
            }

            if (y > yMax) {
                yMax = y;
            }
        }
    }

    stickersheet.resize(xMax, yMax);

    for (unsigned i = 0; i < numStickers; i++) {
        if (images[i] != nullptr) {
            for (unsigned x = xCoords[i]; x < (xCoords[i] + images[i]->width()); x++) {
                for (unsigned y = yCoords[i]; y < (yCoords[i] + images[i]->height()); y++) {
                    HSLAPixel& basePixel = stickersheet.getPixel(x, y);
                    HSLAPixel& finalPixel = images[i]->getPixel(x - xCoords[i], y - yCoords[i]);
                    
                    if (finalPixel.a != 0) {
                        basePixel.h = finalPixel.h;
                        basePixel.s = finalPixel.s;
                        basePixel.l = finalPixel.l;
                        basePixel.a = finalPixel.a;
                    }
                }
            }
        }
    }

    return stickersheet;
}

void StickerSheet::clear() {
    for (unsigned i = 0; i < maxStickers; i++) {
        if (images[i] != nullptr) {
            delete images[i];
            images[i] = nullptr;
        }
    }

    delete[] images;
    delete[] xCoords;
    delete[] yCoords;
    delete base;

    images = nullptr;
    xCoords = nullptr;
    yCoords = nullptr;
    base = nullptr;
    numStickers = 0;
}

void StickerSheet::copy(const StickerSheet& other) {
    maxStickers = other.maxStickers;

    base = new Image(*(other.base));

    images = new Image*[maxStickers];
    for (unsigned i = 0; i < maxStickers; i++) {
        images[i] = nullptr;
    }

    xCoords = new unsigned[maxStickers];
    yCoords = new unsigned[maxStickers];
    numStickers = other.numStickers;

    for (unsigned i = 0; i < maxStickers; i++) {
        if (other.images[i] != nullptr) {
            images[i] = new Image(*(other.images[i]));
            xCoords[i] = other.xCoords[i];
            yCoords[i] = other.yCoords[i];
        }
    }
}
