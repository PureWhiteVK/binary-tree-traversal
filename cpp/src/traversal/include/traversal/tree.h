#pragma once
#include <iostream>

namespace traversal {
template <typename T> struct TreeNode {
  using value_type = T;
  using ptr_type = TreeNode<T> *;

  value_type val{};
  ptr_type left{nullptr};
  ptr_type right{nullptr};
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const TreeNode<T> &node) {
  return os << node.val;
}
} // namespace traversal