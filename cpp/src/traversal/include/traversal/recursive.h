#pragma once
#include "traversal/tree.h"
#include "traversal/utils.h"
#include <stack>

namespace traversal {
namespace recursive {
template <typename T>
void preorder(TreeNode<T> *root, std::function<void(TreeNode<T> *)> visit) {
  using node_ptr = TreeNode<T> *;
  std::function<void(node_ptr)> recursive;
  recursive = [&](node_ptr node) {
    if (!node) {
      return;
    }
    visit(node);
    recursive(node->left);
    recursive(node->right);
  };
  recursive(root);
}

template <typename T>
void inorder(TreeNode<T> *root, std::function<void(TreeNode<T> *)> visit) {
  using node_ptr = TreeNode<T> *;
  std::function<void(node_ptr)> recursive;
  recursive = [&](node_ptr node) {
    if (!node) {
      return;
    }
    recursive(node->left);
    visit(node);
    recursive(node->right);
  };
  recursive(root);
}

template <typename T>
void postorder(TreeNode<T> *root, std::function<void(TreeNode<T> *)> visit) {
  using node_ptr = TreeNode<T> *;
  std::function<void(node_ptr)> recursive;
  recursive = [&](node_ptr node) {
    if (!node) {
      return;
    }
    recursive(node->left);
    recursive(node->right);
    visit(node);
  };
  recursive(root);
}

template <typename T>
void postorder2(TreeNode<T> *root, std::function<void(TreeNode<T> *)> visit) {
  using node_ptr = TreeNode<T> *;
  std::function<void(node_ptr)> recursive;
  recursive = [&](node_ptr node) {
    std::stack<node_ptr> stack;
    for (node_ptr curr = node; curr != nullptr; curr = curr->right) {
      recursive(curr->left);
      stack.push(curr);
    }
    while (!stack.empty()) {
      visit(stack.top());
      stack.pop();
    }
  };
  recursive(root);
}

template <typename T>
void postorder3(TreeNode<T> *root, std::function<void(TreeNode<T> *)> visit) {
  using node_ptr = TreeNode<T> *;
  std::function<void(node_ptr)> recursive;
  recursive = [&](node_ptr node) {
    // 遍历完该链表上的所有左子树
    for (node_ptr curr = node; curr != nullptr; curr = curr->right) {
      recursive(curr->left);
    }
    node_ptr reversed_head = utils::reverse_right_linked_list(node);
    for (node_ptr curr = reversed_head; curr != nullptr; curr = curr->right) {
      visit(curr);
    }
    utils::reverse_right_linked_list(reversed_head);
  };
  recursive(root);
}

} // namespace recursive
} // namespace traversal