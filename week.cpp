#include <iostream>
#include <cstdio>
#include <sstream>

using namespace std;

struct Student{
	
	int x;
	Student *pre;
	Student *nxt;
};

Student *head; 
Student *tail;

void insert(int p){
	Student *current;
	current = new Student[1];
	if(head == NULL)
	{
		current[0].x=p;
		current[0].pre=NULL;
		current[0].nxt=NULL;
		head = current;
		tail = current;
	}
	else
	{
		current[0].x=p;
		current[0].pre=tail;
		tail[0].nxt = current;
		current[0].nxt=NULL;
		tail = current;
	}
}

void swap(int p, int q){

	Student *st1,*st2,*temp;
	
	for(Student *it=head; it != NULL; it = it[0].nxt)
	{
		if(it[0].x == p)
		{
			it[0].x = q;
		}
		else if(it[0].x == q)
		{
			it[0].x = p;
		}
	}
	
	/*st1 = temp;
	temp[0].pre = st2[0].pre;
	temp[0].nxt = st2[0].nxt;
	temp[0].id = st2[0].id;
	temp = st2;
	st2 = st1;*/
	
}

void print(Student *current){
	
	
	//cout << "he" << endl;
	if (head == NULL)
		return;
	cout << "here is " << current[0].x << endl;
	if(tail == current)
		return;
	
	print(current[0].nxt);
}

void createLinkList(){
	
	head = NULL;
	tail = NULL;
}

void deleteEntry(int p)
{
	for(Student *it=head; it != NULL; it = it[0].nxt)
	{
		if(it[0].x == p)
		{
			if((it != head) && (it != tail))
			{
				it[0].pre[0].nxt = it[0].nxt;
				it[0].nxt[0].pre = it[0].pre;
			}
			else if (it == head)
			{
				it[0].nxt[0].pre = NULL;
				head = it[0].nxt;
			}
			else if (it == tail)
			{
				it[0].pre[0].nxt = NULL;
				tail = it[0].pre;
			}
		}
	}
}

int main()
{
	createLinkList();
	
	while(1){
		
		string s;
		getline(cin,s);
		
		istringstream iss(s);
		string str;
		iss >> str;
		if(str == "insert")
		{
			int p;
			iss >> p;
			//cout << "here is " << p << endl;
			insert(p);
		}
		else if(str == "print")
		{
			print(head);
		}
		else if(str == "delete")
		{
			int p;
			iss >> p;
			deleteEntry(p);
		}
		else
		{
			int p,q;
			
			iss >> p;
			iss >> q;
			
			swap(p,q);
		}	
	}
	
	return 0;
}
