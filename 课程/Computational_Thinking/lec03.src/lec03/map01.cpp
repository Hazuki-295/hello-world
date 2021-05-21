#include <bits/stdc++.h>
using namespace std;

int main()
{
    map<string, int> month_name;

    month_name["January"] = 1;
    month_name["February"] = 2;
    month_name["July"] = 7;

    map<string, int>::iterator it;
    for (it = month_name.begin(); it != month_name.end(); it++)
    {
        cout << it->first << "    " << it->second << endl;
    }
    return 0;
}