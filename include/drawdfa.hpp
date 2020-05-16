#ifndef HPP_DRAWDFA
#define HPP_DRAWDFA
//lockguard
#include <vector>
#include <unordered_map>

#include "dfa.hpp"
#include "dfstate.hpp"
#include "Gstate.hpp"
#include "Garrow.hpp"

void makeaut(DFA& dfa, std::vector<std::shared_ptr<DFState>>& automata);

void makebase(std::vector<std::shared_ptr<DFState>>& automata, std::vector<std::shared_ptr<GState>>& gstates, std::unordered_map<DFState*, std::shared_ptr<GState>>& table);

void makelayout(std::vector<std::shared_ptr<GState>> states, std::vector<sf::Text>& text, sf::Font& font);

void makearrows(DFA& dfa, std::vector<std::shared_ptr<GState>>& gstates, std::vector<std::shared_ptr<GArrow>>& arrows, sf::Font& font);

int drawdfa(DFA& dfa);
//lockguard
#endif
