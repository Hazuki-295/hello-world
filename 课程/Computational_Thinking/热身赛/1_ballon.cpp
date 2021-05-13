#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/* Problem B. ���� */
void process(int heap) // heap������
{
	int temp; char c;
	vector<vector<int>> ball(heap); // ÿ������Ϊһ�����򣬼������е�һ��
	for (int i = 0; i < heap; i++)  // ����heap������
	{
		while ((c = getchar()) != '\n') // ����ʹ�� getline() �������Ǵ˴���ÿ���ո������Ǵ���1λ������
		{
			ungetc(c, stdin);

			cin >> temp;
			ball[i].push_back(temp); // ��i��
		}
	}

	struct Ball { int color; int num; };

	// Ball ballon[heap][101]; // heap���������ɫ��������Ϣ

	using Ballon = Ball[101]; // ÿ���������ɫ��������Ϣ��1��100��0��δ��

	Ballon *eachline = new Ballon[heap + 1]; // heap������0��δ��

	/* ÿ�е�����Ϊ��һ�������У�ÿ���������ɫ */
	for (int line = 1; line <= heap; line++)
	{
		for (int i = 0; i < 101; i++) // ÿһ�ж��� Ball[101]
		{
			eachline[line][i].color = i; // ��ʼ����ɫΪ1,2,3,...
			eachline[line][i].num = 0;   // ��ʼ������Ϊ0
		}

		for (auto color : ball[line - 1]) // ÿ���������ݼ���
		{
			eachline[line][color].num++;  // ��color��ɫ������+1
		}
	}

	/* ɨ��һ��������ɫ */
	bool right = true; // �Ƿ���Ϲ���
	for (int colornum = 1; colornum <= 100; colornum++) // ������ɫ
	{
		int *colors = new int[heap]; // ��������
		for (int i = 0; i < heap; i++) // heap���У�ÿ�Ѹ���ɫ�����Ϣ
		{
			colors[i] = eachline[i + 1][colornum].num;
		}
		sort(colors, colors + heap); // �������������и���ɫ����������������һ��
		int	div = colors[heap - 1] - colors[0]; // ��ʵ��������������ֵ����Сֵ�ܹ���>1���Ϳ��Ա�֤���岻>1
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
	int heap; char c; // heapΪ��Ķ���

	while (cin >> heap)
	{
		c = getchar(); // ���������Ļ���
		process(heap);
	}

	return 0;
}