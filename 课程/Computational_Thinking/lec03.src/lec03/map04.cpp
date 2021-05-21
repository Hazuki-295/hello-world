#include <bits/stdc++.h>
using namespace std;
int main()
{
    map<int, string> mapStudent;
    mapStudent.insert(pair<int, string>(1, "student_one"));
    mapStudent.insert(pair<int, string>(2, "student_two"));
    mapStudent.insert(pair<int, string>(3, "student_three"));

    int c1 = mapStudent.count(5);
    if (c1 == 0)
        cout << "5 not find" << endl;
    else 
        cout << "find 5" << endl;

    map<int, string>::iterator iter;
    iter = mapStudent.find(1);
    if (iter != mapStudent.end())
    {
        cout <<"Find, the value is "<< iter->second << endl;
    }
    else
    {
        cout <<"Do not Find"<< endl;
    }
    return 0;
}