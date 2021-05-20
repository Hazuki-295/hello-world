#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

typedef struct { string word; unsigned count; } record, *precord;

bool operator> (const record &a, const record &b) // 按单词出现次数及字典顺序排序
{
	if (a.count > b.count) return true; // 按单词出现次数
	else if (a.count == b.count)
		if (a.word < b.word) // 按字典序
			return true;

	return false;
}

bool cmp(record a, record b) { return a > b; } // 降序

int main()
{
	string line; vector<record> dictionary;

	while (getline(cin, line)) // 处理一行
	{
		for (int i = 0; i < line.size(); i++) // 错误3-5
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

		string word; // 单个单词
		istringstream buffer(line);  // 将buffer绑定到刚读入的行

		while (buffer >> word)
		{
			/* trim */
			for (int i = 0; i < word.size(); i++)
			{
				if (word[i] == '\''/* && word[i + 1] == 's'*/) // 去掉所有格
				{
					word.erase(word.begin() + i, word.end());
				}
				if (word[i] == '-') // 去掉连字符
				{
					word.erase(word.begin() + i);
				}
			}

			vector<record>::iterator it;
			for (it = dictionary.begin(); it != dictionary.end() && it->word != word; it++);
			if (it == dictionary.end()) // 第一次出现
				dictionary.push_back({ word , 1 });
			else
				it->count++;
		}
	}

	std::sort(dictionary.begin(), dictionary.end(), cmp);  // 按单词出现次数及字典顺序排序

	for (auto temp : dictionary)
		cout << temp.word << endl;

	return 0;
}
