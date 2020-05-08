#ifndef HPP_DRAWDFA
#define HPP_DRAWDFA
//lockguard
#include <vector>
#include <unordered_map>

#include "dfa.hpp"
#include "dfstate.hpp"
#include "Gstate.hpp"

void makeaut(DFA& dfa, std::vector<std::shared_ptr<DFState>>& automata);

void makebase(std::vector<std::shared_ptr<DFState>>& automata, std::vector<std::shared_ptr<GState>>& states, std::unordered_map<DFState*, std::shared_ptr<GState>>& table);

void makelayout(std::vector<std::shared_ptr<GState>> states);

void drawdfa(DFA& dfa);
//lockguard
#endif
