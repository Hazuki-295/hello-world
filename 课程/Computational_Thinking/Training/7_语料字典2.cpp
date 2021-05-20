#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

typedef struct { string word; unsigned count; } record, *precord;

bool operator> (const record &a, const record &b) // �����ʳ��ִ������ֵ�˳������
{
	if (a.count > b.count) return true; // �����ʳ��ִ���
	else if (a.count == b.count)
		if (a.word < b.word) // ���ֵ���
			return true;

	return false;
}

bool cmp(record a, record b) { return a > b; } // ����

int main()
{
	string line; vector<record> dictionary;

	while (getline(cin, line)) // ����һ��
	{
		for (int i = 0; i < line.size(); i++) // ����3-5
		{
			if (isalpha(line[i])) line[i] = tolower(line[i]);
			else if (line[i] == '\'' && line[i + 1] == 's')
			{
				line[i] = ' '; line[i + 1] = ' ';
			}
			else if (line[i] == '-')
			{
				/*line.erase(line.begin() + i);
				i--;*/
			}
			else line[i] = ' ';
		}

		string word; // ��������
		istringstream buffer(line);  // ��buffer�󶨵��ն������

		while (buffer >> word)
		{
			/* trim */
			for (int i = 0; i < word.size(); i++)
			{
				if (word[i] == '\''/* && word[i + 1] == 's'*/) // ȥ�����и�
				{
					word.erase(word.begin() + i, word.end());
				}
				if (word[i] == '-') // ȥ�����ַ�
				{
					word.erase(word.begin() + i);
				}
			}

			vector<record>::iterator it;
			for (it = dictionary.begin(); it != dictionary.end() && it->word != word; it++);
			if (it == dictionary.end()) // ��һ�γ���
				dictionary.push_back({ word , 1 });
			else
				it->count++;
		}
	}

	std::sort(dictionary.begin(), dictionary.end(), cmp);  // �����ʳ��ִ������ֵ�˳������

	for (auto temp : dictionary)
		cout << temp.word << endl;

	return 0;
}
