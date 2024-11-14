#include <iostream>
using namespace std;

// Definition for a binary tree node
class TreeNode {
public:
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        key = value;
        left = right = nullptr;
    }
};

// Function to check if two trees are identical
bool areIdentical(TreeNode* root1, TreeNode* root2) {
    // If both trees are empty, they are identical
    if (root1 == nullptr && root2 == nullptr) {
        return true;
    }

    // If one of the trees is empty and the other is not, they are not identical
    if (root1 == nullptr || root2 == nullptr) {
        return false;
    }

    // Check if the current nodes' data is the same and recursively check left and right subtrees
    return (root1->key == root2->key) && 
           areIdentical(root1->left, root2->left) &&
           areIdentical(root1->right, root2->right);
}

int main() {
    // Example of two identical trees
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);

    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(5);

    // Check if both trees are identical
    if (areIdentical(root1, root2)) {
        cout << "The trees are identical." << endl;
    } else {
        cout << "The trees are not identical." << endl;
    }

    return 0;
}

