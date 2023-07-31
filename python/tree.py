from typing import Any, Optional


class TreeNode:
    def __init__(self, value: Any, left: Optional['TreeNode'] = None, right: Optional['TreeNode'] = None) -> None:
        self.val = value
        self.left = left
        self.right = right

    def __str__(self) -> str:
        return str(self.val)

    def __repr__(self) -> str:
        return f'TreeNode({self.val})'

def create_test_tree1() -> 'TreeNode':
    v0 = TreeNode(5)
    v1 = TreeNode(3)
    v2 = TreeNode(1)
    v3 = TreeNode(2)
    v4 = TreeNode(4)
    v5 = TreeNode(0)
    v6 = TreeNode(6)
    v7 = TreeNode(8)
    v8 = TreeNode(7)
    v0.left = v1
    v0.right = v2
    v1.left = v3
    v1.right = v4
    v2.left = v5
    v2.right = v6
    v3.left = v7
    v4.right = v8
    return v0


def create_test_tree2() -> 'TreeNode':
    v0 = TreeNode(1)
    v1 = TreeNode(2)
    v2 = TreeNode(3)
    v0.right = v1
    v1.left = v2
    return v0


def create_test_tree3() -> Optional['TreeNode']:
    return None

def create_test_tree4() -> 'TreeNode':
    v0 = TreeNode(5)
    v1 = TreeNode(3)
    v2 = TreeNode(1)
    v3 = TreeNode(2)
    v4 = TreeNode(4)
    v5 = TreeNode(8)
    v6 = TreeNode(7)
    v0.left = v1
    v0.right = v2
    v1.left = v3
    v1.right = v4
    v3.left = v5
    v4.right = v6
    return v0