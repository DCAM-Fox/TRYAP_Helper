#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <unordered_map>
#include <sstream>
#include <thread>

#include "tree.hpp"
#include "grammar.hpp"
#include "Grexpnode.hpp"
#include "rexpnode.hpp"
#include "drawtree.hpp"
#include "followpos.hpp"
#include "dfa.hpp"
#include "drawdfa.hpp"
#include "messagequeue.hpp"
#include "startscreen.hpp"
#include "dfacheckword.hpp"
#include "menu.hpp"
#include "minimize.hpp"
#include "drawdfall.hpp"
//#include "showfp.hpp"

//#include <X11/Xlib.h>

//#define DEBUG_DRAWTREE
//#define DEBUG_FOLLOWPOS
//#define DEBUG_ROOT
//#define DEBUG_AUT
//#define DEBUG_MAIN

int main()
{
    int algo = -1;

    int what_to_do = 3;

    while(what_to_do == 3)
    {
        algo = drawmenu();

        switch (algo)
        {
            case (0) :
            {
                std::string more_dfa = "yes";

                std::vector<std::set<std::pair<size_t, char>>> followpos;

                while((more_dfa != "no") &&
                      (more_dfa != "nothing") &&
                      (more_dfa != "closed") &&
                      (more_dfa != "sfp"))
                {
                    //XInitThreads();

                    std::string str;

                    what_to_do = drawstartscreen(str);

                    if(what_to_do == 0)
                    {
                        if(!str.empty())
                        {
                            std::set<char> alphabet;

                            get_alph(alphabet, str);

                            std::cout << "ALPHABET" << std::endl;

                            for(auto item : alphabet)
                            {
                                std::cout << item << ' ';
                            }
                            std::cout << std::endl;

                            str = "(" + str + ")#";

                            #ifdef DEBUG_MAIN
                            std::cout << str << std::endl;
                            #endif

                            std::stringstream stream(str);

                            std::shared_ptr<Node<NData>> root;
                            size_t count = 0;
                            yy::parser parse(stream, root, count);
                            int next_step = parse();

                            if(next_step == 0)
                            {
                                #ifdef DEBUG_ROOT
                                std::cout << root.get() << std::endl;
                                #endif

                                calculate(*root);

                                #ifdef DEBUG_ROOT
                                std::cout << root->value.firstpos.size() << ' '
                                          << root->value.is_nullable << ' '
                                          << root->value.lastpos.size() << std::endl;
                                #endif

                                size_t max_pos = makefollow(str, followpos);

                                #ifdef DEBUG_FOLLOWPOS
                                std::cout << max_pos << std::endl;
                                #endif

                                countfollow(root, followpos, max_pos);

                                std::cout << "FOLLOWPOS" << std::endl;

                                for(size_t i = 0; i < followpos.size(); ++i)
                                {
                                    std::cout << "i = " << i << ": ";
                                    for(auto item : followpos[i])
                                    {
                                        std::cout << "(" << item.first << ";" << item.second << "), ";
                                    }
                                    std::cout << std::endl;
                                }

                                DFA dfa;

                                makestart(root, dfa.states, dfa.transit, max_pos);
                                makestates(dfa.states, dfa.transit, max_pos, followpos);
                                makefinal(dfa.states, dfa.fin);

                                #ifdef DEBUG_AUT
                                std::cout << "AUTOMATA" << std::endl;
                                std::cout << "   | ";

                                for(size_t i = size_t('a'); i <= size_t('z'); ++i)
                                {
                                    std::cout << char(i) << " | ";
                                }
                                std::cout << std::endl;
                                for(size_t i = 0; i < (dfa.transit.size()/256); ++i)
                                {
                                    std::cout << i << " | ";
                                    for(size_t j = size_t('a'); j <= size_t('z'); ++j)
                                    {
                                        std::cout << dfa.transit[256*i + j] << " | ";
                                    }
                                    std::cout << std::endl;
                                }
                                #endif

                                #ifdef DEBUG_AUT
                                for(size_t i = 0; i < dfa.states.size(); ++i)
                                {
                                    std::cout << "Is " << i << " accepting? " << dfa.states[i]->is_accepting << std::endl;
                                }
                                #endif

                                /*
                                drawtree(root);
                                */
                                std::shared_ptr<mtt::Messaging<TurnOn>> turn_on_box = std::make_shared<mtt::Messaging<TurnOn>>();
                                std::shared_ptr<mtt::Messaging<GetWord>> get_word_box = std::make_shared<mtt::Messaging<GetWord>>();

                                std::thread check_thread(checkword, std::ref(dfa), std::ref(turn_on_box), std::ref(get_word_box));
                                /*
                                more_dfa = drawdfa(dfa, turn_on_box, get_word_box);
                                */
                                more_dfa = drawdfall(dfa, root, followpos, turn_on_box, get_word_box);
                                /*
                                  if(more_dfa == "sfp")
                                  {
                                  std::cout << "sfp" << std::endl;
                                  int sfp = -1;
                                  sfp = showfp(followpos);
                                  std::cout << sfp << std::endl;
                                  if(sfp != -1)
                                  {
                                  more_dfa = "no";
                                  std::cout << more_dfa << std::endl;
                                  if (check_thread.joinable())
                                  {
                                  check_thread.join();
                                  }
                                  std::cout << "+" << std::endl;
                                  str = "";
                                  //return 0;
                                  }
                                  if (sfp == 3)
                                  {
                                  more_dfa = "yes";
                                  }
                                  }
                                */
                                /*
                                  std::cout << "sfp" << std::endl;

                                  int sfp = showfp(followpos);
                                */

                                if (check_thread.joinable())
                                {
                                    check_thread.join();
                                }

                                str = "";
                            }
                            else
                            {
                                std::cout << "Syntax error! Cannot build an automata!" << std::endl;
                                //return 0;
                            }
                        }
                        else
                        {
                            std::cout << "You putted an empty string!" << std::endl;
                        }
                    }
                    else
                    {
                        if(what_to_do != 3)
                        {
                            std::cout << "You did nothing!" << std::endl;
                            return 0;
                        }
                        else
                        {
                            more_dfa = "no";
                            //return 0;
                        }
                    }
                }
                break;
            }
            case (-1) :
            {
                return 0;
            }
            default :
            {
                std::cout << "Sorry, this algorythm is not ready yet." << std::endl;
                break;
            }
        }
    }
    /*
      int num;
      std::cin >> num;
      std::string str = int_to_str(num);
      std::cout << str << std::endl;
    */
    return 0;
}
