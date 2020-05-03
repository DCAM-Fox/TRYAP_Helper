#ifndef HPP_DFSTATE
#define HPP_DFSTATE
//lockguard

#include <set>

class DFState
{
public:
    bool is_start;
    bool is_accepting;
    std::set<std::pair<size_t, char>> positions;
    std::string name;
    //конструктор
    DFState() { }
    //деструктор
    ~DFState() { }
};


//lockguard
#endif
