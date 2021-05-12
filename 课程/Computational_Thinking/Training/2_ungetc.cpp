#include <iostream>
using namespace std;

int main()
{
	long long temp, sum; char c;

	while ((c = getchar()) != '0') // 每趟处理一行
	{
		ungetc(c, stdin);

		sum = 0;
		while (scanf("%lld", &temp) == 1)
		{
			sum += temp;

			if ((c = getchar()) == '\n') // getchar已经把内存读入，此时判断是否为换行，如果是，则退出
			{
				break;
			}
			ungetc(c, stdin);            // 此语句用于把getchar从输入流取出的字符放回输入流
		}
		cout << sum << endl;
	}

	return 0;
}