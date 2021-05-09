#include <time.h>
#include <iostream>
using namespace std;

int countPrimes(int n) // ������˹����ɸ�� Sieve of Eratosthenes
{
    bool *isPrime = new bool[n];
    memset(isPrime, true, n * sizeof(bool)); // �����鶼��ʼ��Ϊ true

    clock_t start1, finish1;

    start1 = clock();
    for (int i = 2; i * i < n; i++) // ������ 2 ��ʼ��
    {
        if (isPrime[i])
        {
            for (int j = i * i; j < n; j += i) // i �ı�����������������
            {
                isPrime[j] = false;
            }
        }
    }

    int count = 0;
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