#ifndef HPP_REXPNODE
#define HPP_REXPNODE
//lockguard

//вершина дерева РВ

#include "tree.hpp"
#include <set> //тут реализованы множества
#include <algorithm>
#include <unordered_map>
#include <iostream>

struct NData
{
    /*
      bool is_calc = false; //посчитали уже?
    */
    bool is_nullable = false;

    std::set<std::pair<size_t, char>> firstpos;
    std::set<std::pair<size_t, char>> lastpos;
    /*
    std::set<size_t> firstpos;
    std::set<size_t> lastpos;
    */
    int depth = 0; //глубина поддерева
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

void calculate(Node<NData>& place);
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
