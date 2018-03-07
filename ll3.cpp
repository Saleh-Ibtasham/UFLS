#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
	int data;
	Node *next, *previous;
};

Node *head, *tail;

void createLinkedList(void)
{
	head = NULL;
	tail = NULL;
}

Node* createNode(int data)
{
	Node *temp;
	temp = new Node[1];
	
	temp[0].data = data;
	temp[0].next = NULL;
	temp[0].previous = NULL;
	return temp;
}

void deleteNode(Node *anyNode)
{
	delete [] anyNode;
}

bool checkInvalidityOfNode(Node *node)
{
	if(node == NULL) return true;
	else return false;
}

void deleteList(void)
{
	if(checkInvalidityOfNode(head)) return;
	while (head!=tail)
	{
		Node *current = head;
		head = current[0].next;
		deleteNode(current);
	}
	deleteNode(head);
	head = NULL;
	tail = NULL;
}

void printNode (Node *node)
{
	if(checkInvalidityOfNode(node)) cout << "Eikhane maal nai" << endl;
	else cout << node[0].data << endl;
}

//==
void traverseForward(void)
{
	cout << "In Forward Direction The List Contains" << endl;
	
	for(Node *current = head; current != NULL; current= current[0].next)
	{
		printNode(current);
	}
}

void traverseBackward(void)
{
	cout << "In Backward Direction The List Contains" << endl;
	
	for(Node *current = tail; current != NULL; current= current[0].previous)
	{
		printNode(current);
	}
}
//==

Node* SearchForGreaterGetPrevious(int searchKey)
{
	for(Node *current = head; current != NULL; current= current[0].next)
	{
		if(current[0].data >= searchKey)
		{
			return current[0].previous;
		}
	}
	return tail; /*if we cannot find the item, we return tail as a token*/
}

Node* SearchForNext(int searchKey)
{
	for(Node *current = head; current != NULL; current= current[0].next)
	{
		if(current[0].data == searchKey)
		{
			return current[0].next;
		}
	}
	return NULL;
}

Node* SearchForPrevious(int searchKey)
{
	for(Node *current = head; current != NULL; current= current[0].next)
	{
		if(current[0].data == searchKey)
		{
			return current[0].previous;
		}
	}
	return NULL;
}

Node* SearchItem(int searchKey)
{
	for(Node *current = head; current != NULL; current= current[0].next)
	{
		if(current[0].data == searchKey)
		{
			return current;
		}
	}
	return NULL;
}

//==

void insertAtEnd(Node *newNode)
{
	if(checkInvalidityOfNode(head) && checkInvalidityOfNode(tail))
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		newNode[0].previous = tail;
		tail[0].next = newNode;
		tail = newNode;
	}
}

void insertAtBeginning(Node *newNode)
{
	if(checkInvalidityOfNode(head) && checkInvalidityOfNode(tail))
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		newNode[0].next = head;
		head[0].previous = newNode;
		head = newNode;
	}
}

void insertInMiddle(Node *previous, Node *newNode)
{
	newNode[0].previous = previous;
	newNode[0].next = previous[0].next;
	previous[0].next[0].previous = newNode;
	previous[0].next = newNode;
}

void insertBeforeItem(int existingItem, int newItem)
{
	Node *currentItem = SearchItem(existingItem);
	
	if(checkInvalidityOfNode(currentItem))
	{
		cout << "Maalta Nai, Insert hoibo na" << endl;
		return;
	}
	else
	{
		Node *newNode = createNode(newItem);
		
		if(currentItem == head)
		{
			insertAtBeginning(newNode);
		}
		else
		{
			insertInMiddle(currentItem[0].previous, newNode);
		}
	}
}

void insertAfterItem(int existingItem, int newItem)
{
	Node *currentItem = SearchItem(existingItem);
	
	if(checkInvalidityOfNode(currentItem))
	{
		cout << "Maalta Nai, Insert hoibo na" << endl;
		return;
	}
	else
	{
		Node *newNode = createNode(newItem);
		
		if(currentItem == tail)
		{
			insertAtEnd(newNode);
		}
		else
		{
			insertInMiddle(currentItem, newNode);
		}
	}
}

void insertIntoSorted(int newItem)
{
	Node *newNode = createNode(newItem);
	
	if(checkInvalidityOfNode(head) && checkInvalidityOfNode(tail))
	{
		head = newNode;
		tail = newNode;
		return;
	}
	
	Node *previous = SearchForGreaterGetPrevious(newItem);
	
	if (previous == tail) /*if we cannot find the item, we return tail as a token*/
	{
		insertAtEnd(newNode);
	}
	else if (checkInvalidityOfNode(previous))
	{
		insertAtBeginning(newNode);
	}
	else
	{
		insertInMiddle(previous, newNode);
	}
}

//==

void deleteFirst(void)
{
	if(checkInvalidityOfNode(head)) return;
	
	Node *moraMama = head;
	head = head[0].next;
	if (!checkInvalidityOfNode(head)) head[0].previous = NULL;
	else tail = NULL;
	deleteNode(moraMama);
}

void deleteLast(void)
{
	if(checkInvalidityOfNode(tail)) return;
	
	Node *moraMama = tail;
	tail = tail[0].previous;
	if(!checkInvalidityOfNode(tail)) tail[0].next = NULL;
	else head = NULL;
	deleteNode(moraMama);
}

void deleteInMiddle(Node *current)
{
	current[0].previous[0].next = current[0].next;
	current[0].next[0].previous = current[0].previous;
	deleteNode(current);
}

void actualNodeDeletion(Node *currentItem)
{
	if(checkInvalidityOfNode(currentItem))
	{
		cout << "Item ta nai list e  (actual)" << endl;
		return;
	}
	else if (currentItem == head)
	{
		deleteFirst();
	}
	else if (currentItem == tail)
	{
		deleteLast();
	}
	else
	{
		deleteInMiddle(currentItem);
	}
}

void deleteItem(int item)
{
	Node * currentItem = SearchItem(item);
	actualNodeDeletion(currentItem);
}

void deletePreviousItem(int item)
{
	Node * currentItem = SearchItem(item);
	if(checkInvalidityOfNode(currentItem))
	{
		cout << "Item ta nai list e" << endl;
		return;
	}
	actualNodeDeletion(currentItem[0].previous);
}

void deleteNextItem(int item)
{
	Node * currentItem = SearchItem(item);
	if(checkInvalidityOfNode(currentItem))
	{
		cout << "Item ta nai list e" << endl;
		return;
	}
	actualNodeDeletion(currentItem[0].next);
}

//==

bool readFromFileAndInitialize(char *fileName)
{
	ifstream iFile;
	iFile.open(fileName);
	if(iFile.is_open())
	{
		int numberOfInputs;
		iFile >> numberOfInputs;
		
		for(int i=0; i<numberOfInputs; i++)
		{
			int input;
			iFile >> input;
			
			Node *newNode = createNode(input);
			insertAtEnd(newNode);
			//insertAtBeginning(newNode);
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







int main (int argc, char *argv[])
{
	createLinkedList();
	if(!readFromFileAndInitialize(argv[1])) 
	{
		cout << "Issue with the file" << endl;	
		return -1;
	}
	
	//insertIntoSorted(10);
	
	//insertBeforeItem(18,100);
	
	//insertAfterItem(7,100);
	
	//deleteFirst();
	//deleteLast();
	//deleteItem(500);
	//deletePreviousItem(9);
	//deleteNextItem(9);
	
	traverseForward();
	traverseBackward();
	
	deleteList();
	
	return 0;
}
