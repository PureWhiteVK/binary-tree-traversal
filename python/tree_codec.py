from tree import TreeNode
from abc import ABC, abstractmethod
from typing import Optional


class Codec(ABC):
    def __init__(self) -> None:
        super().__init__()

    @abstractmethod
    def serialize(self, root: Optional['TreeNode']) -> str:
        raise NotImplementedError()

    @abstractmethod
    def deserialize(self, data: str) -> Optional['TreeNode']:
        raise NotImplementedError()


class TreeCodec(Codec):
    def __init__(self) -> None:
        super().__init__()

    def serialize(self, root: Optional['TreeNode']) -> str:
        if root is None:
            return '[]'
        tokens = []
        queue = [root]
        while len(queue) != 0:
            n = len(queue)
            # loop through current layer
            while n > 0:
                curr = queue.pop(0)
                n-=1
                if curr is not None:
                    # 或者直接判断 curr 是不是最后一个元素，也行
                    tokens.append(str(curr))
                    # 如果此处可以判断出当前在最后一层，可以减少叶子结点的 null
                    queue.append(curr.left)
                    queue.append(curr.right)
                else:
                    tokens.append('null')
        while tokens[-1] == 'null':
            tokens.pop()
        return f'[{",".join(tokens)}]'

    def deserialize(self, data: str) -> Optional['TreeNode']:
        print(data)
        data = data[1:-1].split(',')
        print(data)
        n = len(data)
        if n == 0:
            return None
        i = 1
        root = TreeNode(int(data[0]))
        n_children = 2
        n_next_children = 0
        queue = [ root ]
        parent = None
        node = None
        while i < n:
            # load current layer
            while n_children > 0:
                val = data[i]
                i+=1
                if val == 'null':
                    node = None
                else:
                    node = TreeNode(int(val))
                    n_next_children += 2
                    queue.append(node)
                if n_children & 1 == 0:
                    parent = queue.pop(0)
                    parent.left = node
                else:
                    parent.right = node
                n_children -= 1
            n_children = n_next_children
            n_next_children = 0
        return root

        

    


if __name__ == "__main__":
    from tree import create_test_tree4, create_test_tree3
    from tree_visualize import visualize
    from tree_traversal import MorrisInorderIterator
    r = create_test_tree4()
    for v in MorrisInorderIterator(r):
        print(v,end='')
    print()
    print(TreeCodec().serialize(r))
    # v = codec.deserialize(codec.serialize(r))
    g = visualize(r)
    # g.save()
    g.format = 'svg'
    g.view(cleanup=True,quiet=True,quiet_view=True)
