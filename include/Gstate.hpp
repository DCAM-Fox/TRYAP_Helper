#ifndef HPP_GSTATE
#define HPP_GSTATE
//lockguard

//вершина дерева РВ

#include <SFML/Graphics.hpp>
#include <cmath>
#include "dfa.hpp"
#include "dfstate.hpp"
#include <set> //тут реализованы множества
#include <algorithm>

class GState
{
public:
    //sf::RectangleShape line;
    //std::vector<std::array<sf::Vertex, 2>> lines; //линии
    sf::CircleShape circle; //кружок
    sf::CircleShape ring; //внутренний кружок
    std::shared_ptr<DFState> data; //ссылка на состояние
    sf::Vector2f coords; //координаты центра
    //конструктор
    GState() { }
    //деструктор
    ~GState() { }
};


//lockguard
#endif
