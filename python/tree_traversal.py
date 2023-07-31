from typing import Iterator, Any, Optional, Callable
from enum import IntEnum, auto
from tree import TreeNode


class LevelOrderIterator(Iterator):
    def __init__(self, root: Optional['TreeNode']) -> None:
        super().__init__()
        self.__root = root

    def __iter__(self) -> 'LevelOrderIterator':
        # 初始化迭代器的状态
        self.__queue = [(self.__root, 0)] if self.__root is not None else []
        return self

    def __next__(self) -> Any:
        # 弹出栈的第一个元素
        queue = self.__queue
        if len(queue) == 0:
            raise StopIteration()
        top, depth = queue.pop(0)
        if top.left is not None:
            queue.append((top.left, depth + 1))
        if top.right is not None:
            queue.append((top.right, depth + 1))
        return top.val


class PreorderIterator(Iterator):
    def __init__(self, root: Optional['TreeNode']) -> None:
        super().__init__()
        self.__root = root

    def __iter__(self) -> 'PreorderIterator':
        self.__stack = [self.__root] if self.__root is not None else []
        return self

    def __next__(self) -> Any:
        stack = self.__stack
        if len(stack) == 0:
            raise StopIteration()
        top = stack.pop()
        if top.right is not None:
            stack.append(top.right)
        if top.left is not None:
            stack.append(top.left)
        return top.val


class InorderIterator(Iterator):
    def __init__(self, root: Optional['TreeNode']) -> None:
        super().__init__()
        self.__root = root

    def __iter__(self) -> 'InorderIterator':
        # 初始化迭代器的状态
        self.__stack = [(self.__root, True)]
        return self

    def __next__(self) -> Any:
        # 弹出栈的第一个元素
        stack = self.__stack
        while len(stack) != 0:
            top, first_visit = stack.pop()
            if top is None:
                continue
            if not first_visit:
                return top.val
            else:
                stack.append((top.right, True))
                stack.append((top, False))
                stack.append((top.left, True))
        raise StopIteration()


class PostorderIterator(Iterator):
    def __init__(self, root: Optional['TreeNode']) -> None:
        super().__init__()
        self.__root = root

    def __iter__(self) -> 'InorderIterator':
        # 初始化迭代器的状态
        self.__stack = [(self.__root, True)]
        return self

    def __next__(self) -> Any:
        # 弹出栈的第一个元素
        stack = self.__stack
        while len(stack) != 0:
            top, first_visit = stack.pop()
            if top is None:
                continue
            if not first_visit:
                return top.val
            else:
                stack.append((top, False))
                stack.append((top.right, True))
                stack.append((top.left, True))
        raise StopIteration()


def preorder_traversal(root: Optional['TreeNode'], visit:Callable):
    def recursive(node: Optional['TreeNode']):
        if node is None:
            return
        visit(node)
        recursive(node.left)
        recursive(node.right)
    recursive(root)


def inorder_traversal(root: Optional['TreeNode'], visit:Callable):
    def recursive(node: Optional['TreeNode']):
        if node is None:
            return
        recursive(node.left)
        visit(node)
        recursive(node.right)
    recursive(root)


def postorder_traversal(root: Optional['TreeNode'], visit:Callable):
    def recursive(node: Optional['TreeNode']):
        if node is None:
            return
        recursive(node.left)
        recursive(node.right)
        visit(node)
    recursive(root)


class MorrisPreorderIterator(Iterator):
    def __init__(self, root: Optional['TreeNode']) -> None:
        super().__init__()
        self.__root = root
        self.__curr: Optional['TreeNode'] = None

    def __iter__(self) -> 'MorrisPreorderIterator':
        self.__curr = self.__root
        return self

    def __next__(self) -> Any:
        curr = self.__curr
        while curr is not None:
            if curr.left is None:
                self.__curr = curr.right
                return curr.val
            prev = curr.left
            while prev.right is not None and prev.right != curr:
                prev = prev.right
            if prev.right == curr:
                prev.right = None
                curr = curr.right
            else:
                prev.right = curr
                self.__curr = curr.left
                return curr.val
        raise StopIteration()


class MorrisInorderIterator(Iterator):
    def __init__(self, root: Optional['TreeNode']) -> None:
        super().__init__()
        self.__root = root
        self.__curr: Optional['TreeNode'] = None

    def __iter__(self) -> 'MorrisInorderIterator':
        self.__curr = self.__root
        return self

    def __next__(self) -> Any:
        curr = self.__curr
        while curr is not None:
            if curr.left is None:
                self.__curr = curr.right
                return curr.val
            prev = curr.left
            while prev.right is not None and prev.right != curr:
                prev = prev.right
            if prev.right == curr:
                prev.right = None
                self.__curr = curr.right
                return curr.val
            else:
                prev.right = curr
                curr = curr.left
        raise StopIteration()


class MorrisPostorderIterator(Iterator):

    class State(IntEnum):
        Morris = auto()
        Reverse = auto()
        End = auto()

    def __init__(self, root: Optional['TreeNode']) -> None:
        super().__init__()
        self.__root = root
        self.__morris_curr: Optional['TreeNode'] = None
        self.__reverse_curr: Optional['TreeNode'] = None
        self.__reverse_head: Optional['TreeNode'] = None
        self.__state = MorrisPostorderIterator.State.Morris

    def __iter__(self) -> 'MorrisPostorderIterator':
        self.__morris_curr = self.__root
        self.__reverse_curr = None
        self.__reverse_head = None
        self.__state = MorrisPostorderIterator.State.Morris \
            if self.__root is not None else MorrisPostorderIterator.State.End
        return self

    # reverse linked list
    @staticmethod
    def __reverse(start: 'TreeNode') -> 'TreeNode':
        head = TreeNode(-1)
        curr = start
        while curr != None:
            t = curr.right
            curr.right = head.right
            head.right = curr
            curr = t
        return head.right

    def __start_reverse(self, head: 'TreeNode') -> Any:
        self.__state = MorrisPostorderIterator.State.Reverse
        self.__reverse_head = self.__reverse(head)
        self.__reverse_curr = self.__reverse_head
        return self.__reverse_next()

    def __morris_next(self) -> Any:
        curr = self.__morris_curr
        while curr is not None:
            if curr.left is None:
                curr = curr.right
                continue
            prev = curr.left
            while prev.right is not None and prev.right != curr:
                prev = prev.right
            if prev.right == curr:
                prev.right = None
                self.__morris_curr = curr.right
                return self.__start_reverse(curr.left)
            else:
                prev.right = curr
                curr = curr.left
        return self.__start_reverse(self.__root)

    def __reverse_next(self) -> Any:
        curr = self.__reverse_curr
        if curr == self.__root:
            self.__state = MorrisPostorderIterator.State.End
            self.__reverse(self.__reverse_head)
            return curr.val
        if curr is None:
            self.__state = MorrisPostorderIterator.State.Morris
            self.__reverse(self.__reverse_head)
            return self.__morris_next()
        self.__reverse_curr = self.__reverse_curr.right
        return curr.val

    def __next__(self) -> Any:
        if self.__state == MorrisPostorderIterator.State.End:
            raise StopIteration()
        if self.__state == MorrisPostorderIterator.State.Reverse:
            return self.__reverse_next()
        return self.__morris_next()

