#include<bits/stdc++.h>
using namespace std;

struct node
{
	node *parent;
	int data;
	int degree;
	int level;
	node *left, *right;
	//node *child;
	//node *sibling;
};
int nuberOfInputs,sizeOfTree;
node *root;
bool balanced=true;

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
	temp[0].degree = 0;
	temp[0].left = NULL;
	temp[0].right = NULL;
	//temp[0].child = NULL;
	//temp[0].sibling = NULL;
	return temp;
}

void destroyNode(node *anyNode)
{
	delete [] anyNode;
}

bool compareNodes(node *newNode, node *current)
{
	if(newNode[0].data > current[0].data) return true;
	else return false;
}

//void deleteNode(node *newNode)

void insertNode(node *newNode)
{
	if(root == NULL)
	{
		root = newNode;
		root[0].level=0;

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
			newNode[0].parent[0].degree++;
			//currnt[0].degree++
		}
		else
		{
			current[0].left = newNode;
			newNode[0].parent = current;
			newNode[0].parent[0].degree++;
			//currnt[0].degree++
		}
		newNode[0].level=current[0].level+1;

	}
}
bool readFromFileAndInitialize(char *fileName)
{
	ifstream iFile;
	iFile.open(fileName);
	if(iFile.is_open())
	{

		iFile >> nuberOfInputs;
		for(int i=0; i<nuberOfInputs; i++)
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

stack <node*> qutubStack;

void fillupStack(node *ptr)
{
	while(ptr != NULL)
	{
		qutubStack.push(ptr);
		ptr = ptr[0].left;
	}
}

void traverseInOrder(void)
{
	node *ptr = root;

	fillupStack(ptr);

	while(!qutubStack.empty())
	{
		ptr = qutubStack.top();
		qutubStack.pop();

		cout << ptr[0].data << endl;

		if(ptr[0].right !=NULL)
		{
			ptr = ptr[0].right;
			fillupStack(ptr);
		}
	}
}

void traverseInOrderRecursive(node *current)
{
	if(current != NULL)
	{
		traverseInOrderRecursive(current[0].left);
		cout << current[0].data << endl;
		traverseInOrderRecursive(current[0].right);
	}
}


void traversePreOrder(void){

	node *ptr = root;

	fillupStack(ptr);

	while(!qutubStack.empty())
	{
		ptr = qutubStack.top();

		qutubStack.pop();

		cout << ptr[0].data << endl;

		if(ptr[0].right !=NULL)
		{
			ptr = ptr[0].right;
			fillupStack(ptr);
		}
	}

}
/*
void traversePostOrder(void);
*/

bool searchItem(int searchKey)
{
	//node *parent;
	//int data;
	//int degree;
	//node *left, *right;
	//node *child;
	//node *sibling;
	node *current = root;

	while(current != NULL)
	{
		if(current[0].data == searchKey)
		{
			return true;
		}
		else if(current[0].data < searchKey)
		{
			current = current[0].right;
		}
		else
		{
			current = current[0].left;
		}
	}

	return false;
}
node *z = NULL;
bool searchItemRecursive(int searchKey, node *current)
{
	if(current == NULL) return false;
	else if(searchKey == current[0].data){
		z = current;
		return true;
	}
	else if(searchKey > current[0].data)
	{
		return searchItemRecursive(searchKey, current[0].right);
	}
	else
	{
		return searchItemRecursive(searchKey, current[0].left);
	}
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

int findMin(void)
{
	node *current = root;

	while(current[0].left != NULL)
		current = current[0].left;

	return current[0].data;
}

int findMax(void)
{
	node *current = root;

	while(current[0].right != NULL)
		current = current[0].right;

	return current[0].data;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void deleteLeaf(node *n)
{
    if(n != root)
    {
        node *baap = n[0].parent;
        if(baap[0].left == n)
        {
            baap[0].left = NULL;
        }
        else
        {
            baap[0].right = NULL;
        }
        baap[0].degree--;
    }
    else root = NULL;

    destroyNode(n);
}

void deleteNodeWithOneChild(node *n)
{
    if(n == root)
    {
        node * newRoot;
        if(n[0].left == NULL)
        {
            newRoot = n[0].right;
        }
        else
        {
            newRoot = n[0].left;
        }
        newRoot[0].parent = NULL;
        root = newRoot;
    }
    else
    {
        node * newChild;
        if(n[0].left == NULL)
        {
            newChild = n[0].right;
        }
        else
        {
            newChild = n[0].left;
        }

        node *baap= n[0].parent;
        if(baap[0].left == n)
        {
            baap[0].left = newChild;
        }
        else
        {
            baap[0].right = newChild;
        }
        newChild[0].parent = baap;
    }
    destroyNode(n);
}

node* findMinReturnPointer(node *x)
{
	node *current = x;

	while(current[0].left != NULL)
		current = current[0].left;

	return current;
}

void swapNodeContent(node* n, node* replacer)
{
    int temp = n[0].data;
    n[0].data = replacer[0].data;
    replacer[0].data = temp;
}

void deleteNode(int n)
{
    bool flag = searchItemRecursive(n, root);
    if(!flag)
    {
        cout << n << "maalta not found and not deleted" << endl;
        return;
    }

    if(z[0].left == NULL && z[0].right == NULL)
    {
        deleteLeaf(z);
    }
    else if(z[0].left == NULL || z[0].right == NULL)
    {
        deleteNodeWithOneChild(z);
    }
    else
    {
        node *replacer = findMinReturnPointer(z[0].right);
        swapNodeContent(z, replacer);
        if(replacer[0].left == NULL && replacer[0].right == NULL)
            deleteLeaf(replacer);
        else deleteNodeWithOneChild(replacer);
    }
}

void calculateSizeOfTree(node* current)
{
        if(current==root && root!=NULL)  sizeOfTree=0;
        if(current!=NULL)
        {
                calculateSizeOfTree(current[0].left);
                sizeOfTree++;
                calculateSizeOfTree(current[0].right);

        }
}

//balancing pera start


int currentMax=0;
int findMaxLevel(node* current,int baapLevel)
{
        if(current!=NULL)
        {
                if(abs(current[0].level-baapLevel)>currentMax)
                        currentMax=abs(current[0].level-baapLevel);

                findMaxLevel(current[0].left,baapLevel);
                findMaxLevel(current[0].right,baapLevel);
        }
}


void calculateBalanced(node* current)
{
        int maxLeft=0,maxRight=0;
        currentMax=0;
        findMaxLevel(current[0].left,current[0].level);
        maxLeft=currentMax;

        currentMax=0;
        findMaxLevel(current[0].right,current[0].level);
        maxRight=currentMax;

      //  cout<<abs(maxLeft-maxRight)<<endl;
        if(abs(maxLeft-maxRight)>1)
        {
                balanced=false;
        }
}


 void isTreeBalanced(node* current)
 {
        if(current ==root || root==NULL)  balanced=true;
        if(current!=NULL)
        {
                isTreeBalanced(current[0].left);
                calculateBalanced(current);
                isTreeBalanced(current[0].right);
                //calculateBalanced(current);

        }

}


//balancing pera end

int main ()
{
	createTree();
	if(!readFromFileAndInitialize("case3.txt")) return -1;
        calculateSizeOfTree(root);
        cout<<sizeOfTree<<endl;

        isTreeBalanced(root);
        if(balanced)
        {
                cout<<"Tree is balanced"<<endl;
        }
        else cout<<"Tree is not balanced" <<endl;

	return 0;
}


