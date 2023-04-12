#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const double eps = 1e-8;       // 极小数ε - Epsilon
const double pi = acos(-1.0);  // 圆周率

#define Equ(a, b) ((fabs((a) - (b))) < (eps))  // ==
#define More(a, b) (((a) - (b)) > (eps))       // >
#define MoreEqu(a, b) (((a) - (b)) > (-eps))   // >=
#define Less(a, b) (((a) - (b)) < (-eps))      // <
#define LessEqu(a, b) (((a) - (b)) < (eps))    // <=

int main() {
    char str[100] = {};
    cin.getline(str, 100);  // 从标准输入，读入一整行: Hello world!
    cout << setiosflags(ios::fixed) << setprecision(2) << 123.4567 << endl;  // cout 输出精度控制

    double db1 = 4 * asin(sqrt(2.0) / 2);  // 4 * pi/4 = pi
    double db2 = 3 * asin(sqrt(3.0) / 2);  // 3 * pi/3 = pi

    cout << ((db1 == db2) ? "true" : "false") << '\n'
         << (Equ(db1, db2) ? "true" : "false") << endl;

    return 0;
}