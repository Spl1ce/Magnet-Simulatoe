#pragma once

const float force = 48;
const float parSize = 8;
const float minDis = sqrtf(((parSize*2)*(parSize*2))*2);

namespace dim {
    const int height = 600;
    const int width = 800;
}

namespace partColor{
    const sf::Color pos = sf::Color::Red;
    const sf::Color neg = sf::Color::Blue;
}
