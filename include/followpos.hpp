#ifndef HPP_FOLLOWPOS
#define HPP_FOLLOWPOS
//lockguard

#include <vector>

#include "tree.hpp"
#include "rexpnode.hpp"

size_t makefollow (std::string str, std::vector<std::set<std::pair<size_t, char>>>& followpos);

void countfollow (std::shared_ptr<Node<NData>> root,  std::vector<std::set<std::pair<size_t, char>>>& followpos, size_t max_pos);

//lockguard
#endif
