#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef struct frequency { char alpha = 'A'; int freq = 0; } Alpha, *pAlpha;

int cmp2(const void *a, const void *b)
{
	if (((pAlpha)a)->freq < ((pAlpha)b)->freq)
		return 1;
	else if (((pAlpha)a)->freq == ((pAlpha)b)->freq)
		return 0;
	else
		return -1;
}

bool cmp(Alpha a, Alpha b) { return (a.freq > b.freq); } // 降序

int main()
{
	// 字母可以重排，则字母的位置并不重要，要判断是否存在映射，统计两个字符串中每个字母出现的次数即可。
	string s1, s2; cin >> s1 >> s2;

	vector<Alpha> a(26), b(26); // 字母出现次数
	for (int i = 0; i < 26; i++)
	{
		a[i].alpha += i; b[i].alpha += i;
	}

	for (auto c : s1) a[c - 'A'].freq++;
	for (auto c : s2) b[c - 'A'].freq++;

	//qsort(&a[0], a.size(), sizeof(Alpha), cmp2);
	//qsort(&b[0], b.size(), sizeof(Alpha), cmp2);
	sort(a.begin(), a.end(), cmp);
	sort(b.begin(), b.end(), cmp);

	bool equal = true;
	for (int i = 0; i < 26; i++)
		if (a[i].freq != b[i].freq)
			equal = false;
	if (equal)
	{
		cout << "YES" << endl;
		string result;
		for (int i = 0; i < 26; i++)
		{
			if (a[i].freq != 0)
			{
				result.push_back(a[i].alpha); result += "->";
				result.push_back(b[i].alpha); result += " ";
				//cout << a[i].alpha << "->" << b[i].alpha << " ";
			}
		}
		result.erase(result.size() - 1);
		cout << result << endl;
	}
	else
		cout << "NO" << endl;

	return 0;
}
