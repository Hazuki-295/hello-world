#include <iostream>
using namespace std;

int main()
{
	long long temp, sum; char c;

	while ((c = getchar()) != '0') // ÿ�˴���һ��
	{
		ungetc(c, stdin);

		sum = 0;
		while (scanf("%lld", &temp) == 1)
		{
			sum += temp;

			if ((c = getchar()) == '\n') // getchar�Ѿ����ڴ���룬��ʱ�ж��Ƿ�Ϊ���У�����ǣ����˳�
			{
				break;
			}
			ungetc(c, stdin);            // ��������ڰ�getchar��������ȡ�����ַ��Ż�������
		}
		cout << sum << endl;
	}

	return 0;
}