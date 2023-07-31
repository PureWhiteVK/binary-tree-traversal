#pragma once
#include "traversal/utils.h"
#include "traversal/tree.h"
#include "util.h"
#include <queue>
#include <stack>

namespace traversal {
namespace iterative {
template <typename T>
void preorder(TreeNode<T> *root, std::function<void(TreeNode<T> *)> visit) {
  using node_ptr = TreeNode<T> *;
  std::stack<node_ptr> stack;
  stack.emplace(root);
  while (!stack.empty()) {
    node_ptr curr = stack.top();
    stack.pop();
    if (!curr) {
      continue;
    }
    visit(curr);
    stack.emplace(curr->right);
    stack.emplace(curr->left);
  }
}

template <typename T>
void inorder(TreeNode<T> *root, std::function<void(TreeNode<T> *)> visit) {
  using node_ptr = TreeNode<T> *;
  std::stack<std::pair<node_ptr, bool>> stack;
  stack.emplace(root, true);
  while (!stack.empty()) {
    auto [curr, first] = stack.top();
    stack.pop();
    if (!curr) {
      continue;
    }
    if (!first) {
      visit(curr);
    } else {
      stack.emplace(curr->right, true);
      stack.emplace(curr, false);
      stack.emplace(curr->left, true);
    }
  }
}

template <typename T>
void postorder(TreeNode<T> *root, std::function<void(TreeNode<T> *)> visit) {
  using node_ptr = TreeNode<T> *;
  std::stack<std::pair<node_ptr, bool>> stack;
  stack.emplace(root, true);
  while (!stack.empty()) {
    auto [curr, first] = stack.top();
    stack.pop();
    if (!curr) {
      continue;
    }
    if (!first) {
      visit(curr);
    } else {
      stack.emplace(curr, false);
      stack.emplace(curr->right, true);
      stack.emplace(curr->left, true);
    }
  }
}

template <typename T>
void level_order(TreeNode<T> *root, std::function<void(TreeNode<T> *)> visit) {
  using node_ptr = typename TreeNode<T>::ptr_type;
  std::queue<node_ptr> queue;
  queue.emplace(root);
  while (!queue.empty()) {
    // 相应的替换成 queue 对应的队首和弹出函数
    node_ptr curr = queue.front();
    queue.pop();
    visit(curr);
    if (curr->right) {
      queue.emplace(curr->right);
    }
    if (curr->left) {
      queue.emplace(curr->left);
    }
  }
}

template <typename T>
void morris_preorder(TreeNode<T> *root,
                     std::function<void(TreeNode<T> *)> visit) {
  using node_ptr = typename TreeNode<T>::ptr_type;
  node_ptr curr = root;
  while (curr) {
    if (!curr->left) {
      visit(curr);
      curr = curr->right;
      continue;
    }
    node_ptr prev = curr->left;
    while (prev->right && prev->right != curr) {
      prev = prev->right;
    }
    if (prev->right == curr) {
      prev->right = nullptr;
      curr = curr->right;
    } else {
      prev->right = curr;
      visit(curr);
      curr = curr->left;
    }
  }
}

template <typename T>
void morris_inorder(TreeNode<T> *root,
                    std::function<void(TreeNode<T> *)> visit) {
  using node_ptr = typename TreeNode<T>::ptr_type;
  node_ptr curr = root;
  while (curr) {
    if (!curr->left) {
      visit(curr);
      curr = curr->right;
      continue;
    }
    node_ptr prev = curr->left;
    while (prev->right && prev->right != curr) {
      prev = prev->right;
    }
    if (prev->right == curr) {
      prev->right = nullptr;
      visit(curr);
      curr = curr->right;
    } else {
      prev->right = curr;
      curr = curr->left;
    }
  }
}

template <typename T>
void morris_postorder(TreeNode<T> *root,
                      std::function<void(TreeNode<T> *)> visit) {
  using node = TreeNode<T>;
  using node_ptr = typename node::ptr_type;
  node_ptr curr = root;

  std::function<void(node_ptr)> add_path = [&](node_ptr head) {
    node_ptr rhead = utils::reverse_right_linked_list(head);
    for (node_ptr i = rhead; i != nullptr; i = i->right) {
      visit(i);
    }
    utils::reverse_right_linked_list(rhead);
  };

  while (curr) {
    if (!curr->left) {
      curr = curr->right;
      continue;
    }
    node_ptr prev = curr->left;
    while (prev->right && prev->right != curr) {
      prev = prev->right;
    }
    if (prev->right == curr) {
      prev->right = nullptr;
      add_path(curr->left);
      curr = curr->right;
    } else {
      prev->right = curr;
      curr = curr->left;
    }
  }
  add_path(root);
}

} // namespace iterative
} // namespace traversal