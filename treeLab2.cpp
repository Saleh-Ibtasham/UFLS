#include <iostream>
#include <fstream>
#include <stack>
#include <cmath>

using namespace std;

struct node
{
	node *parent;
	int data;
	int height;
	node *left, *right;
};

node *root;

void createTree(void)
{
	root= NULL;
}

node* createNode(int input)
{
	node *temp;
	temp = new node[1];
	temp[0].parent = NULL;
	temp[0].data = input;
	temp[0].height = 0;
	temp[0].left = NULL;
	temp[0].right = NULL;
	return temp;
}

bool compareNodes(node *newNode, node *current)
{
	if(newNode[0].data > current[0].data) return true;
	else return false;
}

void insertNode(node *newNode)
{
	if(root == NULL)
	{
		root = newNode;
		return;
	}
	else
	{
		node * current = root;
		bool flag = false;

		while(1)
		{
			if(compareNodes(newNode, current))
			{
				if(current[0].right != NULL)
				{
					current = current[0].right;
				}
				else
				{
					flag = true;
					break;
				}
			}
			else
			{
				if(current[0].left != NULL)
				{
					current = current[0].left;
				}
				else
				{
					break;
				}
			}
		}

		if(flag)
		{
			current[0].right = newNode;
			newNode[0].parent = current;
			newNode[0].height = newNode[0].parent[0].height + 1;
		}
		else
		{
			current[0].left = newNode;
			newNode[0].parent = current;
			newNode[0].height = newNode[0].parent[0].height + 1;
		}
	}
}

bool readFromFileAndInitialize(char *fileName)
{
	ifstream iFile;
	iFile.open(fileName);
	if(iFile.is_open())
	{
        int i;
        iFile >> i;
		for(int j=0; j<i; j++)
		{
			int input;
			iFile >> input;
			node *newNode = createNode(input);

			insertNode(newNode);
		}

		iFile.close();
	}
	else
	{
		cout << "Could not open file" << endl;
		return false;
	}
	return true;
}


int height;

bool finalFlag = false;

void traverseRecursiveForHeight(node *current)
{
	if(current != NULL)
	{
		traverseRecursiveForHeight(current[0].left);
		traverseRecursiveForHeight(current[0].right);
		if(current[0].height > height)
            height = current[0].height;
	}
}

int findMaxHeight(node *current)
{
    height = 0;
    traverseRecursiveForHeight(current);
//    cout << "here" << endl;
    return height;
}

void checkBalance(int h1, int h2)
{
    if(abs(h1-h2)>1)
        finalFlag = true;
}

void traverseRecursive(node *current)
{
    int h1 = 0;
    int h2 = 0;
	
	if(current != NULL)
	{
		if(current[0].left != NULL)
			h1 = findMaxHeight(current[0].left);
		if(current[0].right != NULL)
			h2 = findMaxHeight(current[0].right);
	}
    checkBalance(h1,h2);

//	cout << current[0].data << endl;

	if(current != NULL)
	{
		traverseRecursive(current[0].left);
//		cout << current[0].data << endl;
		traverseRecursive(current[0].right);
	}
}

void answer()
{
	if(finalFlag)
		cout << "not balanced tree" << endl;
	else
		cout << "balanced tree" << endl;
}

int main ()
{
	createTree();
	if(!readFromFileAndInitialize("case3.txt")) return -1;

    traverseRecursive(root);

    answer();

	return 0;
}

