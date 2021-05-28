#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
using namespace std;

string TrimWord(string word) // ת����ͳһ��ʽ
{
	for (auto &c : word) c = tolower(c); // תСд
	sort(word.begin(), word.end());      // ����
	return word;
}

int main()
{
	string line; // ���һ��

	set<string> result;             // ��Ž��(ԭ��ʽ)���Զ�����
	map<string, string> dictionary; // key��ת����ĸ�ʽ��value��ԭ��ʽ

	while (getline(cin, line) && line != "#") // ����һ��
	{
		string word, trim;          // �������ʣ������ĵ�������
		istringstream buffer(line); // ��buffer�󶨵��ն������

		while (buffer >> word)
		{
			map<string, string>::iterator temp; // ���ڼ���Ƿ��ظ�
			trim = TrimWord(word); // ������
			if ((temp = dictionary.find(trim)) == dictionary.end())  // ��һ�γ���
				dictionary.insert(pair<string, string>(trim, word)); // �����һ�γ��ֵ���ʽ�����ֵ�
			else if (word == temp->second) // �������һ�γ��ֵĸ�ʽ��ͬ
				continue; // ��������
			else // �����ⵥ��
				result.insert(temp->second); // ������ԭ��ʽ
		}
	}

	for (auto word : result) cout << word << endl;

	return 0;
}