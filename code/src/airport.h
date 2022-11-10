#include <string>
#include <math.h>
class Airport{
    public:
        Vertex(long double a, long double b, std::string c){
            longitude_ = a;
            latitude_ = b;
            id_ = c;
        }
        //returns distance between two airports in miles
        long double calculateDistance(Airport other);
        long double toRadians(long double a){
            long double rad = (M_PI) / 180;
            return a / rad;
        }
    private:
        long double longitude_;
        long double latitude_;
        std::string id_;
}