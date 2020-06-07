#ifndef HPP_SHOWFP
#define HPP_SHOWFP
//lockguard
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <math.h>

#include "followpos.hpp"

void sig_sh_button(sf::RenderWindow & window, bool & is_back);

int showfp(std::vector<std::set<std::pair<size_t, char>>>& followpos);// (sf::Font font);
//lockguard
#endif
