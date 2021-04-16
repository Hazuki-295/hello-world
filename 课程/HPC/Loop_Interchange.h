#include <stdio.h>
#include <time.h>
float array[5000][5000];

/* Loop_Interchange 循环交换 */
int Loop_Interchange()
{
    int i, j;
    clock_t start1, finish1, start2, finish2;
    double duretime;

    printf("traverse in row\n");//以行遍历
    start1 = clock();
    for (i = 0; i < 5000; i++)
        for (j = 0; j < 5000; j++)
            array[i][j] = (i + j) * 2;
    finish1 = clock();
    duretime = (double)(finish1 - start1) / CLK_TCK;
    printf("time:%f\n", duretime);

    printf("traverse in collumn\n");//以列遍历
    start2 = clock();
    for (j = 0; j < 5000; j++)
        for (i = 0; i < 5000; i++)
            array[i][j] = (i + j) * 2;
    finish2 = clock();
    duretime = (double)(finish2 - start2) / CLK_TCK;
    printf("time: %f\n", duretime);
    return 0;
}
