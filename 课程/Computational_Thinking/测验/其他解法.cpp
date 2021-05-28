#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct product // �˻�
{
	// ��Ա
	long long val; int count; // �˻���������
	// ���캯��
	product(long long _val, int _count) :val(_val), count(_count) {};
};

bool operator<(const product &a, const product &b) // ���ȼ�����
{
	if (abs(a.val) < abs(b.val))
		return true;
	else if (abs(a.val) == abs(b.val))
	{
		if (a.count > b.count)
			return true;
		else if (a.count == b.count) // ������Ϊ׼
			if (a.val < b.val)
				return true;
	}

	return false;
}

bool compare(const int &a, const int &b) // a>b? ����
{
	if (abs(a) > abs(b))
		return true;
	else if (abs(a) == abs(b))
		if (a > b)  // ������Ϊ׼
			return true;

	return false;
} // ����

/* Problem C. ���� */
int main()
{
	// �������ɸ�����S=S1,S2,...,Sn�������������˻��Ƕ��٣�

	// ���˻��������������У��Ӵ�С��
	string line; int cases = 0;

	while (getline(cin, line))
	{
		cout << "Case " << ++cases << ":";
		stringstream buffer(line);

		int temp;
		vector<int> factors; // ����

		while (buffer >> temp)
		{
			if (temp > 0)
				factors.push_back(temp); // ������
			else if (temp < 0)
				factors.push_back(temp); // ������
		}
		// ������ֻ����0

		sort(factors.begin(), factors.end(), compare); // �������ӿɻ��ʹ�ã��Ծ���ֵ���Ϊ׼

		/* �������� */
		vector<product> products;
		long long sum = 0;   // �˻�
		int count = 1;       // ������

		if (factors.size() != 0)
		{
			long long temp = 1;
			for (int i = 0; i < factors.size(); i++) // ����ÿ������
			{
				temp = temp * factors[i];
				products.push_back(product(temp, i + 1));
			}
			sort(products.begin(), products.end());
			sum = products.back().val;     // ȡ�����˻�
			count = products.back().count; // �����Ӧ����
		}

		long long ans = sum; int min = count; // ansΪ����Ҫ������˻���minΪ�õ���������������������

		cout << " " << ans << " " << min << endl;
	}

	return 0;
}
