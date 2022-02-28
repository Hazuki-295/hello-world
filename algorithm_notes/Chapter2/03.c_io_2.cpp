#include <iostream>
#include <climits>

int main() {
    /* Examples for the printf() function - Format specifier */
    int num = INT_MAX;
    long long bigNum = LONG_LONG_MAX;
    printf("%d, %lld; ", num, bigNum);  // long long 使用 %lld

    float fl = 3.1415;
    double db = 3.1415926536;
    printf("%f, %f;", fl, db);  // 在 printf 中 double 使用 %f

    char c = ' ';
    char str[15] = "Hello,World!";
    printf("%c, %s.", c, str);

    char space = ' ', new_line = '\n';
    printf("%c%c", space, new_line);

    /***********************************************************************************
     * 注意：
     * 1. %c 将会读入空白符(空格、换行等)，而其他格式描述符(如 %d)的输入则是以空白符为结束判断标志的。
     *      因此，除非使用 %c 把空格按字符读入，其他情况都会自动跳过空格。
     * 2. 输入示例："2147483647, 9223372036854775807; 3.1415, 3.1415926536; , Hello,World!. "
     *      最后读入的两个字符，并没有在输入时阻塞，而是直接读取了缓冲区中已存在的字符。
     ***********************************************************************************/

    return 0;
}