#include <omp.h>
#include <time.h>
#include <math.h>
#include <iostream>
using namespace std;

#define NUM_THREADS 2 // 线程数

int countPrimes(int n) // 埃拉托斯特尼筛法 Sieve of Eratosthenes
{
    bool *isPrime = new bool[n];
    memset(isPrime, true, n * sizeof(bool)); // 将数组都初始化为 true

    double sqrt_n = sqrt(n);
    int finish = (int)sqrt_n;

    clock_t start1, finish1;

    start1 = clock();
    #pragma omp parallel for num_threads(NUM_THREADS)
    for (int i = 2; i < finish; i++) // 素数从 2 开始算
    {
        if (isPrime[i])
        {
            for (int j = i * i; j < n; j += i) // i 的倍数不可能是素数了
            {
                isPrime[j] = false;
            }
        }
    }

    int count = 0;
    #pragma omp parallel for num_threads(NUM_THREADS) reduction(+:count)
    for (int i = 2; i < n; i++)
    {
        if (isPrime[i])
            count++;
    }
    delete[] isPrime;
    finish1 = clock();

    cout << "Num of primes:" << count << '\n';
    double time = (double)(finish1 - start1) / CLOCKS_PER_SEC;
    cout << "time:" << time * 1000 << "ms\n";

    return count;
}

int main(int argc, char *argv[])
{
    int n; cin >> n;
    countPrimes(n);

    return 0;
}