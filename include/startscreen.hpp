#ifndef HPP_STARTSCREEN
#define HPP_STARTSCREEN
//lockguard
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "dfa.hpp"
#include "dfstate.hpp"
#include "Gstate.hpp"
#include "Garrow.hpp"
void sig_button(sf::RenderWindow & window, bool & is_back);

int drawstartscreen(std::string& str);// (sf::Font font);
//lockguard
#endif
