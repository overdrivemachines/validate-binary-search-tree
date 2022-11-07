#include <iostream>
#include <map>
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
bool isValidBST(TreeNode *root);

int main(int argc, char const *argv[]) {
  vector<int> input1 = {3, 9, 20, NULL, NULL, 15, 7};
  vector<int> input2 = {1};
  vector<int> input3 = {1, 7, 9, 2, 6, NULL, 9, NULL, NULL, 5, 11, 5, NULL};
  vector<int> input4 = {1, 2, 3, 4, 5};

  vector<int> input5 = {2, 1, 3};             // valid binary search tree
  vector<int> input6 = {17, 5, NULL, 1, 15};  // valid binary search tree

  vector<int> input7 = {25, 5, NULL, NULL, 15, 10, 30};
  vector<int> input8 = {25, 5, NULL, NULL, 15, 4, 20};

  TreeNode *root = createTree(input1);
  isValidBST(root);

  return 0;
}

bool isValidBST(TreeNode *root) {
  // Every node has 2 constraints: min value and max value that is dependant on the parent node
  map<int, int[2]> nodeConstraint;

  queue<TreeNode *> nodesQ;

  TreeNode *node;  // used for traversal

  // edge cases

  // if tree is empty
  if (root == nullptr)
    return false;

  // if tree only has one node
  if ((root->left == nullptr) && (root->right == nullptr))
    return true;

  nodesQ.push(root);
  // traverse the binary tree

  while (!nodesQ.empty()) {
    node = nodesQ.front();
    cout << node->val << " ";
    nodesQ.pop();
    if (node->left != nullptr) {
      nodesQ.push(node->left);
    }

    if (node->right != nullptr) {
      nodesQ.push(node->right);
    }
  }

  cout << endl;

  return true;
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
