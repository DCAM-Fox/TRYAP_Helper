#ifndef HPP_DFSTATE
#define HPP_DFSTATE
//lockguard

#include <set>

#include "tree.hpp"
#include "rexpnode.hpp"
#include "followpos.hpp"

class DFState
{
public:
    bool is_start = false;
    bool is_accepting = false;
    std::set<std::pair<size_t, char>> positions;
    size_t num;
    bool mark = false;
    //конструктор
    DFState() { }
    //деструктор
    ~DFState() { }
};


//lockguard
#endif
