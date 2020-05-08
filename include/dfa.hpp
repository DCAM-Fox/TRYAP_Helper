#ifndef HPP_DFA
#define HPP_DFA
//lockguard

#include <vector>

#include "dfstate.hpp"
#include "followpos.hpp"

class DFA
{
public:
    std::vector<std::shared_ptr<DFState>> states;
    std::vector<ssize_t> transit;
    //std::vector<std::pair<std::pair<DFState, char>, DFState>> transit;
    std::shared_ptr<DFState> start;
    std::vector<std::shared_ptr<DFState>> fin;
    //конструктор
    DFA() { }
    //деструктор
    ~DFA() { }
};

void makestart(std::shared_ptr<Node<NData>> root,
               //std::shared_ptr<DFState>& start,
               std::vector<std::shared_ptr<DFState>>& states,
               std::vector<ssize_t>& transit,
               size_t max_pos);

void makestates(std::vector<std::shared_ptr<DFState>>& states,
                std::vector<ssize_t>& transit,
                size_t max_pos,
                std::vector<std::set<std::pair<size_t, char>>>& followpos);

void makefinal (std::vector<std::shared_ptr<DFState>>& states, std::vector<std::shared_ptr<DFState>>& fin);
//lockguard
#endif
