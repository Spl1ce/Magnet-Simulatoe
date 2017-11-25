#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Consts.h"

struct particalParts
{
    bool state = false ; // True Positive
    sf::Vector2f pos = sf::Vector2f(0,0);
    sf::Vector2f vel = sf::Vector2f(0,0);
};

class Particals
{
// Vars
public:
    std::vector<particalParts> parts;
    unsigned int partSize = 0;

    bool wrap = false;

private:
    sf::Vertex temp[4];
    sf::VertexArray drawArray = sf::VertexArray(sf::Quads, 0);

// Functions
public:
    Particals();
    virtual ~Particals();

    void addPart(bool state, sf::Vector2i pos);
    void reset();
    void update(float fps, sf::RenderWindow &win);

private:
    float findDistance(sf::Vector2f pos1, sf::Vector2f pos2);
    float findRatio(sf::Vector2f pos1, sf::Vector2f pos2);
};
