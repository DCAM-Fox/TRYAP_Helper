#ifndef HPP_GREXPNODE
#define HPP_GREXPNODE
//lockguard

//вершина дерева РВ

#include <SFML/Graphics.hpp>
#include <cmath>
#include "tree.hpp"
#include "rexpnode.hpp"
#include <set> //тут реализованы множества
#include <algorithm>

class GRExpNode
{
public:
    //sf::RectangleShape line;
    std::vector<std::array<sf::Vertex, 2>> lines; //линии
    sf::CircleShape circle; //кружок
    sf::Text text;
    std::shared_ptr<Node<NData>> data; //ссылка на узел
    sf::Vector2f coords; //координаты центра
    //конструктор
    GRExpNode() { }
    //деструктор
    ~GRExpNode() { }
};


//lockguard
#endif
