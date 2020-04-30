#ifndef HPP_REXP_NODE
#define HPP_REXP_NODE
//lockguard

//вершина дерева РВ

#include "tree.hpp"
#include <set> //тут реализованы множества
#include <algorithm>

struct NData
{
    /*
      bool is_calc = false; //посчитали уже?
    */
    bool is_nullable;

    std::set<size_t> firstpos;
    std::set<size_t> lastpos;
    
    //перечисляемый тип
    enum class Type
    {
        Char,
        Conc,
        Union,
        Iter
    };
    Type type; //а здесь оно хранится
};

/*
Node<NData> //создает вершину с NData вместо T
*/

void calculate(Node<NData>& place)
{
    switch(place.value.type)
    {
        case NData::Type::Char:
        {
            place.value.is_nullable = false;
            break;
        }
        case NData::Type::Conc:
        {
            /*begin возвращает итератор на указатель, его разыменовываем*/
            std::shared_ptr<Node<NData>> c1 = *(place.children.begin());
            std::shared_ptr<Node<NData>> c2 = *(++place.children.begin());
            /*вычисляем firstpos*/
            if (c1->value.is_nullable)
            {
                std::set_union(c1->value.firstpos.begin(), c1->value.firstpos.end(),
                               c2->value.firstpos.begin(), c2->value.firstpos.end(),
                               std::inserter(place.value.firstpos, place.value.firstpos.begin()));
            }
            else
            {
                place.value.firstpos = c1->value.firstpos;
            }
            /*вычисляем lastpos*/
            if (c2->value.is_nullable)
            {
                std::set_union(c1->value.lastpos.begin(), c1->value.lastpos.end(),
                               c2->value.lastpos.begin(), c2->value.lastpos.end(),
                               std::inserter(place.value.lastpos, place.value.lastpos.begin()));
            }
            else
            {
                place.value.lastpos = c1->value.lastpos;
            }
            /*вычисляем nullable*/
            place.value.is_nullable = c1->value.is_nullable && c2->value.is_nullable;
            break;
        }
        case NData::Type::Union:
        {
            /*begin возвращает итератор на указатель, его разыменовываем*/
            std::shared_ptr<Node<NData>> c1 = *(place.children.begin());
            std::shared_ptr<Node<NData>> c2 = *(++place.children.begin());
            /*вычисляем firstpos*/
            std::set_union(c1->value.firstpos.begin(), c1->value.firstpos.end(),
                           c2->value.firstpos.begin(), c2->value.firstpos.end(),
                           std::inserter(place.value.firstpos, place.value.firstpos.begin()));
            /*вычисляем lastpos*/
            std::set_union(c1->value.lastpos.begin(), c1->value.lastpos.end(),
                           c2->value.lastpos.begin(), c2->value.lastpos.end(),
                           std::inserter(place.value.lastpos, place.value.lastpos.begin()));
            /*вычисляем nullable*/
            place.value.is_nullable = c1->value.is_nullable || c2->value.is_nullable;
            break;
        }
        case NData::Type::Iter:
        {
            /*begin возвращает итератор на указатель, его разыменовываем*/
            std::shared_ptr<Node<NData>> c1 = *(place.children.begin());
            /*вычисляем firstpos*/
            place.value.firstpos =  c1->value.firstpos;
            /*вычисляем lastpos*/
            place.value.lastpos = c1->value.lastpos;
            /*вычисляем nullable*/
            place.value.is_nullable = true;
            break;
        }
    }
}

/*
class RExpNode : public Node<NData>
{
public:
    //конструктор
    RExpNode() { }
    //конструктор, вызывающий конструктор Node
    RExpNode(const NData& init_value) : Node<NData>(init_value) { }
    //деструктор
    ~RExpNode() { }

    //вычислитель
    void calculate()
    {
        switch(value.type)
        {
            case NData::Type::Char:
            {
                value.is_nullable = false;
                break;
            }
            case NData::Type::Conc:
            {
                std::shared_ptr<RExpNode> c1 = children.begin(); //begin воз
                if ()
                break;
            }
            case NData::Type::Union:
            {
                break;
            }
            case NData::Type::Iter:
            {
                value.is_nullable = true;
                break;
            }
        }
    }
};
*/

//lockguard
#endif
