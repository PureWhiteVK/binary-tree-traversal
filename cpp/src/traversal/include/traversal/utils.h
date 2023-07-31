#pragma once
#include "traversal/iterator.h"
#include "traversal/tree.h"
#include <functional>
#include <iostream>
#include <memory>
#include <ostream>

namespace traversal {
namespace utils {
template <typename T>
TreeNode<T> *reverse_right_linked_list(TreeNode<T> *start) {
  using node = TreeNode<T>;
  using node_ptr = node *;
  static node head{};
  head.right = nullptr;
  node_ptr curr = start;
  while (curr) {
    node_ptr temp = curr->right;
    curr->right = head.right;
    head.right = curr;
    curr = temp;
  }
  return head.right;
}

template <typename T> void pretty_print(TreeNode<T> *root) {
  using node_ptr = TreeNode<T> *;
  std::function<void(node_ptr, std::string, bool)> recursive;
  recursive = [&](node_ptr node, std::string prefix, bool is_right) {
    if (!node) {
      std::cout << prefix << "null" << std::endl;
      return;
    }
    std::cout << prefix << *node << std::endl;
    if (!prefix.empty()) {
      // warning: no utf-8 support in cpp
      static const int length = std::string("├── ").length();
      prefix = is_right ? prefix.substr(0, prefix.length() - length) + "│   "
                        : prefix.substr(0, prefix.length() - length) + "    ";
    }
    if (node->left || node->right) {
      recursive(node->right, prefix + "├── ", true);
      recursive(node->left, prefix + "└── ", false);
    }
  };
  recursive(root, "", false);
}

enum RecursiveType { Preorder, Inorder, Postorder };

template <typename T>
void print_callstack(TreeNode<T> *root, RecursiveType type) {
  using node_ptr = TreeNode<T> *;
  std::function<std::ostream &(std::ostream &, int)> print_indent =
      [](std::ostream &os, int indent) -> std::ostream & {
    while (indent--) {
      os << ' ';
    }
    return os;
  };

  std::function<void(node_ptr, int)> inorder_recursive;
  inorder_recursive = [&](node_ptr node, int indent) {
    if (!node) {
      return;
    }
    print_indent(std::cout, indent)
        << "recursive(" << *node << ")" << std::endl;
    indent += 2;
    if (type == RecursiveType::Preorder) {
      print_indent(std::cout, indent) << "visit(" << *node << ")" << std::endl;
    }
    inorder_recursive(node->left, indent);
    if (type == RecursiveType::Inorder) {
      print_indent(std::cout, indent) << "visit(" << *node << ")" << std::endl;
    }
    inorder_recursive(node->right, indent);
    if (type == RecursiveType::Postorder) {
      print_indent(std::cout, indent) << "visit(" << *node << ")" << std::endl;
    }
  };
  inorder_recursive(root, 0);
}

template <typename T> void delete_tree(TreeNode<T> *root) {
  auto iter = traversal::iterator::LevelOrderIterator<T>(root);
  while (iter.has_next()) {
    delete iter.next();
  }
}

inline std::unique_ptr<TreeNode<int>, std::function<void(TreeNode<int> *)>>
create_test_tree4() {
  using node = TreeNode<int>;
  using node_ptr = node *;
  node_ptr v0 = new node{5};
  node_ptr v1 = new node{3};
  node_ptr v2 = new node{1};
  node_ptr v3 = new node{2};
  node_ptr v4 = new node{4};
  node_ptr v5 = new node{8};
  node_ptr v6 = new node{7};
  v0->left = v1;
  v0->right = v2;
  v1->left = v3;
  v1->right = v4;
  v3->left = v5;
  v4->right = v6;
  return std::unique_ptr<TreeNode<int>, std::function<void(TreeNode<int> *)>>(
      v0, delete_tree<int>);
}

} // namespace utils
} // namespace traversal