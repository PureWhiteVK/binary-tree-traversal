#pragma once

#include "tree.h"
#include <queue>
#include <stack>

namespace traversal {
namespace iterator {
template <typename T> class TreeIterator {
  using node_ptr = typename TreeNode<T>::ptr_type;

public:
  TreeIterator<T>() = delete;
  TreeIterator<T>(node_ptr root) : root(root) {}
  virtual void reset() = 0;
  virtual bool has_next() = 0;
  virtual node_ptr next() = 0;

protected:
  node_ptr root{nullptr};
};

template <typename T, typename S>
class StackTreeIterator : public TreeIterator<T> {
  using node_ptr = typename TreeNode<T>::ptr_type;

public:
  StackTreeIterator<T, S>(node_ptr root) : TreeIterator<T>(root) {}

  bool has_next() override { return !stack.empty(); }

  void reset() override {
    while (!stack.empty()) {
      stack.pop();
    }
  }

protected:
  std::stack<S> stack;
};

template <typename T>
class PreorderIterator
    : public StackTreeIterator<T, typename TreeNode<T>::ptr_type> {
  using node_ptr = typename TreeNode<T>::ptr_type;

public:
  PreorderIterator<T>(node_ptr root) : StackTreeIterator<T, node_ptr>(root) {
    reset();
  }

  void reset() override {
    StackTreeIterator<T, node_ptr>::reset();
    if (this->root) {
      this->stack.emplace(this->root);
    }
  }

  node_ptr next() override {
    node_ptr curr = this->stack.top();
    this->stack.pop();
    if (curr->right) {
      this->stack.emplace(curr->right);
    }
    if (curr->left) {
      this->stack.emplace(curr->left);
    }
    return curr;
  }
};

template <typename T>
class InorderIterator
    : public StackTreeIterator<
          T, std::pair<typename TreeNode<T>::ptr_type, bool>> {
  using node_ptr = typename TreeNode<T>::ptr_type;
  using stack_value_type = std::pair<typename TreeNode<T>::ptr_type, bool>;

public:
  InorderIterator<T>(node_ptr root)
      : StackTreeIterator<T, stack_value_type>(root) {
    reset();
  }

  void reset() override {
    StackTreeIterator<T, stack_value_type>::reset();
    if (this->root) {
      this->stack.emplace(this->root, true);
    }
  }

  node_ptr next() override {
    node_ptr res{nullptr};
    while (!this->stack.empty()) {
      auto [top, first] = this->stack.top();
      this->stack.pop();
      if (!first) {
        res = top;
        break;
      } else {
        if (top->right) {
          this->stack.emplace(top->right, true);
        }
        this->stack.emplace(top, false);
        if (top->left) {
          this->stack.emplace(top->left, true);
        }
      }
    }
    return res;
  }
};

template <typename T>
class PostorderIterator
    : public StackTreeIterator<
          T, std::pair<typename TreeNode<T>::ptr_type, bool>> {
  using node_ptr = typename TreeNode<T>::ptr_type;
  using stack_value_type = std::pair<typename TreeNode<T>::ptr_type, bool>;

public:
  PostorderIterator<T>(node_ptr root)
      : StackTreeIterator<T, stack_value_type>(root) {
    reset();
  }

  void reset() override {
    StackTreeIterator<T, stack_value_type>::reset();
    if (this->root) {
      this->stack.emplace(this->root, true);
    }
  }

  node_ptr next() override {
    node_ptr res;
    while (!this->stack.empty()) {
      auto [top, first] = this->stack.top();
      this->stack.pop();
      if (!first) {
        res = top;
        break;
      } else {
        this->stack.emplace(top, false);
        if (top->right) {
          this->stack.emplace(top->right, true);
        }
        if (top->left) {
          this->stack.emplace(top->left, true);
        }
      }
    }
    return res;
  }
};

template <typename T> class LevelOrderIterator : public TreeIterator<T> {
  using node_ptr = typename TreeNode<T>::ptr_type;

public:
  LevelOrderIterator<T>(node_ptr root) : TreeIterator<T>(root) { reset(); }

  virtual ~LevelOrderIterator<T>() {}

  bool has_next() override { return !queue.empty(); }

  void reset() override {
    while (!queue.empty()) {
      queue.pop();
    }
    if (this->root) {
      queue.emplace(this->root);
    }
  }

  node_ptr next() override {
    node_ptr top = queue.front();
    queue.pop();
    if (top->left) {
      queue.emplace(top->left);
    }
    if (top->right) {
      queue.emplace(top->right);
    }
    return top;
  }

private:
  std::queue<node_ptr> queue;
};

template <typename T> class MorrisTreeIterator : public TreeIterator<T> {
  using node_ptr = typename TreeNode<T>::ptr_type;

public:
  MorrisTreeIterator<T>(node_ptr root) : TreeIterator<T>(root) { reset(); }

  bool has_next() override { return bool(curr); }

  void reset() override { curr = this->root; }

protected:
  node_ptr curr{nullptr};
};

template <typename T>
class MorrisPreorderIterator : public MorrisTreeIterator<T> {
  using node_ptr = typename TreeNode<T>::ptr_type;

public:
  MorrisPreorderIterator<T>(node_ptr root) : MorrisTreeIterator<T>(root) {}

  node_ptr next() override {
    node_ptr res{nullptr};
    while (this->curr) {
      if (!this->curr->left) {
        res = this->curr;
        this->curr = this->curr->right;
        break;
      }
      node_ptr prev = this->curr->left;
      while (prev->right && prev->right != this->curr) {
        prev = prev->right;
      }
      if (prev->right == this->curr) {
        prev->right = nullptr;
        this->curr = this->curr->right;
      } else {
        prev->right = this->curr;
        res = this->curr;
        this->curr = this->curr->left;
        break;
      }
    }
    return res;
  }
};

template <typename T>
class MorrisInorderIterator : public MorrisTreeIterator<T> {
  using node_ptr = typename TreeNode<T>::ptr_type;

public:
  MorrisInorderIterator<T>(node_ptr root) : MorrisTreeIterator<T>(root) {}

  node_ptr next() override {
    node_ptr res{nullptr};
    while (this->curr) {
      if (!this->curr->left) {
        res = this->curr;
        this->curr = this->curr->right;
        break;
      }
      node_ptr prev = this->curr->left;
      while (prev->right && prev->right != this->curr) {
        prev = prev->right;
      }
      if (prev->right == this->curr) {
        prev->right = nullptr;
        res = this->curr;
        this->curr = this->curr->right;
        break;
      } else {
        prev->right = this->curr;
        this->curr = this->curr->left;
      }
    }
    return res;
  }
};

template <typename T>
class MorrisPostorderIterator : public MorrisTreeIterator<T> {
  using node = TreeNode<T>;
  using node_ptr = node *;

public:
  MorrisPostorderIterator<T>(node_ptr root) : MorrisTreeIterator<T>(root) {
    reset();
  }

  void reset() override {
    MorrisTreeIterator<T>::reset();
    reverse_curr = nullptr;
    reverse_head = nullptr;
    state = this->root ? Morris : End;
  }

  bool has_next() override { return state != End; }

  node_ptr next() override {
    if (state == Morris) {
      return morris_next();
    }
    return reverse_next();
  }

private:
  static node_ptr reverse_linked_list(node_ptr start) {
    node head{};
    node_ptr curr = start;
    while (curr) {
      node_ptr temp = curr->right;
      curr->right = head.right;
      head.right = curr;
      curr = temp;
    }
    return head.right;
  }

  node_ptr morris_next() {
    node_ptr &curr = this->curr;
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
        node_ptr temp = curr;
        curr = curr->right;
        return start_reverse(temp->left);
      } else {
        prev->right = curr;
        curr = curr->left;
      }
    }
    return start_reverse(this->root);
  }

  node_ptr reverse_next() {
    node_ptr &curr = reverse_curr;
    if (curr == this->root) {
      state = End;
      reverse_linked_list(this->reverse_head);
      return curr;
    }
    if (!curr) {
      state = Morris;
      reverse_linked_list(this->reverse_head);
      return morris_next();
    }
    node_ptr temp = curr;
    curr = curr->right;
    return temp;
  }

  node_ptr start_reverse(node_ptr head) {
    state = Reverse;
    reverse_head = reverse_linked_list(head);
    reverse_curr = reverse_head;
    return reverse_next();
  }

private:
  enum State { Morris, Reverse, End } state{Morris};
  node_ptr reverse_curr{nullptr};
  node_ptr reverse_head{nullptr};
};
} // namespace iterator
} // namespace traversal