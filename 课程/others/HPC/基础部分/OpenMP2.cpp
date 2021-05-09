#include <omp.h>
#include <time.h>
#include <iostream>
using namespace std;

static long num_steps = 100000; // 分块数
double step; // 步长
#define NUM_THREADS 8 // 线程数

int main()
{
	int i, id;
	double x, pi, sum = 0.0; // 公共变量
	step = 1.0 / (double)num_steps; // 步长
	clock_t start, finish;

	omp_set_num_threads(NUM_THREADS); // 设置线程数
	start = clock();

	#pragma omp parallel reduction(+:sum) private(x, i, id) // 分块构造，归约和，每个线程私有的累加值
	{
		id = omp_get_thread_num();
		for (i = id; i < num_steps; i = i + NUM_THREADS)
		{
			x = (i + 0.5) * step;
			sum = sum + 4.0 / (1.0 + x * x); // 积分求pi
		}
	}
	pi = step * sum; // 归约后的结果再乘以步长
	finish = clock();

	double time = (double)(finish - start) / CLOCKS_PER_SEC;

	const double pi2 = 3.141592653589793;
	printf("  real pi = %.15f\n", pi2);
	printf("  test pi = %.15f\n", pi);
	cout << "time:" << time * 1000 << "ms\n";
	return 0;
}