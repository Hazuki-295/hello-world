#include <iostream>
using namespace std;
int main()
{
    char a;
    char array[20] = {NULL};
    cin.get(array, 20);
    cin.get(a);
    cout << array << " " << (int)a << endl;
    return 0;
}
