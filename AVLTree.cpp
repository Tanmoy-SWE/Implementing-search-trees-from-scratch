#include <cstddef>
#include <iostream>
class AVL {
public:
	int key;
	AVL* right;
	AVL* left;
	int h;

	//I am not sure about this one
	int max(int a, int b) {
		return (a > b) ? a : b;
	}

	int height(AVL* N)
	{
		if (N == NULL)
			return 0;
		return N->h;
	}


	AVL* newNode(int key) {
		AVL* Splay = new AVL();
		Splay->key = key;
		Splay->left = NULL;
		Splay->right = NULL;
		Splay->h = 1;

		return (Splay);
	}

	AVL* rightRotate(AVL* y) {
		AVL* x = y->left;
		AVL* T2 = x->right;

		x->right = y;
		y->left = T2;

		y->h = max(height(y->left),
			height(y->right)) + 1;
		x->h = max(height(x->left),
			height(x->right)) + 1;
		return x;
	}


	AVL* leftRotate(AVL* x)
	{
		AVL* y = x->right;
		AVL* T2 = y->left;

		y->left = x;
		x->right = T2;

		x->h = max(height(x->left),
			height(x->right)) + 1;
		y->h = max(height(y->left),
			height(y->right)) + 1;

		return y;
	}

	int getBalance(AVL* N)
	{
		if (N == NULL)
			return 0;
		return height(N->left) - height(N->right);
	}

	AVL* insert(AVL* Splay, int key)
	{

		if (Splay == NULL)
			return(newNode(key));

		if (key < Splay->key)
			Splay->left = insert(Splay->left, key);
		else if (key > Splay->key)
			Splay->right = insert(Splay->right, key);
		else // Equal keys are not allowed in BST  
			return Splay;


		Splay->h = 1 + max(height(Splay->left),
			height(Splay->right));

		// Get the balance factor of this ancestor node to check whether this node became unbalanced 
		//	
			//
		int balance = getBalance(Splay);

		if (balance > 1 && key < Splay->left->key)
			return rightRotate(Splay);

		if (balance < -1 && key > Splay->right->key)
			return leftRotate(Splay);

		if (balance > 1 && key > Splay->left->key)
		{
			Splay->left = leftRotate(Splay->left);
			return rightRotate(Splay);
		}

		// Right Left 
		if (balance < -1 && key < Splay->right->key)
		{
			Splay->right = rightRotate(Splay->right);
			return leftRotate(Splay);
		}
		return Splay;
	}

	AVL* minValueNode(AVL* Splay)
	{
		AVL* current = Splay;

		/* loop down to find the leftmost leaf */
		while (current->left != NULL)
			current = current->left;

		return current;
	}


	AVL* deleteNode(AVL* root, int key)
	{

		// STEP 1: PERFORM STANDARD BST DELETE  
		if (root == NULL)
			return root;

		// If the key to be deleted is smaller  
		// than the root's key, then it lies 
		// in left subtree  
		if (key < root->key)
			root->left = deleteNode(root->left, key);

		// If the key to be deleted is greater  
		// than the root's key, then it lies  
		// in right subtree  
		else if (key > root->key)
			root->right = deleteNode(root->right, key);

		// if key is same as root's key, then  
		// This is the node to be deleted  
		else
		{
			// node with only one child or no child  
			if ((root->left == NULL) ||
				(root->right == NULL))
			{
				AVL* temp = root->left ?
					root->left :
					root->right;

				// No child case  
				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else // One child case  
					*root = *temp; // Copy the contents of  
								   // the non-empty child  
				free(temp);
			}
			else
			{
				// node with two children: Get the inorder  
				// successor (smallest in the right subtree)  
				AVL* temp = minValueNode(root->right);

				// Copy the inorder successor's  
				// data to this node  
				root->key = temp->key;

				// Delete the inorder successor  
				root->right = deleteNode(root->right,
					temp->key);
			}
		}

		// If the tree had only one node 
		// then return  
		if (root == NULL)
			return root;

		// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
		root->h = 1 + max(height(root->left),
			height(root->right));

		// STEP 3: GET THE BALANCE FACTOR OF  
		// THIS NODE (to check whether this  
		// node became unbalanced)  
		int balance = getBalance(root);

		// If this node becomes unbalanced,  
		// then there are 4 cases  

		// Left Left Case  
		if (balance > 1 &&
			getBalance(root->left) >= 0)
			return rightRotate(root);

		// Left Right Case  
		if (balance > 1 &&
			getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		// Right Right Case  
		if (balance < -1 &&
			getBalance(root->right) <= 0)
			return leftRotate(root);

		// Right Left Case  
		if (balance < -1 &&
			getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}
};