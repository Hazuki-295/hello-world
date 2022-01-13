#include <iostream>

int main() {
    /* scanf() function, conversion specifications */
    int num;
    long long bigNum;
    scanf("%d, %lld;", &num, &bigNum);  // long long 使用 %lld

    float f;
    double d;
    scanf("%f, %lf;", &f, &d);  // 在 scanf 中 double 使用 %lf

    char c;
    char str[15];
    scanf("%c, %s.", &c, str);  // 注意：%c 将会读入空白符。另外，str 为数组名，本身就是地址。

    /* "2147483647, 9223372036854775807; 3.1415, 3.1415926536; , Hello,World! ." */

    return 0;
}