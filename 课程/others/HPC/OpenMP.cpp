#include <omp.h>
#include <time.h>
#include <iostream>
using namespace std;

static long num_steps = 100000; // �ֿ���
double step; // ����
#define NUM_THREADS 2 // �߳���

int main()
{
	int i; double x, pi, sum = 0.0; // ��������
	step = 1.0 / (double)num_steps; // ����
	clock_t start, finish;

	omp_set_num_threads(NUM_THREADS); // �����߳���
	start = clock();

	#pragma omp parallel for reduction(+:sum) private(x) // �����죬��Լ�ͣ�ÿ���߳�˽�е��ۼ�ֵ
	for (i = 1; i <= num_steps; i++)
	{
		x = (i - 0.5) * step;
		sum = sum + 4.0 / (1.0 + x * x); // ������pi
	}
	pi = step * sum; // ��Լ��Ľ���ٳ��Բ���
	finish = clock();

	double time = (double)(finish - start) / CLOCKS_PER_SEC;

	const double pi2 = 3.141592653589793;
	printf("  real pi = %.15f\n", pi2);
	printf("  test pi = %.15f\n", pi);
	cout << "time:" << time * 1000 << "ms\n";
	return 0;
}