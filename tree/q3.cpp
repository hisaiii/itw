#include <iostream>
#include <vector>
using namespace std;

// Structure for B-Tree node
class BTreeNode {
public:
    bool isLeaf;                 // True if the node is a leaf, false if it's an internal node
    vector<int> keys;            // Keys in the node
    vector<BTreeNode*> children; // Child pointers (size is one more than keys)

    BTreeNode(bool leaf) {
        isLeaf = leaf;
    }
};

// Function to find the k-th smallest element in a B-tree using in-order traversal
int find_kth_smallest(BTreeNode* root, int k, int& count) {
    if (root == nullptr) return -1; // Return -1 if the tree is empty

    // Traverse all children of the node (except the last child)
    for (int i = 0; i < root->keys.size(); ++i) {
        // If the node is not a leaf, recurse down its left child
        if (!root->isLeaf) {
            int result = find_kth_smallest(root->children[i], k, count);
            if (result != -1) return result;  // If result is found, return it
        }

        // Visit the current key
        count++;
        if (count == k) {
            return root->keys[i]; // Return the k-th smallest element
        }
    }

    // If it's not a leaf node, traverse the rightmost child (for the last key in the node)
    if (!root->isLeaf) {
        return find_kth_smallest(root->children[root->children.size() - 1], k, count);
    }

    return -1;  // Return -1 if the k-th smallest element isn't found (invalid k)
}

// Wrapper function to call find_kth_smallest with an initial count of 0
int get_kth_smallest(BTreeNode* root, int k) {
    int count = 0;  // Initialize count to 0 for in-order traversal
    return find_kth_smallest(root, k, count);
}

// Helper function to print the node's keys (for testing)
void printNode(BTreeNode* node) {
    for (int key : node->keys) {
        cout << key << " ";
    }
    cout << endl;
}

int main() {
    // Example usage of B-Tree and find_kth_smallest function
    BTreeNode* root = new BTreeNode(false); // Internal node

    // Inserting keys into the root node
    root->keys = {10, 20, 30};
    
    // Adding children nodes to root (for simplicity, adding leaf nodes with keys)
    root->children.push_back(new BTreeNode(true));
    root->children.push_back(new BTreeNode(true));
    root->children.push_back(new BTreeNode(true));
    
    root->children[0]->keys = {1, 5};
    root->children[1]->keys = {15};
    root->children[2]->keys = {25, 35};

    // Find the 3rd smallest element
    int k = 3;
    int result = get_kth_smallest(root, k);
    cout << "The " << k << "-th smallest element is: " << result << endl;

    return 0;
}

