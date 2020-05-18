#ifndef HPP_DFACHECKWORD
#define HPP_DFACHECKWORD
//lockguard

#include <vector>
#include <thread>

#include "dfstate.hpp"
#include "followpos.hpp"
#include "dfa.hpp"
#include "messagequeue.hpp"

class TurnOn : public mtt::Message
{
public:
    size_t state_number;
    bool is_all;
    bool is_wrong;
    //конструктор
    TurnOn() { }
    //деструктор
    ~TurnOn() { }
};

class GetWord : public mtt::Message
{
public:
    std::string word;
    bool should_stop;
    //конструктор
    GetWord() { }
    //деструктор
    ~GetWord() { }
};

void checkword (DFA& dfa, std::shared_ptr<mtt::Messaging<TurnOn>> turn_on_box, std::shared_ptr<mtt::Messaging<GetWord>> get_word_box);
//lockguard
#endif
