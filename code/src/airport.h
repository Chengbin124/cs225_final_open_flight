#include <string>
#include <math.h>
#pragma once
class Airport{
    public:
        Airport(long double a, long double b, std::string c,std::string d){
            longitude_ = a;
            latitude_ = b;
            id_ = c;
            name_ = d;
        }
        //returns distance between two airports in miles
        long double calculateDistance(Airport other);
        long double toRadians(long double a){
            long double rad = (M_PI) / 180;
            return a / rad;
        }
        std::string getName() const{
            return name_;
        }
        bool operator<(const Airport& other) const{
            return longitude_ < other.longitude_;
        }
    private:
        long double longitude_;
        long double latitude_;
        std::string id_;
        std::string name_;
};