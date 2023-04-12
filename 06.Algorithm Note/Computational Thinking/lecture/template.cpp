#include <iostream>
#include <iomanip>
using namespace std;

// int sum(int *begin, int *end)
// {
//     int *p = begin;
//     int ans = 0;
//     for (int *p = begin; p != end; p++)
//         ans += *p;
//     return ans;
// }

template <typename T>
T sum(T *begin, T *end)
{
    T *p = begin;
    T ans = 0;
    for (T *p = begin; p != end; p++)
        ans += *p;
    return ans;
}

struct Point
{
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    Point operator+=(const Point& A){
        return Point(this->x+A.x, this->y+A.y);
    }
};
Point operator+(const Point &A, const Point &B)
{
    return Point(A.x + B.x, A.y + B.y);
}
ostream &operator<<(ostream &out, const Point &p)
{
    out << "(" << p.x << "," << p.y << ")";
    return out;
}

template <typename T>
struct PointV2
{
    T x, y;
    PointV2(T x = 0, T y = 0) : x(x), y(y) {}
};
template <typename T>
PointV2<T> operator+(const PointV2<T> &A, const PointV2<T> &B)
{
    return PointV2<T>(A.x + B.x, A.y + B.y);
}
template <typename T>
ostream &operator<<(ostream &out, const PointV2<T> &p)
{
    out << "(" << p.x << "," << p.y << ")";
    return out;
}

int main()
{
    double a[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    cout << sum(a, a + 5) << "\n";
    Point b[] = {Point(1, 2), Point(3, 4), Point(5, 6), Point(7, 8)};
    PointV2<int> c[] = {PointV2<int>(1, 2), PointV2<int>(3, 4), PointV2<int>(5, 6), PointV2<int>(7, 8)};
    PointV2<double> d[] = {PointV2<double>(1.1, 2.2), PointV2<double>(3., 4.), PointV2<double>(5, 6), PointV2<double>(7, 8)};
    // cout.width(6);
    cout << sum(b, b + 4) << "\n";
    cout << sum(c, c + 4) << "\n";
    cout << setprecision(6) << sum(d, d + 4) << "\n";
    cout<<setprecision(3)<<setiosflags(ios::fixed)<<3.1415926<<endl;

    // int temp1 = 65, temp2 = 66;
	// cout << (char)temp1 << " " << (char)temp2 << endl; //A B
	// cout << temp1 << " " <<  temp2 << endl;  //
	// cout << "hex:" <<ios_base::hex << temp1 << endl;
	// cout << "oct:" << oct << temp2 << endl;


    return 0;
}