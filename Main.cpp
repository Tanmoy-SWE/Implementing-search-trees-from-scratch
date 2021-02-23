#include <iostream>
#include <fstream>
using namespace std;

int main()
{ 

	int selection = 0;
	string input1;
	string input2;
	string outputBST ;
	string outputAVL ;
	string outputSplay ;
	string outputStats ;
	cout << "Enter First Input File: ";
	cin >> input1;
	ifstream inputFile1(input1);
	inputFile1.open(input1);
	cout << "Enter Second Input File: ";
	cin >> input2;
	ifstream inputFile2(input2);
	inputFile2.open(input2);
	cout << "Enter First Output File: ";
	cin >> outputBST;
	ofstream outputFile1(outputBST);
	cout << "Enter Second Output File: ";
	cin >> outputAVL;
	ofstream outputFile2(outputAVL);
	cout << "Enter Third Output File: ";
	cin >> outputSplay;
	ofstream outputFile3(outputSplay);
	cout << "Enter Fourth Output File: ";
	cin >> outputStats;
	ofstream outputFile4(outputStats);
	cout << "Welcome to the tree creation tool!" << endl
		<< "1. BST" << endl
		<< "2. AVL Tree" << endl
		<< "3. Splay Tree" << endl
		<< "4. Quit" << endl;
	cout << "Choose one of the following:";
	cin >> selection;
	while (true)
	{
		switch (selection)
		{
		case 1:
			outputFile1.open(outputBST);
			//bst class
			break;
		case 2:
			outputFile2.open(outputAVL);
			//avl tree class
			break;
		case 3:
			outputFile3.open(outputSplay);
			//splay tree
			break;
		case 4:
			cout << "Thank you for using the program!" << endl;
			return 0;
			break;
		default:
			cout << "Enter correct option!" << endl;
			break;
		}
	}
		 
}
