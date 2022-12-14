#include <iostream>
#include <limits>
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

  TreeNode *root = createTree(input8);
  bool result = isValidBST(root);
  if (result) {
    cout << "**Valid** Binary Search Tree\n";
  } else {
    cout << "**Invalid** Binary Search Tree\n";
  }

  return 0;
}

bool isValidBST(TreeNode *root) {
  struct Range {
    int begin;
    int end;
  };
  // Every node has 2 constraints: min value and max value that is dependant on the parent node
  map<int, Range> nodeConstraints;
  queue<TreeNode *> nodesQ;
  TreeNode *node;                                  // Used for traversal
  int minValue = std::numeric_limits<int>::min();  // Minimum value for a Node
  int maxValue = std::numeric_limits<int>::max();  // Maximum value for a Node
  int nodeLeftVal;                                 // Value of Left child Node
  int nodeRightVal;                                // Value of Right child Node
  int nodeVal;                                     // Value of Node

  // edge cases

  // if tree is empty
  if (root == nullptr)
    return false;

  // if tree only has one node
  if ((root->left == nullptr) && (root->right == nullptr))
    return true;

  // add the root node to the queue
  nodesQ.push(root);
  // set min and max for the root node
  Range rootRange = {minValue, maxValue};
  // nodeConstraints[root->val] = &rVals;
  nodeConstraints[root->val] = rootRange;
  // cout << "ROOT: Range for " << root->val << " is " << nodeConstraints[root->val].begin << ".." << nodeConstraints[root->val].end << endl;

  // Constraint Rules
  //              (Node)
  //              /    \
  //   (Left Child)    (Right Child)
  //
  //  Left Child: [Min: node's min, Max: node's val]
  //  Right Child: [Min: node's val, Max: node's max]

  // traverse the binary tree

  while (!nodesQ.empty()) {
    node = nodesQ.front();
    nodeVal = node->val;
    // cout << "Node: " << nodeVal << endl;
    nodesQ.pop();
    if (node->left != nullptr) {
      nodesQ.push(node->left);
      nodeLeftVal = node->left->val;
      // cout << "\tLeft Child: " << nodeLeftVal;

      // check constraints

      // if this child node already exists in map,
      // this is not a valid binary search tree
      if (nodeConstraints.count(nodeLeftVal))
        return false;

      // Computing min and max vals of this child node
      // Range: [Min: node's min, Max: node's val]. node refer's to the parent of this child node
      minValue = nodeConstraints[nodeVal].begin;
      maxValue = nodeVal;

      // cout << " Valid Range: " << minValue << ":" << maxValue;

      // Checking if this node's value is out of range
      if ((nodeLeftVal < minValue) || (nodeLeftVal > maxValue))
        return false;

      // cout << " this node is in valid range. ";

      // Set Constraints: Save valid range in map
      Range nodeRange = {minValue, maxValue};
      nodeConstraints[nodeLeftVal] = nodeRange;
      // cout << "Saved Range for node " << nodeLeftVal << " is " << nodeConstraints[nodeLeftVal].begin << ".." << nodeConstraints[nodeLeftVal].end << endl;
    }

    // minValue = 0;
    // maxValue = 0;
    // nodeLeftVal = 0;
    // nodeRightVal = 0;

    // cout << "\t->Range for parent node " << nodeVal << " is " << nodeConstraints[nodeVal][0] << ".." << nodeConstraints[nodeVal][1] << endl;

    if (node->right != nullptr) {
      nodesQ.push(node->right);
      nodeRightVal = node->right->val;
      // cout << "\tRight Child: " << nodeRightVal;

      // check constraints

      // if this child node already exists in map,
      // this is not a valid binary search tree
      if (nodeConstraints.count(nodeRightVal))
        return false;

      // Computing min and max vals of this child node
      // Range: [Min: node's val, Max: node's max]. node refer's to the parent of this child node
      minValue = nodeVal;
      maxValue = nodeConstraints[nodeVal].end;

      // cout << " Valid Range: " << minValue << ":" << maxValue;

      // Checking if this node's value is out of range
      if ((nodeRightVal < minValue) || (nodeRightVal > maxValue))
        return false;

      // cout << " this node is in valid range. ";

      // Set Constraints: Save valid range in map
      Range nodeRange = {minValue, maxValue};
      nodeConstraints[nodeRightVal] = nodeRange;

      // cout << "Saved Range for node " << nodeRightVal << " is " << nodeConstraints[nodeRightVal].begin << ".." << nodeConstraints[nodeRightVal].end << endl;
    }
  }

  // cout << endl;

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
