#ifndef HPP_DRAWTREE
#define HPP_DRAWTREE
//lockguard
#include <vector>
#include <unordered_map>
#include <TGUI/TGUI.hpp>

#include "tree.hpp"
#include "rexpnode.hpp"
#include "Grexpnode.hpp"

void makegvec(std::vector<std::shared_ptr<Node<NData>>>& tree, std::vector<std::shared_ptr<GRExpNode>>& nodes,
              std::unordered_map<Node<NData>*, std::shared_ptr<GRExpNode>>& table);

//std::pair<float, float>
void makegr(std::shared_ptr<GRExpNode> root, std::unordered_map<Node<NData>*, std::shared_ptr<GRExpNode>>& table, std::pair<float, float> & sizes, float& minx, float& maxx, float& miny, float& maxy);

void sig_button(sf::RenderWindow & window, tgui::Gui & gui, sf::View & view, std::pair<float,float> & sizes, int scale_base, int & scale_power);

void sig_see_info_but(bool& see_info, tgui::Button& see_info_but);

void makenodes(std::vector<std::shared_ptr<GRExpNode>>& nodes, sf::Font & font);

void drawtree(std::shared_ptr<Node<NData>> root);

//lockguard
#endif
