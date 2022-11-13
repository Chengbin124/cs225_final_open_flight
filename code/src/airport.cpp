#include "airport.h"

long double Airport::calculateDistance(Airport other){
    long double dlat  = other.toRadians(other.latitude_) - this -> toRadians(this -> latitude_);
    long double dlong = other.toRadians(other.longitude_) - this -> toRadians(this -> longitude_);
    long double ans = pow(sin(dlat / 2), 2) + cos(other.toRadians(other.latitude_)) * cos(this -> toRadians(this -> latitude_)) * pow(sin(dlong / 2), 2);
    ans = 2 * asin(sqrt(ans));
    return ans * 3956;
}