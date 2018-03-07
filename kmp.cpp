#include <iostream>
#include <string>
//#include <bits/stdc++.h>

using namespace std;

int *failArr;

void failFunc(string &pattern);
void createFailArray(int l);
void printFailArr(string &pattern);
void kmpMatch(string &text, string &pattern);

int main()
{
	
	string pattern, text;
	
	getline(cin, pattern);
	
	failFunc(pattern);
	
	printFailArr(pattern);
	
	getline(cin, text);
	
//	cout << failArr[6] << " " << failArr[4]<< endl;
	
	kmpMatch(text, pattern);
	
	delete [] failArr;
	
	return 0;
}

void failFunc(string &pattern)
{
	createFailArray(pattern.length());
	
	failArr[0] = 0;
	int k = 0;
	
	//cout << endl;
	for(int q = 1; q<pattern.length(); q++)
	{
		while((k>0)&&(pattern[k]!=pattern[q]))
		{
			k = failArr[k-1];
		}
		if(pattern[k]==pattern[q])
		{
			k = k+1;
		}
		failArr[q]=k;
		//cout << q << " " << failArr[q] << endl;
	}
}

void createFailArray(int l)
{
	failArr = new int[l];
}

void printFailArr(string &pattern)
{
	cout << endl;
	for(int i=0; i<pattern.length(); i++)
	{
		cout << failArr[i] << endl;
	}
	cout << endl;
}

void kmpMatch(string &text, string &pattern)
{
	int count=0;
	int q=0;
	
	int j=0;
	
	for(int i=0; i<text.length(); i++)
	{
		while((q>0)&&(pattern[q]!=text[j]))
		{
			q=failArr[q-1];
		}
		if(text[j]==pattern[q])
		{
			q=q+1;
			j++;
		}
		if(!q)
			j++;
//		cout << text[j-1] << " " << q << endl;
		if(q == (pattern.length()))
		{
			cout << "Match found at index " << j-pattern.length() << endl;
			q=failArr[q-1];
			count++;
		}
	}
	
	cout << "Match found " << count << " times" << endl;
}
