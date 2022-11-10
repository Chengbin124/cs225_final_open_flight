#include "vertex.h"

long double Vertex::calculateDistance(Vertex other){
    long double dlat =  = other.toRadians(other.latitude) - this -> toRadians(this -> latitude);
    long double dlong = other.toRadians(other.longitude) - this -> toRadians(this -> longitude);
    long double ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2);
    ans = 2 * asin(sqrt(ans));
    return ans * 3956;
}