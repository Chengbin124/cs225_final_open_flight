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
        vector<Image*> getPicts() const{
            return picts_;
        }
        unsigned getMax() const{
            return max_;
        }
        Image* getPic(unsigned index) const{
            return picts_[index];
        }
    private:
        vector<Image*> picts_;
        unsigned max_;
};