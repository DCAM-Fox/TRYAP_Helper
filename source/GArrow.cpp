#include "Garrow.hpp"

GArrowHead::GArrowHead()
{
    lines.push_back(std::array<sf::Vertex,2>());
    lines.push_back(std::array<sf::Vertex,2>());
    lines.push_back(std::array<sf::Vertex,2>());

    lines[0][0] = sf::Vertex(sf::Vector2f(0.0f, 0.0f));
    lines[0][1] = sf::Vertex(sf::Vector2f(20.0f, 0.0f));
    lines[1][0] = sf::Vertex(sf::Vector2f(0.0f, 0.0f));
    lines[1][1] = sf::Vertex(sf::Vector2f(12.0f, 6.0f));
    lines[2][0] = sf::Vertex(sf::Vector2f(0.0f, 0.0f));
    lines[0][1] = sf::Vertex(sf::Vector2f(12.0f, -6.0f));
}

void GArrowHead::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Применение трансформации.
    states.transform *= getTransform();

    target.draw(lines[0].data(), 2, sf::Lines, states);
    target.draw(lines[1].data(), 2, sf::Lines, states);
    target.draw(lines[2].data(), 2, sf::Lines, states);
}
