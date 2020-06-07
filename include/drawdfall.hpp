#ifndef HPP_DRAWDFALL
#define HPP_DRAWDFALL
//lockguard
#include <vector>
#include <unordered_map>
#include <TGUI/TGUI.hpp>

#include "drawdfa.hpp"
#include "drawtree.hpp"
#include "rexpnode.hpp"
#include "Grexpnode.hpp"

void sig_see_tree(sf::RenderWindow & window, tgui::Gui & gui, sf::View & view, std::pair<float, float>& sizes, int scale_base, int & scale_power);

void if_draw_aut(bool & draw_aut, bool & draw_tree, bool & draw_fp);

void if_draw_tree(bool & draw_aut, bool & draw_tree, bool & draw_fp);

void if_draw_fp(bool & draw_aut, bool & draw_tree, bool & draw_fp);

std::string drawdfall(DFA& dfa, std::shared_ptr<Node<NData>> root, std::vector<std::set<std::pair<size_t, char>>>& followpos, std::shared_ptr<mtt::Messaging<TurnOn>> turn_on_box, std::shared_ptr<mtt::Messaging<GetWord>> get_word_box);//, std::string& the_word)
    //std::string drawdfall(DFA& dfa, std::shared_ptr<Node<NData>> root, std::shared_ptr<mtt::Messaging<TurnOn>> turn_on_box, std::shared_ptr<mtt::Messaging<GetWord>> get_word_box);//, std::string& the_word)
//lockguard
#endif
