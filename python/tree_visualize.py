from tree import TreeNode
from typing import Optional


# def visualize(root: 'TreeNode', name='binary tree') -> 'graphviz.Digraph':
#     graph = graphviz.Digraph(name)
#     # node_attrs = {'shape': 'none'}
#     node_attrs = {}
#     edge_attrs = {'dir': 'none'}
#     hidden_node_attrs = {
#         # 'style':'invis',
#         **node_attrs
#     }
#     hidden_edge_attrs = {'style': 'invis', **edge_attrs}

#     def id_allocator(start=0):
#         _id = start

#         def allocate() -> int:
#             nonlocal _id
#             curr_id = _id
#             _id += 1
#             return curr_id
#         return allocate

#     allocator = id_allocator()

#     def recursive(node: 'TreeNode', parent_id: int = -1) -> None:
#         if not node and parent_id == -1:
#             return
#         curr_id = allocator()
#         graph.node(name=f'n{curr_id}', label=str(
#             node) if node else None, **(node_attrs if node else hidden_node_attrs))
#         if parent_id != -1:
#             graph.edge(tail_name=f'n{parent_id}',
#                        head_name=f'n{curr_id}', **(edge_attrs if node else hidden_edge_attrs))
#         if not node or (not node.left and not node.right):
#             return
#         recursive(node.left, curr_id)
#         recursive(node.right, curr_id)

#     recursive(root)
#     return graph


def visualize_ascii(root: 'TreeNode'):
    def recursive(node: 'TreeNode', prefix: str = '', is_right: bool = False):
        if not node:
            print(f'{prefix}null')
            return
        print(f'{prefix}{str(node)}')
        if prefix:
            if is_right:
                prefix = prefix[:-4] + '│   '
            else:
                prefix = prefix[:-4] + '    '
        if node.right or node.left:
            recursive(node.right, prefix + '├── ',True)
            recursive(node.left,  prefix + '└── ',False)
    recursive(root)

if __name__ == "__main__":
    from tree import create_test_tree4
    r = create_test_tree4()
    visualize_ascii(r)
    # g = visualize(r)
    # g.format = 'png'
    # g.view(cleanup=True, quiet=True, quiet_view=True)
