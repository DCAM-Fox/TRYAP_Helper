#ifndef HPP_TREE
#define HPP_TREE
//lockguard

//дерево в общем виде

#include <memory> //хранится объявление умных указателей
#include <list> //хранятся списки

//вершина

template<typename T>
/*класс Node есть шаблон,
  он принимает один аргумент - некоторый тип,
  и если мы хотим обратиться к этому аргументу, то пишем T*/
class Node
{
public:
    //хранится элемент какого-то типа
    T value;
    /*
    //указатель на родителя
    std::shared_ptr<Node<t>> parent;
    */
    //список указателей на детей
    std::list<std::shared_ptr<Node<T>>> children;

    //конструктор
    Node() { }
    /*конструктор, но в него передается еще ссылка на тип t,
      const - редактировать нельзя, только читать*/
    Node(const T& init_value)
    {
        value = init_value; //то, что лежит по ссылке, копируется в value
    }
    //деструктор
    ~Node() { }

    //добавление ребенка
    void add_child(const std::shared_ptr<Node<T>>& child)
    {
        children.push_back(child);
        //child->parent = parent;
    }
};

//lockguard
#endif
