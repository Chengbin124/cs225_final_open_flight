/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#include <vector>
#include "Image.h"
using namespace std;
#pragma once
class StickerSheet{
    public:
        StickerSheet(const Image& picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet& other);
        
        int addSticker(Image& sticker, unsigned x, unsigned y);
        void changeMaxStickers(unsigned max);
        Image* getSticker(unsigned index);

        const StickerSheet& operator=(const StickerSheet& other);
        void removeSticker(unsigned index);
        Image render() const;
        bool translate(unsigned index, unsigned x, unsigned y);
    private:
        unsigned maxStickers;
        Image* base;
        Image** images;
        unsigned* xCoords;
        unsigned* yCoords;
        unsigned numStickers;
        void clear();
        void copy(const StickerSheet& other);
};
