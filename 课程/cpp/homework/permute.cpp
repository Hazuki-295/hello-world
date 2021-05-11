#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    vector<int> student; // 空vector对象
    for (int i = 1; i <= 40; i++)
    {
        student.push_back(i);
    }

    /* 随机置乱，使各元素等概率出现于各位置 */
    srand((unsigned)time(0));
    for (int i = student.size(); i > 0; i--) // 自后向前
    {
        swap(student[i - 1], student[rand() % i]); // v[i - 1]与v[0,i)中某一随机元素交换
    }

    cout << setiosflags(ios::left);
    for (int i = 1; i <= 40; i++)
    {
        cout << setw(4) << student[i - 1];
        if (i % 10 == 0)
        {
            cout << endl;
        }
    }

    for (auto temp : student)
    {
        cout << setw(4) << temp;
    }
    cout << endl;

    for (auto beg = student.begin(), end = student.end(); beg != end; beg++)
    {
        cout << setw(4) << *beg;
    }
    cout << endl;

    return 0;
}

void song()
{
    int num[41] = { 0 }, n, g;

    vector<vector<int>> group(4);

    srand((unsigned)time(NULL));

    for (int i = 0; i < 40; i++)
    {
        do
        {
            n = rand() % 40 + 1;
        } while (num[n] == 1);

        num[n] = 1;
        do
        {
            g = rand() % 4;
        } while (group[g].size() == 10);

        group[g].push_back(n);
    }
    cout << setiosflags(ios::left); ;

    for (auto v : group) {
        for (auto x : v)
            cout << setw(2) << x << " ";
        cout << endl;
    }
}
