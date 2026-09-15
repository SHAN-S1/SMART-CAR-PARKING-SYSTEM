#include<iostream>
using namespace std;
void max(int a, int b)
{
    if(a>b)
    {
        cout << "a is bigger" << endl;
    }
    else{
        cout<< "b is bigger" << endl;
    }
}
int main()
{
    int a,b;
    cout << "enter a:";
    cin >> a;
    cout << "enter b:";
    cin >> b;
    max(a, b);
    return 0;
    
}