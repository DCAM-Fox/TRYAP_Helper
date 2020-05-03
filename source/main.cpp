#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <unordered_map>
#include <sstream>

#include "tree.hpp"
#include "grammar.hpp"
#include "Grexpnode.hpp"
#include "rexpnode.hpp"
#include "drawtree.hpp"
#include "followpos.hpp"

//#define DEBUG_DRAWTREE


int main()
{
    std::string str;
    std::cin >> str;
    str = "(" + str + ")#";

    std::stringstream stream(str);

    std::shared_ptr<Node<NData>> root;
    yy::parser parse(stream, root);
    parse();
    std::cout << root.get() << std::endl;
    calculate(*root);
    std::cout << root->value.firstpos.size() << ' '
              << root->value.is_nullable << ' '
              << root->value.lastpos.size() << std::endl;

    std::vector<std::set<std::pair<size_t, char>>> followpos;
    size_t max_pos = makefollow(str, followpos);

    std::cout << max_pos << std::endl;

    countfollow(root, followpos, max_pos);

    for(size_t i = 0; i < followpos.size(); ++i)
    {
        std::cout << "i = " << i;
        for(auto item : followpos[i])
        {
            std::cout << "(" << item.first << ";" << item.second << "), ";
        }
        std::cout << std::endl;
    }
    drawtree(root);

    return 0;
}
