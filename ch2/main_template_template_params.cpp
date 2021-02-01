#include "template_template_params.hpp"

#include <list>

int main(int argc, char** argv)
{
    // Phonebook pb;
    // pb.add("police", "110");
    // pb.add("fire", "119");
    // pb.add("weather", "177");
    // pb.print(std::cout);

    Phonebook<std::list> pb;
    pb.add("police", "110");
    pb.add("fire", "119");
    pb.add("weather", "177");
    pb.print(std::cout);

    return 0;
}