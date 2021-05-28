#include <iostream>
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
	if (a.val < b.val)
		return true;
	else if (a.val == b.val)
		if (a.count > b.count)
			return true;

	return false;
}

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
		vector<int> nege_factors; // ������
		vector<int> posi_factors; // ������

		while (buffer >> temp)
		{
			if (temp > 0)
				posi_factors.push_back(temp); // ������
			else if (temp < 0)
				nege_factors.push_back(temp); // ������
		}
		// ������ֻ����0

		sort(posi_factors.begin(), posi_factors.end(), greater<int>()); // �Ӵ�С����
		sort(nege_factors.begin(), nege_factors.end(), less<int>());    // ��С��������

		/* �������� */
		vector<product> nege_part; // �Ƚϸ��ӣ��Ӵ�С��

		long long sum_nege = 0;   // �������ֳ˻�
		int count_nege = 0;    // �������������� 
		if (nege_factors.size() != 0)
		{
			long long temp = 1;
			for (int i = 0; i < nege_factors.size(); i++)
			{
				temp = temp * nege_factors[i];
				nege_part.push_back(product(temp, i + 1));
			}
			sort(nege_part.begin(), nege_part.end());
			sum_nege = nege_part.back().val;     // ȡ�����˻�
			count_nege = nege_part.back().count; // �����Ӧ����
		}

		/* ���������� */
		vector<product> posi_part;
		long long sum_posi = 0;   // �������ֳ˻�
		int count_posi = 0;    // ��������������
		if (posi_factors.size() != 0)
		{
			long long temp = 1;
			for (int i = 0; i < posi_factors.size(); i++)
			{
				temp = temp * posi_factors[i];
				posi_part.push_back(product(temp, i + 1));
			}
			sort(posi_part.begin(), posi_part.end());
			sum_posi = posi_part.back().val;     // ȡ�����˻�
			count_posi = posi_part.back().count; // �����Ӧ����
		}

		long long ans = 0; int min = 0; // ansΪ����Ҫ������˻���minΪ�õ���������������������

		vector<product> result; // ���������
		result.push_back(product(sum_posi, count_posi));
		result.push_back(product(sum_nege, count_nege));
		result.push_back(product(sum_posi * sum_nege, count_posi + count_nege));
		sort(result.begin(), result.end());
		ans = result.back().val; min = result.back().count;

		if (ans == 0) min = 1;

		cout << " " << ans << " " << min << endl;
	}

	return 0;
}
