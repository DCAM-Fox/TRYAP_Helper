#ifndef HPP_DRAWDFA
#define HPP_DRAWDFA
//lockguard
#include <vector>
#include <unordered_map>
#include <TGUI/TGUI.hpp>


#include "dfa.hpp"
#include "dfacheckword.hpp"
#include "dfstate.hpp"
#include "Gstate.hpp"
#include "Garrow.hpp"

void makeaut(DFA& dfa, std::vector<std::shared_ptr<DFState>>& automata);

void makebase(std::vector<std::shared_ptr<DFState>>& automata, std::vector<std::shared_ptr<GState>>& gstates, std::unordered_map<DFState*, std::shared_ptr<GState>>& table);

void makelayout(std::vector<std::shared_ptr<GState>> states, std::vector<sf::Text>& text, sf::Font& font);

void makearrows(DFA& dfa, std::vector<std::shared_ptr<GState>>& gstates, std::vector<std::shared_ptr<GArrow>>& arrows, sf::Font& font);

void sig_word(std::shared_ptr<mtt::Messaging<GetWord>> get_word_box, std::shared_ptr<tgui::EditBox>& wordBox, bool& is_checking, std::string& the_word, size_t& current_state, std::vector<std::shared_ptr<GState>> & gstates);

void sig_button(bool & sfp);

std::string drawdfa(DFA& dfa, std::shared_ptr<mtt::Messaging<TurnOn>> turn_on_box, std::shared_ptr<mtt::Messaging<GetWord>> get_word_box);//, std::string& the_word)
//std::string drawdfa(DFA& dfa);
//lockguard
#endif
