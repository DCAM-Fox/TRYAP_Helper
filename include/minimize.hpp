#ifndef HPP_MINIMIZE
#define HPP_MINIMIZE
//lockguard

#include "dfa.hpp"
#include <set> //тут реализованы множества
#include <algorithm>
#include <unordered_map>
#include <iostream>

void get_alph(std::set<char>& alphabet, std::string rexpr);

void minimize(DFA dfa, DFA& min_dfa, std::set<char>& alphabet);

//lockguard
#endif
