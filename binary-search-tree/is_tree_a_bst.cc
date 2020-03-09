#include <memory>
#include <stack>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::stack;

bool IsBinaryTreeBSTHelper(const unique_ptr<BinaryTreeNode<int>>& tree, stack<int>& s){
  if(!tree) {
    return true;
  }

  bool ret = true;

  ret &= IsBinaryTreeBSTHelper(tree->left, s);

  if(s.size()) {
    ret &= s.top() <= tree->data;
    s.pop();
  }
  s.push(tree->data);

  ret &= IsBinaryTreeBSTHelper(tree->right, s);

  return ret;
}


bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if(tree == nullptr) {
    return true;
  }
  stack<int> s;

  return IsBinaryTreeBSTHelper(tree, s);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}

