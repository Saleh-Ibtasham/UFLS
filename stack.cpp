#include <iostream>
#include <stack>

using namespace std;

int main (void)
{
	stack <int> mS;
	
	for(int i=1; i<=5; i++)
	{
		mS.push(i*10);
	}
	
	while(!mS.empty())
	{
		cout << mS.top() << endl;
		mS.pop();
	}
	
	return 0;
}
