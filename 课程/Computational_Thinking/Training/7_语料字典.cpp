#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

typedef struct { string word; unsigned count; } record, *precord; // 单词及其出现次数

bool operator> (const record &a, const record &b) // 按单词出现次数及字典顺序排序
{
	if (a.count > b.count) return true; // 按单词出现次数
	else if (a.count == b.count)
		if (a.word < b.word) // 按字典序
			return true;

	return false;
}

bool compare(record a, record b) { return a > b; } // 降序

int main()
{
	string line; vector<record> dictionary; // 存放最终单词

	while (getline(cin, line)) // 处理一行
	{
		string word; // 单个单词
		queue<string> Q;   // 存放提取的一行待处理单词
		line.push_back(' ');    // 补上结尾便于处理

		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == '-')
			{
				line.erase(line.begin() + i);
				i--;
			}
			else if (isblank(line[i]) || isdigit(line[i])) // 空格及数字置空
			{
				line[i] = ' ';
			}
			else if (ispunct(line[i]) && line[i] != '\'')  // 统一格式化标点
			{
				line[i] = '-';
			}
			else if (isalpha(line[i]) || line[i] == '\'')
				continue;
			else return 0;
		}

		int start = 0;       // 单词在字符串里的起始位置
		int end = 0;         // 单词在字符串里的终止位置
		bool entry = false;  // 标记遍历字符串的过程中是否已经进入了单词区间

		for (int i = 0; i < line.size(); i++)  // 开始提取单词
		{
			if (!entry)
			{
				if (isalpha(line[i])) // 确定单词起始位置
				{
					start = i;
					entry = true;         // 进入单词区间
				}
			}
			if (entry && !isalpha(line[i]) && line[i] != '\'' && line[i] != '-') // 两符号视为单词的一部分
			{
				end = i;              // 确认单词终止位置的下一个位置
				entry = false;        // 结束单词区间

				word = line.substr(start, end - start); // 分离出单词
				Q.push(word);
			}
		}

		while (!Q.empty()) // 处理每个单词 Trim words
		{
			word = Q.front(); Q.pop();
			for (int i = 0; i < word.size(); i++)
			{
				word[i] = tolower(word[i]); // 小写格式

				if (word[i] == '\''/* && word[i + 1] == 's'*/) // 去掉所有格
				{
					word.erase(word.begin() + i, word.end());
				}
				if (word[i] == '-') // 去掉连字符
				{
					word.erase(word.begin() + i);
					i--;
				}
			}

			if (word.size() == 0) continue;

			vector<record>::iterator it;
			for (it = dictionary.begin(); it != dictionary.end() && it->word != word; it++);
			if (it == dictionary.end()) // 第一次出现
				dictionary.push_back({ word , 1 });
			else
				it->count++;
		}
	}

	sort(dictionary.begin(), dictionary.end(), compare);  // 按单词出现次数及字典顺序排序

	for (auto temp : dictionary)
		cout << temp.word << endl;

	return 0;
}
