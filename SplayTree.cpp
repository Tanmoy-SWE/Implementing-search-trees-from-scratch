#include <cstddef>
#include <iostream>
using namespace std;

// An AVL tree node  
class Splay
{
public:
    int key;
    Splay* left, * right;
};

Splay* newNode(int key)
{
    Splay* Node = new Splay();
    Node->key = key;
    Node->left = Node->right = NULL;
    return (Node);
}

 
Splay* rightRotate(Splay* x)
{
    Splay* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

  
Splay* leftRotate(Splay* x)
{
    Splay* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Splay* splay(Splay* root, int key)
{
    // Base cases: root is NULL or 
    // key is present at root  
    if (root == NULL || root->key == key)
        return root;

    // Key lies in left subtree  
    if (root->key > key)
    {
        // Key is not in tree, we are done  
        if (root->left == NULL) return root;

        // Zig-Zig (Left Left)  
        if (root->left->key > key)
        {
            // First recursively bring the 
            // key as root of left-left  
            root->left->left = splay(root->left->left, key);

            // Do first rotation for root,  
            // second rotation is done after else  
            root = rightRotate(root);
        }
        else if (root->left->key < key) // Zig-Zag (Left Right)  
        {
            // First recursively bring 
            // the key as root of left-right  
            root->left->right = splay(root->left->right, key);

            // Do first rotation for root->left  
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        // Do second rotation for root  
        return (root->left == NULL) ? root : rightRotate(root);
    }
    else // Key lies in right subtree  
    {
        // Key is not in tree, we are done  
        if (root->right == NULL) return root;

        // Zag-Zig (Right Left)  
        if (root->right->key > key)
        {
            // Bring the key as root of right-left  
            root->right->left = splay(root->right->left, key);

            // Do first rotation for root->right  
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key)// Zag-Zag (Right Right)  
        {
            // Bring the key as root of  
            // right-right and do first rotation  
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        // Do second rotation for root  
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// The search function for Splay tree.  
// Note that this function returns the  
// new root of Splay Tree. If key is  
// present in tree then, it is moved to root.  
Splay* search(Splay* root, int key)
{
    return splay(root, key);
}

// A utility function to print  
// preorder traversal of the tree.  
// The function also prints height of every node  
void preOrder(Splay* root)
{
    if (root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}