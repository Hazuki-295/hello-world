#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
int main()
{
    int sum = 0;
    if (!cin.good())
    {
        cout <<"Standard input is in a bad state !"<< endl;
        exit(1);
    }
    int number;
    while (true)
    {
        cin >> number;
        if (cin.good())
            sum += number;
        else if (cin.eof())
            break;
        else
        {
            cin.clear();
            string badToken;
            cin >> badToken;
            cerr <<"WARNING : Bad input encounter :"<< badToken << endl;
        }
    }
    cout <<"The sum is :"<< sum << endl;
    return 0;
}