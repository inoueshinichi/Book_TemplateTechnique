#include "specialize_template_by_concept.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    // Geoライブラリの点型に対してdistanceを使用する
    {
        geo::point p1(0.0, 0.0);
        geo::point p2(3.0, 3.0);
        double d = distance(p1, p2); 
        std::cout << d << std::endl;
    }
    {
        std::pair<double, double> p1(0.0, 0.0);
        std::pair<double, double> p2(3.0, 3.0);
        double d = distance(p1, p2); 
        std::cout << d << std::endl;
    }
    
    return 0;
}