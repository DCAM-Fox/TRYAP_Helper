#ifndef HPP_MENU
#define HPP_MENU
//lockguard
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "dfa.hpp"
#include "dfstate.hpp"
#include "Gstate.hpp"
#include "Garrow.hpp"

/*
  0 -- RExp -> DFA
  1 -- RExp -> NFA
  2 -- minimisation
  3 -- determination
  4 -- Akho-Korasik
  5 -- context-free
  6 -- LL(1)
  7 -- LR(1)
 */
void sig_re_dfa(sf::RenderWindow & window, int& algo);
void sig_re_nfa(sf::RenderWindow & window, int& algo);
void sig_minim(sf::RenderWindow & window, int& algo);
void sig_determ(sf::RenderWindow & window, int& algo);
void sig_aho(sf::RenderWindow & window, int& algo);
void sig_mag(sf::RenderWindow & window, int& algo);
void sig_ll(sf::RenderWindow & window, int& algo);
void sig_lr(sf::RenderWindow & window, int& algo);

int drawmenu();// (sf::Font font);
//lockguard
#endif
