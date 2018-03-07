#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    int n;
    string astring;
    stack <char> mystack1;
    stack <char> mystack2;

    cin >> n;
    getline(cin, astring);

    while(n--)
    {
        getline(cin, astring);
		cout << "here" << endl;

        for(int i=0; i<astring.length(); i++)
        {
           cout << "stack " << i << endl;
                if((mystack1.top() != astring[0]))
                {
                    cout << "here 2 hello" << endl;
                    mystack1.pop();
                }
            if((astring[i] == '(') || (astring[i] == ')'))
            {

                    mystack1.push(astring[i]);
            }

            /*if(true)
            {
                if((mystack2.top() == astring[i]))
                    mystack2.pop();
                else
                    mystack2.push(astring[i]);
            }*/
                cout << "here 2" << endl;
        }

        if((mystack1.empty())&&(mystack2.empty()))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}
