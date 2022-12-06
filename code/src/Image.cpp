    #include "Image.h"
    #include "../lib/cs225/HSLAPixel.h"
    #include <cmath>
    using namespace cs225;
    
    void Image::lighten(){
        for(unsigned int i = 0; i< this->width(); i++){
            for(unsigned int j = 0; j < this->height(); j++){
                HSLAPixel& temp = this->getPixel(i,j);
                if(temp.l + 0.1 < 1.0){
                    temp.l += 0.1;
                }
                else if(temp.l + 0.1 >= 1){
                    temp.l = 1;
                }
            }
        }
    };
    void Image::lighten(double amount){
        for(unsigned int i = 0; i< this->width(); i++){
            for(unsigned int j = 0; j < this->height(); j++){
                HSLAPixel& temp = this->getPixel(i,j);
                if(temp.l < 1.0 - amount){
                    temp.l += amount;
                }
                else if(temp.l + amount >= 1 ){
                    temp.l = 1;
                }
            }
        }
    };
    void Image::darken(){
        for(unsigned int i = 0; i< this->width(); i++){
            for(unsigned int j = 0; j < this->height(); j++){
                HSLAPixel& temp = this->getPixel(i,j);
                if(temp.l - 0.1 > 0.0){
                    temp.l -= 0.1;
                }
                else if(temp.l - 0.1 <= 0){
                    temp.l = 0;
                }
            }
        }
    };
    void Image::darken(double amount){
        for(unsigned int i = 0; i< this->width(); i++){
            for(unsigned int j = 0; j < this->height(); j++){
                HSLAPixel& temp = this->getPixel(i,j);
                if(temp.l - amount > 0.0){
                    temp.l -= amount;
                }
                else if(temp.l - amount <= 0.0){
                    temp.l = 0;
                }
            }
        }
    };
    void Image::saturate(){
        for(unsigned int i = 0; i< this->width(); i++){
            for(unsigned int j = 0; j < this->height(); j++){
                HSLAPixel& temp = this->getPixel(i,j);
                if(temp.s + 0.1 < 1){
                    temp.s += 0.1;
                }
                else if(temp.s + 0.1 >= 1){
                    temp.s = 1;
                }
            }
        }
    };
    void Image::saturate(double amount){
        for(unsigned int i = 0; i< this->width(); i++){
            for(unsigned int j = 0; j < this->height(); j++){
                HSLAPixel& temp = this->getPixel(i,j);
                if(temp.s + amount < 1){
                    temp.s += amount;
                }
                else if(temp.s + amount >= 1){
                    temp.s = 1;
                }
            }
        }
    };
    void Image::desaturate(){
        for(unsigned int i = 0; i< this->width(); i++){
            for(unsigned int j = 0; j < this->height(); j++){
                HSLAPixel& temp = this->getPixel(i,j);
                if(temp.s - 0.1 > 0.0){
                    temp.s -= 0.1;
                }
                else if(temp.s - 0.1 <= 0.0){
                    temp.s = 0;
                }
            }
        }
    };
    void Image::desaturate(double amount){
        for(unsigned int i = 0; i< this->width(); i++){
            for(unsigned int j = 0; j < this->height(); j++){
                HSLAPixel& temp = this->getPixel(i,j);
                if(temp.s - amount > 0.0){
                    temp.s -= amount;
                }
                else if(temp.s - amount <= 0.0){
                    temp.s = 0.0;
                }
            }
        }
    };
    void Image::grayscale(){
        for(unsigned int i = 0; i< this->width(); i++){
            for(unsigned int j = 0; j < this->height(); j++){
                HSLAPixel& temp = this->getPixel(i,j);
                temp.s = 0;
            }
        }
    };
    void Image::rotateColor(double degrees){
        for(unsigned int i = 0; i < this->width();i++){
            for(unsigned int j = 0; j < this->height(); j++){
                HSLAPixel& temp = this->getPixel(i,j);
                temp.h = temp.h + degrees;
                while(temp.h > 360){
                    temp.h = temp.h - 360;
                }
                while(temp.h < 0){
                    temp.h = temp.h + 360;
                }
            }
        }
    };
    void Image::illinify(){
        for(unsigned int i = 0; i < this->width(); i++){
            for(unsigned int j = 0; j < this->height(); j++){
                HSLAPixel& temp = this->getPixel(i,j);
                if(fabs(temp.h - 11) > fabs(temp.h -216)){
                    temp.h = 216;
                }
                else{
                    temp.h = 11;
                }
            }
        }
    };
    void Image::scale(double factor){
        PNG* copy = new PNG(*this);
        this->resize((unsigned)(this->width()*factor), (unsigned)(this->height()* factor));
        for(unsigned int i = 0; i < this->width();i ++){
            for(unsigned int j = 0; j < this->height(); j++){
                this->getPixel(i,j) = copy->getPixel((unsigned)(floor(i/factor)),(unsigned)(floor(j/factor)));
            }
        }
        delete(copy);
    };
    void Image::scale(unsigned w, unsigned h){
        double newWidth = (double)w / (double)width();
        double newHeight = (double)h / (double)height();
        //trying < instead of >
        (newHeight < newWidth)?scale(newHeight):scale(newWidth);
    };
    void Image::setXY(unsigned x, unsigned y){
        x_ = x;
        y_ = y;
    };
    unsigned Image::getX(){
        return x_;
    }
    unsigned Image::getY(){
        return y_;
    }