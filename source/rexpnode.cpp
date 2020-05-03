#include "rexpnode.hpp"

void calculate(Node<NData>& place)
{
    switch(place.value.type)
    {
        case NData::Type::Char:
        {
            place.value.is_nullable = false;
            place.value.depth = 0;
            break;
        }
        case NData::Type::Conc:
        {
            /*begin возвращает итератор на указатель, его разыменовываем*/
            std::shared_ptr<Node<NData>> c1 = *(place.children.begin());
            std::shared_ptr<Node<NData>> c2 = *(++place.children.begin());
            /*рекурсивно*/
            calculate(*c1);
            calculate(*c2);
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
                place.value.lastpos = c2->value.lastpos;
            }
            /*вычисляем nullable*/
            place.value.is_nullable = c1->value.is_nullable && c2->value.is_nullable;
            /*вычисляем глубину*/
            if (c1->value.depth > c2->value.depth)
            {
                place.value.depth = 1 + c1->value.depth;
            }
            else
            {
                place.value.depth = 1 + c2->value.depth;
            }
            break;
        }
        case NData::Type::Union:
        {
            /*begin возвращает итератор на указатель, его разыменовываем*/
            std::shared_ptr<Node<NData>> c1 = *(place.children.begin());
            std::shared_ptr<Node<NData>> c2 = *(++place.children.begin());
            /*рекурсивно*/
            calculate(*c1);
            calculate(*c2);
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
            /*вычисляем глубину*/
            if (c1->value.depth > c2->value.depth)
            {
                place.value.depth = 1 + c1->value.depth;
            }
            else
            {
                place.value.depth = 1 + c2->value.depth;
            }
            break;
        }
        case NData::Type::Iter:
        {
            /*begin возвращает итератор на указатель, его разыменовываем*/
            std::shared_ptr<Node<NData>> c1 = *(place.children.begin());
            /*рекурсивно*/
            calculate(*c1);
            /*вычисляем firstpos*/
            place.value.firstpos =  c1->value.firstpos;
            std::cout << "FIRSTPOS: ";
            for(auto item : place.value.firstpos)
            {
                std::cout << "(" << item.first << ";" << item.second << "), " << std::endl;
            }
            /*вычисляем lastpos*/
            place.value.lastpos = c1->value.lastpos;
            std::cout << "LASTPOS: ";
            for(auto item : place.value.lastpos)
            {
                std::cout << "(" << item.first << ";" << item.second << "), " << std::endl;
            }
            /*вычисляем nullable*/
            place.value.is_nullable = true;
            /*вычисляем глубину*/
            place.value.depth = 1 + c1->value.depth;
            break;
        }
    }
}
