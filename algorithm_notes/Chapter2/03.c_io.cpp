#include <iostream>

int main() {
    /* scanf() function, conversion specifications */
    int num;
    long long bigNum;
    scanf("%d, %lld;", &num, &bigNum);  // long long 使用 %lld

    float f;
    double d;
    scanf("%f, %lf;", &f, &d);  // 在 scanf 中 double 使用 %lf

    char c;                     // 注意：%c 将会读入空白符(空格、换行等)，而其他格式描述符(如 %d)的输入则是以空白符为结束判断标志的。
    char str[15];               // 因此，除非使用 %c 把空格按字符读入，其他情况都会自动跳过空格。
    scanf("%c, %s.", &c, str);  // 另外，str 为数组名，本身就是地址。

    /* "2147483647, 9223372036854775807; 3.1415, 3.1415926536; , Hello,World! ." */

    return 0;
}