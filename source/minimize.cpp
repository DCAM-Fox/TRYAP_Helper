#include "minimize.hpp"

void get_alph(std::set<char>& alphabet, std::string rexpr)
{
    for (int i = 0; i < 256; ++i)
    {
        for (size_t j = 0; j < rexpr.size(); ++j)
        {
            if ((rexpr[j] == static_cast<char>(i)) &&
                (rexpr[j] != '+') &&
                (rexpr[j] != '*') &&
                (rexpr[j] != ')') &&
                (rexpr[j] != '('))
            {
                alphabet.insert(rexpr[j]);
            }
        }
    }
}

void minimize(DFA dfa, DFA& min_dfa, std::set<char>& alphabet)
{
    DFA full_dfa;
    full_dfa = dfa;
    bool need_add = false;
    for(size_t i = 0; i < full_dfa.states.size(); ++i)
    {
        for(auto item : alphabet)
        {
            if(full_dfa.transit[256*i+item] == -1)
            {
                need_add = true;
                full_dfa.transit[256*i + item] = full_dfa.states.size();
            }
        }
    }
    if(need_add == true)
    {
        full_dfa.states.push_back(std::make_shared<DFState>());
        full_dfa.states[full_dfa.states.size()-1]->num = full_dfa.states.size()-1;
        full_dfa.states[full_dfa.states.size()-1]->is_start = false;
        full_dfa.states[full_dfa.states.size()-1]->is_accepting = false;
        for(auto item : alphabet)
        {
            full_dfa.transit[256*(full_dfa.states.size()-1)+item] = full_dfa.states.size()-1;
        }
    }

    /*
    std::vector<std::vector<std::vector<DFState>>> algo;
    for(size_t i = 0; i < full_dfa.states.size(); ++i)
    {
        if(full_dfa.states[i]->is_accepting == false)
        {
            algo[0][0].push_back(full_dfa.states[i]);
        }
        else
        {
            algo[0][1].push_back(full_dfa.states[i]);
        }
    }
    algo.push_back(std::vector<std::vector<DFState>>());
    for(size_t i = 0; i < algo[0].size(); ++i)
    {
        algo[1].push_back(std::vector<DFState>());
        algo[1][0].push_back(algo[0][0][0]);
        for(size_t j = 0; j < algo[0][0].size(); ++j)
        {
        }
    }
    while (algo[i] != algo[i-1])
    */
}
