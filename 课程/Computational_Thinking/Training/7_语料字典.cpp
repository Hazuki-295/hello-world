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
	string line;
	vector<record> dictionary;

	while (getline(cin, line)) // 处理一行
	{
		string word; // 单个单词

		/* 预处理 */
		for (auto &c : line)
		{
			if (c == '\'' || c == '-')
				continue;
			else if (isdigit(c) || iscntrl(c)) // 去掉数字、控制符
				c = ' ';
			else if (!isgraph(c) || isspace(c))
				c = ' ';
			else if (isalpha(c))
				c = tolower(c);    // 小写形式
		}

		stringstream buffer(line);  // 将buffer绑定到刚读入的行

		while (buffer >> word)
		{
			/* 提取单词 */
			auto c = word.begin();
			while (c != word.end())
			{
				if (*c == '\'') // 去掉所有格
				{
					word.erase(c, word.end());
					break;
				}
				if (ispunct(*c))         // 去掉标点符号
				{
					word.erase(c);
					if (c == word.end()) // 删掉结尾退出
						break;
					else
						continue;
				}
				c++;
			}

			vector<record>::iterator it;
			for (it = dictionary.begin(); it != dictionary.end() && it->word != word; it++);
			if (it == dictionary.end()) // 第一次出现
				dictionary.push_back({ word , 1 });
			else
				it->count++;
		}
	}

	sort(dictionary.begin(), dictionary.end(), cmp);  // 按单词出现次数及字典顺序排序

	for (auto temp : dictionary)
		cout << temp.word << endl;

	return 0;
}
