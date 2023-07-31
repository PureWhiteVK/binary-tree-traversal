#include "traversal/iterative.h"
#include "traversal/iterator.h"
#include "traversal/recursive.h"
#include "traversal/tree.h"
#include "traversal/utils.h"

#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>

// #define STR(x) #x
#define INVOKE_FUNCTION(T, x, y) invoke_function<T>(#x, x<T>, y);
#define INVOKE_ITERATOR(T, x, y) invoke_iterator<T>(#x, x<T>(y));

using traversal::TreeNode;
using traversal::iterator::TreeIterator;

template <typename T> using TreeNodePtr = TreeNode<T> *;

template <typename T> void visit(TreeNodePtr<T> node) {
  std::cout << " " << *node;
}

template <typename T>
void invoke_iterator(std::string &&name, TreeIterator<T> &&iterator) {
  iterator.reset();
  std::cout << name << " [";
  while (iterator.has_next()) {
    auto v = iterator.next();
    visit(v);
  }
  std::cout << " ]" << std::endl;
}

template <typename T>
using NodeVisitCallback = std::function<void(TreeNodePtr<T>)>;

template <typename T>
using TraversalFunction =
    std::function<void(TreeNodePtr<T>, NodeVisitCallback<T>)>;

template <typename T>
void invoke_function(std::string &&name, TraversalFunction<T> func,
                     TreeNodePtr<T> root) {
  std::cout << name << " [";
  func(root, visit<T>);
  std::cout << " ]" << std::endl;
}

int main() {
  auto v0 = traversal::utils::create_test_tree4();

  traversal::utils::pretty_print<>(v0.get());

  std::cout << "[ preorder ]" << std::endl;
  traversal::utils::print_callstack(v0.get(), traversal::utils::Preorder);
  INVOKE_FUNCTION(int, traversal::recursive::preorder, v0.get());
  INVOKE_FUNCTION(int, traversal::iterative::preorder, v0.get());
  INVOKE_FUNCTION(int, traversal::iterative::morris_preorder, v0.get());
  INVOKE_ITERATOR(int, traversal::iterator::PreorderIterator, v0.get());
  INVOKE_ITERATOR(int, traversal::iterator::MorrisPreorderIterator, v0.get());

  std::cout << "[ inorder ]" << std::endl;
  traversal::utils::print_callstack(v0.get(), traversal::utils::Inorder);
  INVOKE_FUNCTION(int, traversal::recursive::inorder, v0.get());
  INVOKE_FUNCTION(int, traversal::iterative::inorder, v0.get());
  INVOKE_FUNCTION(int, traversal::iterative::morris_inorder, v0.get());
  INVOKE_ITERATOR(int, traversal::iterator::InorderIterator, v0.get());
  INVOKE_ITERATOR(int, traversal::iterator::MorrisInorderIterator, v0.get());

  std::cout << "[ postorder ]" << std::endl;
  traversal::utils::print_callstack(v0.get(), traversal::utils::Postorder);
  INVOKE_FUNCTION(int, traversal::recursive::postorder, v0.get());
  INVOKE_FUNCTION(int, traversal::recursive::postorder2, v0.get());
  INVOKE_FUNCTION(int, traversal::recursive::postorder3, v0.get());
  INVOKE_FUNCTION(int, traversal::iterative::postorder, v0.get());
  INVOKE_FUNCTION(int, traversal::iterative::morris_postorder, v0.get());
  INVOKE_ITERATOR(int, traversal::iterator::PostorderIterator, v0.get());
  INVOKE_ITERATOR(int, traversal::iterator::MorrisPostorderIterator, v0.get());

  std::cout << "[ level order ]" << std::endl;
  INVOKE_FUNCTION(int, traversal::iterative::level_order, v0.get());
  INVOKE_ITERATOR(int, traversal::iterator::LevelOrderIterator, v0.get());
  return 0;
}