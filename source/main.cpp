#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <unordered_map>
#include <sstream>
#include <thread>

#include "tree.hpp"
#include "grammar.hpp"
#include "Grexpnode.hpp"
#include "rexpnode.hpp"
#include "drawtree.hpp"
#include "followpos.hpp"
#include "dfa.hpp"
#include "drawdfa.hpp"
#include "startscreen.hpp"

//#include <X11/Xlib.h>

//#define DEBUG_DRAWTREE
//#define DEBUG_FOLLOWPOS
//#define DEBUG_ROOT
//#define DEBUG_AUT

int main()
{
    //XInitThreads();

    std::string str;
    std::cin >> str;
    str = "(" + str + ")#";

    std::cout << str << std::endl;

    std::stringstream stream(str);

    std::shared_ptr<Node<NData>> root;
    yy::parser parse(stream, root);
    parse();

    #ifdef DEBUG_ROOT
    std::cout << root.get() << std::endl;
    #endif

    calculate(*root);

    #ifdef DEBUG_ROOT
    std::cout << root->value.firstpos.size() << ' '
              << root->value.is_nullable << ' '
              << root->value.lastpos.size() << std::endl;
    #endif



    std::vector<std::set<std::pair<size_t, char>>> followpos;
    size_t max_pos = makefollow(str, followpos);

    #ifdef DEBUG_FOLLOWPOS
    std::cout << max_pos << std::endl;
    #endif

    countfollow(root, followpos, max_pos);

    std::cout << "FOLLOWPOS" << std::endl;

    for(size_t i = 0; i < followpos.size(); ++i)
    {
        std::cout << "i = " << i << ": ";
        for(auto item : followpos[i])
        {
            std::cout << "(" << item.first << ";" << item.second << "), ";
        }
        std::cout << std::endl;
    }

    DFA dfa;

    makestart(root, dfa.states, dfa.transit, max_pos);
    makestates(dfa.states, dfa.transit, max_pos, followpos);
    makefinal(dfa.states, dfa.fin);

    #ifdef DEBUG_AUT
    std::cout << "AUTOMATA" << std::endl;
    std::cout << "   | ";

    for(size_t i = size_t('a'); i <= size_t('z'); ++i)
    {
        std::cout << char(i) << " | ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < (dfa.transit.size()/256); ++i)
    {
        std::cout << i << " | ";
        for(size_t j = size_t('a'); j <= size_t('z'); ++j)
        {
            std::cout << dfa.transit[256*i + j] << " | ";
        }
        std::cout << std::endl;
    }
    #endif

    for(size_t i = 0; i < dfa.states.size(); ++i)
    {
        std::cout << "Is " << i << " accepting? " << dfa.states[i]->is_accepting << std::endl;
    }

    //std::thread dfa_thread(drawdfa, std::ref(dfa));

    drawstartscreen();

    drawtree(root);

    /*
    if (dfa_thread.joinable())
    {
        dfa_thread.join();
    }
    */

    drawdfa(dfa);

    return 0;
}
