#include <iostream>
#include <cmath>

const double pi = acos(-1.0);  // 此处把 pi 定义为精确值 acos(-1.0)，因为 cos(pi) = -1

int main() {
    double num1 = -12.56;
    printf("1. fabs(-12.56) = %.2f\n\n", fabs(num1));
    // double 类型的绝对值函数，返回类型也是 double

    double num2 = -5.2;
    printf("2. floor(-5.2) = %.0f, ceil(-5.2) = %.0f\n\n", floor(num2), ceil(num2));
    // double 类型的向下取整(floor)，和向上取整(ceiling)函数，返回类型也是 double

    double num3 = pow(2.0, 3.0);
    printf("3. pow(2.0, 3.0) = %f\n\n", num3);
    // 幂函数，需要的两个参数为 double 类型，返回类型也是 double

    double num4 = sqrt(2.0);
    printf("4. sqrt(2.0) = %f\n\n", num4);
    // 算数平方根

    double num5 = log(1.0), log_2_8 = log(8.0) / log(2.0);
    printf("5. ln(1.0) = %f, log_2_8 = %f\n\n", num5, log_2_8);
    // 对数函数，以自然对数e为底。若要对任意底数求对数，则需要使用“换底公式”

    double sin_ = sin(pi * 45 / 180);
    double cos_ = cos(pi * 45 / 180);
    double tan_ = tan(pi * 45 / 180);
    printf("6. sin(45°) = %f, cos(45°) = %f, tan(45°) = %f\n\n", sin_, cos_, tan_);
    // 三角函数，参数要求是“弧度制”

    double asin_ = asin(1);
    double acos_ = acos(-1.0);
    double atan_ = atan(0);
    printf("7. asin(1) = %f, acos(-1.0) = %f, atan(0) = %f\n\n", asin_, acos_, atan_);
    // 反三角函数

    double num8 = round(3.50);
    printf("8. round(3.5) = %.0f\n\n", num8);
    // 四舍五入，返回类型是 double，需进行取整

    return 0;
}