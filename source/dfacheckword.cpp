#include "dfacheckword.hpp"

//#define DEBUG_DFACHECKWORD

void checkword (DFA& dfa, std::shared_ptr<mtt::Messaging<TurnOn>> turn_on_box, std::shared_ptr<mtt::Messaging<GetWord>> get_word_box)
{
    using namespace std::chrono_literals;
    #ifdef DEBUG_DFACHECKWORD
    std::cout << "CHECKING THREAD" << std::endl;
    #endif
    GetWord msg_word;
    bool should_stop = false;
    size_t state = 0;
    while(should_stop == false)
    {
        if(get_word_box->try_receive(msg_word))
        {
            #ifdef DEBUG_DFACHECKWORD
            std::cout << "RECEIVED:" << msg_word.word << std::endl;
            #endif
            std::string word = msg_word.word;
            should_stop = msg_word.should_stop;
            bool is_end = false;
            state = 0;
            for(size_t i = 0; i < word.size(); ++i)
            {
                if(is_end == false)
                {
                    TurnOn number;
                    if(dfa.transit[256*state + static_cast<int>(word[i])] >= 0)
                    {
                        number.state_number = dfa.transit[256*state + static_cast<int>(word[i])];
                        #ifdef DEBUG_DFACHECKWORD
                        std::cout << "go to state " << number.state_number << std::endl;
                        #endif
                        state = number.state_number;
                        if(i == word.size()-1)
                        {
                            number.is_all = true;
                            number.is_wrong = false;
                            is_end = true;
                        }
                        else
                        {
                            number.is_all = false;
                            number.is_wrong = false;
                        }
                    }
                    else
                    {
                        number.is_all = true;
                        number.is_wrong = true;
                        is_end = true;
                    }
                    turn_on_box->send(number);
                    #ifdef DEBUG_DFACHECKWORD
                    std::cout << "sent number" << number.state_number << std::endl;
                    #endif
                    std::this_thread::sleep_for(500ms);
                }
            }
        }
        std::this_thread::sleep_for(100ms);
    }
}

