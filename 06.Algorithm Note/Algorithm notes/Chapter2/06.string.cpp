#include <iostream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;
using LL = long long;

int main() {
    int myArray[5] = {};

    /* memset() - fill memory with a constant byte (interpreted as an unsigned char) */
    for (auto byte : vector<int>({0, -1, 1, 255})) {
        memset(myArray, byte, sizeof(myArray));

        printf("memset(byte: %3d) = ", byte);  // 0的补码为“全0”，-1的补码为“全1”，
        for (auto x : myArray) {               // 因此 memset 可用来将 int 数组的所有元素赋值为0或-1
            printf("%10d ", x);
        }
        printf("\n");
    }

    cout << string(100, '-') << endl;  // 分割线

    int num; LL bigNum; float fl; double db;
    char c, str[15], space, new_line;

    const char input[100] = "2147483647, 9223372036854775807; 3.1415, 3.1415926536; , Hello,World! \n";
    char output[100] = {};

    /* sscanf() - read input from a character string */
    sscanf(input, "%d,%lld;%f,%lf;%c,%s%c%c", &num, &bigNum, &fl, &db, &c, str, &space, &new_line);

    /* sprintf() - write output to a character string */
    sprintf(output, "%d, %lld; %.4f, %.10lf;%c, %s%c%c", num, bigNum, fl, db, c, str, space, new_line);

    printf("%s", output);
    bool equal = (strcmp(input, output) == 0);

    return 0;
}