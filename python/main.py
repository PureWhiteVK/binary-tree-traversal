from tree_visualize import visualize_ascii
from tree import create_test_tree4, TreeNode
from tree_traversal import (
    preorder_traversal, inorder_traversal, postorder_traversal,
    PreorderIterator, InorderIterator, PostorderIterator,
    MorrisPreorderIterator, MorrisInorderIterator, MorrisPostorderIterator,
    LevelOrderIterator,
)

from typing import Callable


def visit(node: 'TreeNode'):
    print(f'{str(node)} ', end='')


def invoke_function(func: Callable, root: 'TreeNode'):
    print(f'{func.__qualname__} [ ', end='')
    func(root, visit)
    print(']')


def invoke_iterator(cls: type, root: 'TreeNode'):
    instance = cls(root)
    print(f'{cls.__qualname__} [ ', end='')
    for v in instance:
        visit(v)
    print(']')


r = create_test_tree4()
visualize_ascii(r)

print(f'[ preorder ]')
invoke_function(preorder_traversal, r)
invoke_iterator(PreorderIterator, r)
invoke_iterator(MorrisPreorderIterator, r)

print(f'[ inorder ]')
invoke_function(inorder_traversal, r)
invoke_iterator(InorderIterator, r)
invoke_iterator(MorrisInorderIterator, r)

print(f'[ postorder ]')
invoke_function(postorder_traversal, r)
invoke_iterator(PostorderIterator, r)
invoke_iterator(MorrisPostorderIterator, r)

print(f'[level order]')
invoke_iterator(LevelOrderIterator, r)
