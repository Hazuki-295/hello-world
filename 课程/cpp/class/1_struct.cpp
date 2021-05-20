#include <iostream>
using namespace std;

template <typename T> struct Point
{
	T x, y;
	PointV2(T x = 0, T y = 0) : x(x), y(y) {}
};

template <typename T> PointV2<T> operator+(const PointV2<T> &A, const PointV2<T> &B)
{
	return PointV2<T>(A.x + B.x, A.y + B.y);
}

template <typename T> ostream &operator<<(ostream &out, const PointV2<T> &p)
{
	out << "(" << p.x << "," << p.y << ")";
	return out;
}

int main() {
	Point a, b(1, 2);
	a.x = 3;
	cout << a + b << "\n";
	return 0;
}

