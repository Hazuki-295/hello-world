#include <iostream>
using namespace std;

typedef struct node {
	long long value;
	int pos;
} Data;

int cmp(const void *a, const void *b)
{
	if (((Data *)a)->value < ((Data *)b)->value)
	{
		return -1;
	}
	else if (((Data *)a)->value == ((Data *)b)->value)
	{
		return 0;
	}
	else
		return 1;
}

int main()
{
	int n;
	cin >> n;
	Data *data = (Data *)malloc(sizeof(Data) * n);
	
	for (int i = 0; i < n; i++)
	{
		cin >> data[i].value;
		data[i].pos = i + 1; // 索引从1开始计数
	}
	qsort(data, n, sizeof(Data), cmp); // 按值快速排序

	long long min = llabs(data[1].value - data[0].value); // 初始化最小差
	int index1 = data[1].pos; // 最小差下标
	int index2 = data[0].pos;

	long long temp; // 暂存计算结果

	for (int i = 1; i < n; i++) // 寻找最小差
	{
		temp = llabs(data[i].value - data[i - 1].value);
		if (temp < min)
		{
			min = temp;
			index1 = data[i].pos;
			index2 = data[i - 1].pos;
		}
	}

	cout << min << ' ' << index2 << ' ' << index1;	

	free(data);

	return 0;
}
