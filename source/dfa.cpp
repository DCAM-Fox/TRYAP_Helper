#include "dfa.hpp"

#define DEBUG_DFA

void makestart(std::shared_ptr<Node<NData>> root,
               std::vector<std::shared_ptr<DFState>>& states,
               std::vector<ssize_t>& transit,
               size_t max_pos)
{
    std::shared_ptr<DFState> start = std::make_shared<DFState>();

    start->positions = root->value.firstpos;
    start->is_start = true;
    start->num = 0;

    if (start->positions.find(std::make_pair((max_pos-1), '#')) != start->positions.end())
    {
        start->is_accepting = true;
    }

    states.push_back(start);

    #ifdef DEBUG_DFA
    std::cout << "START" << std::endl;

    for(auto item : start->positions)
    {
        std::cout << "(" << item.first << ";" << item.second << "), ";
    }

    std::cout << std::endl;
    #endif

    for(size_t i = 0; i < 256; ++i)
    {
        transit.push_back(-1);
    }
}

void makestates(std::vector<std::shared_ptr<DFState>>& states,
                std::vector<ssize_t>& transit,
                size_t max_pos,
                std::vector<std::set<std::pair<size_t, char>>>& followpos)
{
    for(size_t k = 0; k < states.size(); ++k)
    {
        if(states[k]->mark == false)
        {
            states[k]->mark = true;
            for (size_t i = 0; i < 256; ++i) //проверяем все символы
            {
                std::set<std::pair<size_t, char>> pos;
                std::set<std::pair<size_t, char>> tr;
                for (size_t p = 0; p < max_pos; ++p) //проверяем все позиции
                {
                    auto iter = states[k]->positions.find(std::make_pair(p, char(i))); //если есть позиция
                    if(iter != states[k]->positions.end())
                    {
                        #ifdef DEBUG_DFA
                        std::cout << "(" << (*iter).first <<";"<<(*iter).second<<"):" << std::endl;
                        #endif

                        std::set_union(pos.begin(), pos.end(),
                                       followpos[iter->first].begin(), followpos[iter->first].end(),
                                       std::inserter(pos, pos.begin()));
                        tr.insert(*iter);

                        #ifdef DEBUG_DFA
                        for(auto item : followpos[iter->first])
                        {
                            std::cout << "(" << item.first << ";" << item.second << "), ";
                        }
                        std::cout<<std::endl;
                        #endif
                    }
                }

                bool exists = false;
                size_t number = 0;
                for (size_t l = 0; l < states.size(); ++l)
                {
                    if (states[l]->positions == pos)
                    {
                        exists = true;
                        number = l;
                    }
                }

                if (exists == false)
                {
                    number = states.size();
                }

                //если нет
                if (!(pos.empty()))
                {
                    if (exists == false)
                    {
                        states.push_back(std::make_shared<DFState>());
                        size_t s = states.size()-1;

                        states[s]->positions = pos;
                        states[s]->is_start = false;
                        states[s]->num = s;

                        #ifdef DEBUG_DFA
                        for(auto item : states[s]->positions)
                        {
                            std::cout << "(" << item.first << ";" << item.second << "), ";
                        }
                        std::cout<<std::endl;
                        #endif

                        if (states[s]->positions.find(std::make_pair((max_pos-1), '#')) != states[s]->positions.end())
                        {
                            states[s]->is_accepting = true;
                        }

                        #ifdef DEBUG_DFA
                        std::cout << "is accepting? " << states[s]->is_accepting << std::endl;

                        std::cout << "STATE" << std::endl;

                        for(auto item : states[s]->positions)
                        {
                            std::cout << "(" << item.first << ";" << item.second << "), ";
                        }

                        std::cout << std::endl;
                        #endif

                        for (auto item : tr)
                        {
                            transit[256*k + size_t(item.second)] = number;
                        }

                        for(size_t m = 0; m < 256; ++m)
                        {
                            transit.push_back(-1);
                        }
                    }
                    else
                    {
                        for (auto item : tr)
                        {
                            transit[256*k + size_t(item.second)] = number;
                        }

                        #ifdef DEBUG_DFA
                        std::cout << "STATE" << std::endl;

                        for(auto item : states[number]->positions)
                        {
                            std::cout << "(" << item.first << ";" << item.second << "), ";
                        }
                        #endif
                    }
                }
            }
            #ifdef DEBUG_DFA
            std::cout << "end of state" << k << std::endl;
            #endif
        }
    }
}

void makefinal (std::vector<std::shared_ptr<DFState>>& states, std::vector<std::shared_ptr<DFState>>& fin)
{
    for (size_t i = 0; i < states.size(); ++i)
    {
        if (states[i]->is_accepting == true)
        {
            fin.push_back(states[i]);
        }
    }
}
