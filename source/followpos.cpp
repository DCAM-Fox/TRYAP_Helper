#include "followpos.hpp"

size_t makefollow (std::string str, std::vector<std::set<std::pair<size_t, char>>>& followpos)//(std::vector<std::shared_ptr<Node<NData>>>& tree)//, std::shared_ptr<Node<NData>> root)
{
    size_t max_pos = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        switch (str[i])
        {
            case '(' :
            {
                break;
            }
            case ')' :
            {
                break;
            }
            case '+' :
            {
                break;
            }
            default :
            {
                max_pos++;
                break;
            }
        }
    }
    //создание таблицы followpos (реализована массивом)
    for (size_t i = 0; i < max_pos; ++i)
    {
        followpos.push_back(std::set<std::pair<size_t, char>>());
    }
    return max_pos;
}

void countfollow (std::shared_ptr<Node<NData>> root,  std::vector<std::set<std::pair<size_t, char>>>& followpos, size_t max_pos)
{
    switch (root->value.type)
    {
        case NData::Type::Conc:
        {
            auto c1 = *(root->children.begin());
            auto c2 = *(++(root->children.begin()));
            for (size_t i = 0; i < max_pos; ++i)
            {
                auto iter = c1->value.lastpos.lower_bound(std::make_pair(i, 0));
                if ((iter != c1->value.lastpos.end()) && (iter->first == i))
                {
                    for (size_t j = 0; j < max_pos; ++j)
                    {
                        auto jter = c2->value.firstpos.lower_bound(std::make_pair(j, 0));
                        if ((jter != c2->value.firstpos.end()) && (jter->first == j))
                        {
                            followpos[i].insert(*jter);
                        }
                    }
                }
            }
            countfollow (c1, followpos, max_pos);
            countfollow (c2, followpos, max_pos);
            break;
        }
        case NData::Type::Union:
        {
            auto c1 = *(root->children.begin());
            auto c2 = *(++(root->children.begin()));
            countfollow(c1, followpos, max_pos);
            countfollow(c2, followpos, max_pos);
            break;
        }
        case NData::Type::Iter:
        {
            auto c1 = *(root->children.begin());
            for (size_t i = 0; i < max_pos; ++i)
            {
                auto iter = c1->value.lastpos.lower_bound(std::make_pair(i, 0));
                //std::cout << "i = " << i << "; (" << iter->first << ", " << iter->second << ")" << std::endl;
                if ((iter != c1->value.lastpos.end()) && (iter->first == i))
                {
                    for (size_t j = 0; j < max_pos; ++j)
                    {
                        auto jter = c1->value.firstpos.lower_bound(std::make_pair(j, 0));
                        if ((jter != c1->value.firstpos.end()) && (jter->first == j))
                        {
                            followpos[i].insert(*jter);
                        }
                    }
                }
            }
            countfollow(c1, followpos, max_pos);
            break;
        }
        case NData::Type::Char:
        {
            break;
        }
    }
}

