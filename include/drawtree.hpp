#ifndef HPP_DRAWTREE
#define HPP_DRAWTREE
//lockguard
#include <vector>
#include <unordered_map>

#include "tree.hpp"
#include "rexpnode.hpp"
#include "Grexpnode.hpp"

void makegvec(std::vector<std::shared_ptr<Node<NData>>>& tree, std::vector<std::shared_ptr<GRExpNode>>& nodes,
              std::unordered_map<Node<NData>*, std::shared_ptr<GRExpNode>>& table);

void makegr(std::shared_ptr<GRExpNode> root, std::unordered_map<Node<NData>*, std::shared_ptr<GRExpNode>>& table);

void drawtree(std::shared_ptr<Node<NData>> root);

//lockguard
#endif
