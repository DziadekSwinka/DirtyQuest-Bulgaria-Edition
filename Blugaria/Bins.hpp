#ifndef BINS_HPP_INCLUDED
#define BINS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

class Bin_handling;

class bins
{
private:
    sf::RenderWindow &window;

public:
    std::vector<Bin_handling>BINS;
    bins(sf::RenderWindow &window1):window(window1)
    {
    }
};

class Bin_handling
{
private:

public:
    enum
    {

    }type;
};
#endif // BINS_HPP_INCLUDED
