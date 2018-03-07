#include <iostream>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

struct content
{
	float number;
	char symbol;
	bool flag; // true if number
};

char operators[6] = {'+', '-', '*', '/', '(', ')'};

void replaceSymbols(string &numbers)
{
	for(int i=0;i< 6;i++)
	{
		for(int j=0; j<numbers.length(); j++)
		{
			if(numbers[j]==operators[i]) numbers[j]= ' ';
		}
	}
}

void makeContentWithSymbol(content &node, char symbol)
{
	node.symbol = symbol;
	node.flag = false;
}

void makeContentWithNumber(content &node, float number)
{
	node.number = number;
	node.flag = true;
}

void parsingInput(string inputString, vector <content> &infix)
{
	string numbers = inputString;
	replaceSymbols(numbers);
	
	istringstream iss(numbers);
	
	vector <float> numbersObtained;
	float temp;
	while(iss>>temp)
	{
		numbersObtained.push_back(temp);
	}
	
	for(int i=0; i<numbers.length(); i++)
	{
		if(numbers[i] == ' ')
		{
			if(i!=0)
			{
				if(numbers[i-1] != ' ')
				{
					content node;
					
					makeContentWithNumber(node, numbersObtained[0]);
					infix.push_back(node);
					numbersObtained.erase(numbersObtained.begin());
					
					makeContentWithSymbol(node, inputString[i]);
					infix.push_back(node);
				}
				else
				{
					content node;
					makeContentWithSymbol(node, inputString[i]);
					infix.push_back(node);
				}
			}
			else
			{
				content node;
				makeContentWithSymbol(node, inputString[i]);
				infix.push_back(node);
			}
		}
	}
	
	if(!numbersObtained.empty())
	{
		content node;
		makeContentWithNumber(node, numbersObtained[0]);
		infix.push_back(node);
		numbersObtained.erase(numbersObtained.begin());
	}
}

bool lowerPrecedence(char infixSymbol, char stackSymbol)
{
	if((infixSymbol=='/'|| infixSymbol=='*')&&(stackSymbol=='+'||stackSymbol=='-')) return true;
	else return false;
}

void infixToPostfix(vector <content> infix, vector <content> &postfix)
{
	stack <content> myStack;
	
	content node;
	makeContentWithSymbol(node, '(');
	myStack.push(node);
	
	makeContentWithSymbol(node, ')');
	infix.push_back(node);
	
	for(int i=0; i<infix.size(); i++)
	{
		if(infix[i].flag)
		{
			postfix.push_back(infix[i]);
		}
		else
		{
			if(infix[i].symbol == '(')
			{
				myStack.push(infix[i]);
			}
			else if(infix[i].symbol == ')')
			{
				while(1)
				{
					content tempNode = myStack.top();
					
					if(tempNode.symbol=='(')
					{
						myStack.pop();
						break;
					}
					else
					{
						postfix.push_back(tempNode);
						myStack.pop();
					}
				}
			}
			else
			{
				while(1)
				{
					content tempNode = myStack.top();
					if((lowerPrecedence(infix[i].symbol, tempNode.symbol))||(tempNode.symbol == '(')) break;
					postfix.push_back(tempNode);
					myStack.pop();
				}
				myStack.push(infix[i]);
			}
		}
	}
}

void printExpression(vector <content> expression)
{
	for(int i=0; i<expression.size(); i++)
	{
		if(expression[i].flag) cout << expression[i].number << " ";
		else cout << expression[i].symbol << " ";
	}
	cout << endl;
}

float evaluateBasicArithmetic(float a, float b, char symbol)
{
	switch(symbol)
	{
		case '+': return b+a;
		case '-': return b-a;
		case '*': return b*a;
		default: return b/a;
	}
}

float evaluatePostfix(vector <content> postfix)
{
	stack <content> myStack;
	
	for (int i=0; i<postfix.size(); i++)
	{
		if(postfix[i].flag)
		{
			myStack.push(postfix[i]);
		}
		else
		{
			content stackTop0, stackTop1; 
			float result;
			stackTop0 = myStack.top();
			myStack.pop();
			stackTop1 = myStack.top();
			myStack.pop();
			
			result = evaluateBasicArithmetic(stackTop0.number, stackTop1.number, postfix[i].symbol);
			content tempNode;
			makeContentWithNumber(tempNode, result);
			myStack.push(tempNode);
		}
	}
	return (myStack.top()).number;
}


int main (void)
{
	string inputString;
	getline(cin,inputString);
	
	vector <content> infix;
	parsingInput(inputString, infix);
	
	cout << "Infix is: " << endl;
	printExpression(infix);
	
	vector <content> postfix;
	infixToPostfix(infix, postfix);
	
	cout << "Postfix is: " << endl;
	printExpression(postfix);
	
	cout << "Result is: " << evaluatePostfix(postfix) << endl;
	
	return 0;
}
