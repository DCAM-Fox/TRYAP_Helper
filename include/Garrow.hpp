#ifndef HPP_GARROW
#define HPP_GARROW
//lockguard

#include <SFML/Graphics.hpp>
#include <cmath>
#include "dfa.hpp"
#include "dfstate.hpp"
#include <set> //тут реализованы множества
#include <algorithm>

//наследование: все, что доступно у Transformable b Drawable, доступно и у ArrowHead
class GArrowHead : public sf::Transformable, public sf::Drawable
{
public:
    std::vector<std::array<sf::Vertex,2>> lines;
    //конструктор
    GArrowHead();
    //деструктор
    ~GArrowHead() { }
    //метод
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class GArrow
{
public:
    //sf::RectangleShape line;
    std::vector<std::array<sf::Vertex, 2>> lines; //линии
    std::vector<GArrowHead> heads;
    std::vector<sf::Text> text; //надпись над линией
    //конструктор
    GArrow() { }
    //деструктор
    ~GArrow() { }
};

//lockguard
#endif
