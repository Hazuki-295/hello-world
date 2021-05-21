#include <map>
#include <string>
#include <iostream>
using namespace std;
int main()
{
    map<int, string> mapStudent;
    mapStudent.insert(pair<int, string>(1, "student_one"));
    mapStudent.insert(pair<int, string>(2, "student_two"));
    mapStudent.insert(pair<int, string>(3, "student_three"));

    //用迭代器删除1
    map<int, string>::iterator iter;
    iter = mapStudent.find(1);
    mapStudent.erase(iter);
    cout <<"After 1st erase, map size: " << mapStudent.size() << endl;
    //用关键字删除2
    int n = mapStudent.erase(2); //如果删除了会返回1，否则返回0
    cout <<"After 2nd erase, map size: " << mapStudent.size() << endl;

    map<int, string>::iterator it = mapStudent.begin();
    while(it != mapStudent.end()){
        cout << it->first << "--->" << it->second << endl;
        it++;
    }    
    //用迭代器，成片的删除。成片删除要注意的是，删除区间是一个前闭后开的集合（也是STL的特性）
    mapStudent.erase(mapStudent.begin(), mapStudent.end());
    cout <<"At last, map size: " << mapStudent.size() << endl;
    
    return 0;
}