#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/* Problem B. 气球 */
void process(int heap) // heap堆气球
{
	int temp; char c;
	vector<vector<int>> ball(heap); // 每个向量为一堆气球，即数据中的一行
	for (int i = 0; i < heap; i++)  // 存入heap堆气球
	{
		while ((c = getchar()) != '\n') // 或者使用 getline() 处理，但是此处，每个空格间可能是大于1位的整数
		{
			ungetc(c, stdin);

			cin >> temp;
			ball[i].push_back(temp); // 第i堆
		}
	}

	struct Ball { int color; int num; };

	// Ball ballon[heap][101]; // heap堆气球的颜色及数量信息

	using Ballon = Ball[101]; // 每堆气球的颜色及数量信息，1到100，0号未用

	Ballon *eachline = new Ballon[heap + 1]; // heap堆气球，0号未用

	/* 每行的数据为：一堆气球中，每个气球的颜色 */
	for (int line = 1; line <= heap; line++)
	{
		for (int i = 0; i < 101; i++) // 每一行都是 Ball[101]
		{
			eachline[line][i].color = i; // 初始化颜色为1,2,3,...
			eachline[line][i].num = 0;   // 初始化数量为0
		}

		for (auto color : ball[line - 1]) // 每堆气球数据记入
		{
			eachline[line][color].num++;  // 该color颜色的球数+1
		}
	}

	/* 扫描一遍所有颜色 */
	bool right = true; // 是否符合规则
	for (int colornum = 1; colornum <= 100; colornum++) // 所有颜色
	{
		int *colors = new int[heap]; // 辅助数组
		for (int i = 0; i < heap; i++) // heap堆中，每堆该颜色球的信息
		{
			colors[i] = eachline[i + 1][colornum].num;
		}
		sort(colors, colors + heap); // 任意两堆气球中该颜色的气球数量相差不超过一个
		int div = colors[heap - 1] - colors[0]; // 其实，排完序后，若最大值和最小值能够不>1，就可以保证整体不>1
		if (div > 1) { right = false; break; }
	}

	if (right)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	delete[] eachline;
}


int main()
{
	int heap; char c; // heap为球的堆数

	while (cin >> heap)
	{
		c = getchar(); // 处理缓冲区的换行
		process(heap);
	}

	return 0;
}