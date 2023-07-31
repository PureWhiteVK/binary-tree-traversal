# Binary Tree Traversal

implement basic binary tree traversal algorithms

- Recursion based Traversal
- Stack based Traversal
- Queue based Traversal (Level Order Traversal)
- Morris Traversal (pre-order,in-order and **post-order**)


## Get Started

**for cpp user**
```bash
cd cpp
cmake -B build -S .
cmake --build build
```
run `traversal_demo` exe to test all traversal algorithm

**for python user**
```bash
python python/main.py
```

**demo**

ascii tree visualization like command `tree` (the upper sub-tree is right sub-tree)
```bash
5
├── 1
└── 3
    ├── 4
    │   ├── 7
    │   └── null
    └── 2
        ├── null
        └── 8
```

iterator based implementation

**cpp**
```c++
#include "traversal/tree.h"
#include "traversal/utils.h"
#include "traversal/iterator.h"

using traversal::iterator::MorrisPostorderIterator

int main() {
  auto v0 = traversal::utils::create_test_tree4();
  auto iter = MorrisPostorderIterator(v0);
  while(iter.has_next()) {
    auto curr = iter.next();
    std::cout << curr << std::endl;
  }
  return 0;
}
```

**python**
```python
from tree import create_test_tree4
from tree_traversal import MorrisPostorderIterator 
root = create_test_tree(4)
for v in MorrisPostorderIterator(root):
    print(v)
```


## post-order traversal with Morris Traversal

the hardest part is using Morris Traversal to implement post-order traversal with $\mathcal{O}(1)$ space complexity and the iterator version for it.

pleace read this [blog](https://purewhitevk.github.io/posts/7a74/#%E5%90%8E%E5%BA%8F%E9%81%8D%E5%8E%86) for more explantion on implementation.  