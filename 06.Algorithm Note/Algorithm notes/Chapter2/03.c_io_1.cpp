#include <iostream>
#include <climits>

int main() {
    /* Examples for the scanf() function - Format specifier */
    int num;
    long long bigNum;
    scanf("%d, %lld;", &num, &bigNum);  // long long 使用 %lld

    float fl;
    double db;
    scanf("%f, %lf;", &fl, &db);  // 在 scanf 中 double 使用 %lf

    char c;
    char str[15];
    scanf("%c, %s", &c, str);  // str 为数组名，本身就是地址。

    char space, new_line;
    scanf("%c%c", &space, &new_line);

    /***********************************************************************************
     * 注意：
     * 1. %c 将会读入空白符(空格、换行等)，而其他格式描述符(如 %d)的输入则是以“空白符”为结束判断标志的。
     *       因此，除非使用 %c 把空格按字符读入，“其他情况都会自动跳过空格”。
     *
     * 2. 输入示例："2147483647, 9223372036854775807; 3.1415, 3.1415926536; , Hello,World! "
     *       最后读入的两个字符，并没有在输入时阻塞，而是直接读取了缓冲区中已存在的字符。
     ***********************************************************************************/

    return 0;
}