#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct product { // �˻�
	// ���ݳ�Ա
	long long val; int start, end, wide; // �˻�����ֹ��Χ����Χ��С
	// ���캯��
	product(long long val, int start, int end, int wide) :val(val), start(start), end(end), wide(wide) {}
};

bool operator<(const product &a, const product &b) { // ���ȼ�����
	if (a.val < b.val)
		return true;
	else if (a.val == b.val)
		if (a.wide > b.wide)
			return true;
		else if (a.wide == b.wide)
			if (a.start > b.start)
				return true;
	return false;
}

/* Problem C. ���� */
int main()
{
	// �������ɸ�����S=S1,S2,...,Sn���������ɸ������������˻��Ƕ��٣�

	// ���˻�������˳�򲻱�
	string line; int cases = 0;

	while (getline(cin, line)) {
		cout << "Case " << ++cases << ":";
		stringstream buffer(line);

		int temp;
		vector<int> factors; // ����

		while (buffer >> temp) factors.push_back(temp);

		/* �������� */
		vector<product> result; // �˻�

		int start, end, wide;
		for (int i = 0; i <= factors.size() - 1; i++) { // ö����˻�
			temp = factors[i];
			start = i; end = i; wide = end - start;
			result.push_back(product(temp, start, end, wide));
			for (int j = i + 1; j <= factors.size() - 1; j++) {
				temp *= factors[j];
				end = j; wide = end - start;
				result.push_back(product(temp, start, end, wide));
			}
		}

		long long ans = 0; // ansΪ����Ҫ������˻�����Ӧ����ֹ��Χ

		sort(result.begin(), result.end());
		product answer(result.back());
		ans = answer.val; start = answer.start; end = answer.end;

		cout << " " << ans << " " << start << "-" << end << endl;
	}

	return 0;
}
