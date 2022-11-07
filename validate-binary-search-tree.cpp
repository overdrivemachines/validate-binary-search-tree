#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *createTree(vector<int> input);

int main(int argc, char const *argv[]) {
  return 0;
}

// create a tree given a vector of input elements
// returns root of tree
TreeNode *createTree(vector<int> input) {
  queue<TreeNode *> nodes;
  TreeNode *node, *parent, *root;

  if (input.size() == 0) {
    return nullptr;
  }

  // First element of input vector will always be the root node
  root = new TreeNode(input[0]);

  if (input.size() == 1) {
    return root;
  }

  parent = root;
  bool isLeftFilled = false;

  for (int i = 1; i < input.size(); i++) {
    // cout << input[i] << ": ";
    if (input[i] != NULL) {
      node = new TreeNode(input[i]);
      // add node to queue
      nodes.push(node);
      if (!isLeftFilled) {
        parent->left = node;
        // cout << "adding " << node->val << " to left of " << parent->val << endl;
        isLeftFilled = true;
      } else {
        parent->right = node;
        // cout << "adding " << node->val << " to right of " << parent->val << endl;
        parent = nodes.front();
        // cout << "new parent: " << parent->val << endl;
        nodes.pop();
        isLeftFilled = false;
      }
      // cout << "adding " << node->val << " to " << parent->val << endl;
    } else {
      if (!isLeftFilled) {
        parent->left = nullptr;
        isLeftFilled = true;
        // cout << "adding null to left of " << parent->val << endl;
      } else {
        parent->right = nullptr;
        // cout << "adding null to right of " << parent->val << endl;
        parent = nodes.front();
        // cout << "new parent: " << parent->val << endl;
        nodes.pop();
        isLeftFilled = false;
      }
    }
  }

  return root;
}
