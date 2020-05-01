#include "tree.hpp"
#include "grammar.hpp"
#include <iostream>

int main()
{
    // std::shared_ptr<Node<int>> root = std::make_shared<Node<int>>(0);
    // std::shared_ptr<Node<int>> child1 = std::make_shared<Node<int>>(1);
    // std::shared_ptr<Node<int>> child2 = std::make_shared<Node<int>>(2);

    // root->add_child(child1);
    // root->add_child(child2);

    // for(auto child : root->children) //берет children, идет и перебирает все child'ы из children
    // {
    //     std::cout << child->value << ", ";
    // }

    std::shared_ptr<Node<NData>> root;
    yy::parser parse(std::cin, root);
    parse();
    std::cout << root.get() << std::endl;
    calculate(*root);
    std::cout << root->value.firstpos.size() << ' '
              << root->value.is_nullable << ' '
              << root->value.lastpos.size() << std::endl;
    return 0;
}
