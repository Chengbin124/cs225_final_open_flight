#include "StickerSheet.h"
#include <vector>
using namespace std;

StickerSheet::StickerSheet(const Image& picture, unsigned max){
    picts_.push_back(new Image(picture));
    max_ = max;
};
StickerSheet::~StickerSheet(){
    for(unsigned i = picts_.size()-1; i >0;i--){
        delete picts_[i];
        picts_.pop_back();
    }
    picts_.clear();
};
StickerSheet::StickerSheet(const StickerSheet& other){
    for(unsigned i = 0; i < other.picts_.size();i++){
        picts_.push_back(new Image(*(other.picts_[i])));
    }
    max_ = other.max_;
};
int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y){
    if(x > picts_[0] -> width() || y > picts_[0] -> height()){
        return -1;
    }
    if(picts_.size() -1 < getMax()){
        picts_.push_back(new Image(sticker));
        picts_[picts_.size()-1] -> setXY(x,y);
    }
    return picts_.size()-1;
};
void StickerSheet::changeMaxStickers(unsigned max){
    max_ = max;
    while(picts_.size() > max_ + 1){
        delete picts_[picts_.size()-1];
        picts_.pop_back();
    }
};
Image* StickerSheet::getSticker(unsigned index){
    if(index + 1 >= picts_.size()){
        return NULL;
    }
    return picts_[index+1];
};
const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
    if(this == &other){
        return *this;
    }
    unsigned a = picts_.size();
    for(unsigned i = 0; i < a;i++){
        delete picts_[picts_.size()-1];
        picts_.pop_back();
    }
    picts_.clear();
    for(unsigned i = 0; i < other.getPicts().size();i++){
        Image a = *(other.picts_[i]);
        Image* b = new Image(a);
        picts_.push_back(b);
    }
    max_ = other.max_;
    return *this;
};
void StickerSheet::removeSticker(unsigned index){
    if(index >= 0 && index + 1 < picts_.size()){
        vector<Image*>::iterator it = picts_.begin() + index + 1;
        picts_.erase(it);
    }
    //delete(picts_[index]);
};
Image StickerSheet::render() const{
    Image full;
    if(picts_[0]!=NULL){
        full = *picts_[0];
    }
    for(unsigned int index = 1; index<picts_.size(); index++){
        if(picts_[index] != NULL){
            for(unsigned int i = picts_[index] -> getX(); i < full.width();i++){
                for(unsigned int j = picts_[index] ->getY(); j < full.height(); j++){
                    if(picts_[index] != NULL){
                        //std::cout<< i << " X: " << picts_[index] -> getX() << " " << j << picts_[index] -> getY() << std::endl;
                        if(i - picts_[index] -> getX() < picts_[index]->width() && j - picts_[index] -> getY() < picts_[index]->height() && picts_[index] -> getPixel(i-picts_[index] -> getX(),j-picts_[index] -> getY()).a != 0){
                            //std::cout<<"RENDER HERE " << index << " "<< i<< " "<<  j<<std::endl;
                            full.getPixel(i,j) = picts_[index] -> getPixel(i - picts_[index] -> getX(),j-picts_[index] -> getY());
                        }
                    }
                }
            }
        }
        if(picts_[index] -> getX() + picts_[index] -> width() >= full.width()|| picts_[index] -> getY() + picts_[index] -> height() >= full.height()){
            for(unsigned k = picts_[index] -> getX(); k < picts_[index] -> getX() + picts_[index] -> width(); k++){
                if(k >= full.width()){
                    full.resize(full.width()+1,full.height());
                }
                for(unsigned l = picts_[index] -> getY(); l < picts_[index] -> getY() + picts_[index] -> height(); l++){
                    if(l >= full.height()){
                        full.resize(full.width(),full.height()+1);
                    }
                if(picts_[index] -> getPixel(k - picts_[index] -> getX(),l - picts_[index] -> getY()).a != 0){
                    full.getPixel(k,l) = picts_[index] -> getPixel(k - picts_[index] -> getX(), l -picts_[index] -> getY());
                }
                }
            }
        }
    }
    return full;
};
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if(index+1 >= picts_.size() || picts_[index+1] == NULL){
        return false;
    }
    picts_[index+1] -> setXY(x,y);
    return true;
};