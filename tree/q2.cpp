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

// Function to split a node in a B-tree
void split_node(BTreeNode* node, int t) {
    // Find the median key
    int median_index = t - 1;
    int median_key = node->keys[median_index];
    
    // Create left and right nodes
    BTreeNode* left_node = new BTreeNode(node->isLeaf);
    BTreeNode* right_node = new BTreeNode(node->isLeaf);

    // Move the first t-1 keys to the left node
    for (int i = 0; i < median_index; ++i) {
        left_node->keys.push_back(node->keys[i]);
    }

    // If it is not a leaf node, move the first t children to the left node
    if (!node->isLeaf) {
        for (int i = 0; i < t; ++i) {
            left_node->children.push_back(node->children[i]);
        }
    }

    // Move the t-1 largest keys and the last t children to the right node
    for (int i = median_index + 1; i < 2 * t - 1; ++i) {
        right_node->keys.push_back(node->keys[i]);
    }

    if (!node->isLeaf) {
        for (int i = t; i < 2 * t; ++i) {
            right_node->children.push_back(node->children[i]);
        }
    }

    // Now the node is split, and the median key must be moved up to the parent
    // Assuming the parent node is available, you would insert the median key into the parent.
    // This step is handled in the insert function or the calling context.

    // Update the original node to reflect the split.
    node->keys.clear(); // Remove all keys from the original node
    node->children.clear(); // Remove all children from the original node
    node->keys.push_back(median_key); // Move the median to the parent
    node->children.push_back(left_node); // Add the left child pointer
    node->children.push_back(right_node); // Add the right child pointer

    // If the node is a leaf, make sure both left and right are also leaves
    if (node->isLeaf) {
        left_node->isLeaf = true;
        right_node->isLeaf = true;
    }
}

// Helper function to print a node's keys (for testing)
void printNode(BTreeNode* node) {
    for (int key : node->keys) {
        cout << key << " ";
    }
    cout << endl;
}

int main() {
    // Example usage
    BTreeNode* root = new BTreeNode(false); // Internal node

    // Inserting keys (simplified for the example)
    root->keys = {10, 20, 30, 40}; // Assuming maximum degree t = 3

    // Adding some children (in practice, these would be populated with actual BTreeNode objects)
    root->children.push_back(new BTreeNode(true)); // Child 1 (leaf node)
    root->children.push_back(new BTreeNode(true)); // Child 2 (leaf node)
    root->children.push_back(new BTreeNode(true)); // Child 3 (leaf node))
    
    // Split the node
    split_node(root, 3);

    // Print the result
    cout << "Root after split: ";
    printNode(root);

    // Output the keys of the left and right child nodes
    cout << "Left node: ";
    printNode(root->children[0]);
    cout << "Right node: ";
    printNode(root->children[1]);

    return 0;
}

