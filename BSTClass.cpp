#include <cstddef>
#include <iostream>
class BST
{
	int value;
	BST* left, * right;


public:
	BST(int v)
	{
		value = v;
		left = NULL;
		right = NULL;
	}
	BST() {
		value = NULL;
		left = NULL;
		right = NULL;
	}
	BST* search(BST* root, int key) {
		//This is going to search using inorder traversal
		if (root->value == NULL || root->value == key) {
			return root;
		}

		if (root->value < key) {
			return search(root->right, key);
		}
		return search(root->left, key);
	}

	BST* insert(BST* root, int key) {
		if (!root) {
			return new BST(key);
		}
		if (key > root->value) {
			root->right = insert(root->right, key);
		}
		else {
			root->left = insert(root->left, key);
		}
		return root;
	}

	BST* findMinValue(BST* root) {
		BST* curr = root;

		while (curr && curr->left != NULL) {
			curr = curr->left;
		}
		return curr;
	}
	BST* remove(BST* root, int key)
	{
		if (root == NULL)
		{
			return root;
		}
		if (key < root->value)
		{
			root->left = remove(root->left, key);
		}
		else if (key > root->value)
		{
			root->right = remove(root->right, key);
		}
		else
		{
			if (root->left == NULL)
			{
				BST* temp = root->right;
				free(root);		//Delete the node
				return temp;
			}
			else if (root->right == NULL)
			{
				BST* temp = root->left;
				free(root);
				return temp;
			}

			BST* temp = findMinValue(root->right);

			root->value = temp->value;
			root->right = remove(root->right, temp->value);
		}
		return root;
	}
};