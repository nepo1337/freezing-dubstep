#include <iostream>
#include <SFML/System.hpp>

int main(int argc, char **argv)
{
   sf::Clock clock;
   std::cout << clock.getElapsedTime().asSeconds()<<std::endl;
    return 0;
}
