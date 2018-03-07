#include <iostream>

using namespace std;

int *inputArray;
int *countingArray;
int *sortedArray;

void createDynamicArrays()
{
	inputArray = new int[1000000];
	countingArray = new int[1000000];
	sortedArray = new int [1000000];
}

int numberOfElements;

void getInputArray()
{

	int j = 0;
	int i = 0;
	
	while(cin >> i)
	{
		inputArray[j] = i;
		i = 0;
		j++;
	}
	
	numberOfElements = j;
}

void initializeArrays()
{
	inputArray[1000000] = {0};
	countingArray[1000000] = {0};
	sortedArray[1000000] = {0};
}

void insertIntoSortedArray()
{
	for(int i=0; i<numberOfElements; i++)
	{
		countingArray[inputArray[i]]--;
		sortedArray[countingArray[inputArray[i]]] = inputArray[i];
	}
}

void countingSort()
{
	int maximum = 0;
	
	for(int i=0; i<numberOfElements; i++)
	{
		if(inputArray[i] > maximum)
		{
			maximum = inputArray[i];
		}
		countingArray[inputArray[i]]++;
	}
	
	int sum = 0;
	
	for(int i=0; i<=maximum; i++)
	{
		sum += countingArray[i];
		countingArray[i] = sum;
	}
	
	insertIntoSortedArray();
}

void printSortedArray()
{
	for(int i=0; i<numberOfElements; i++)
	{
		cout << sortedArray[i] << " ";
	}
	cout << endl;
}

void destroyArrays()
{
	delete [] countingArray;
	delete [] inputArray;
	delete [] sortedArray;
}

int main()
{

	createDynamicArrays();
	initializeArrays();
	getInputArray();
	countingSort();
	printSortedArray();
	destroyArrays();

	return 0;
}
