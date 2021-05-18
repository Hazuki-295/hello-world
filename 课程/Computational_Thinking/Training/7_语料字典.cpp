#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

typedef struct { string word; unsigned count; } record, *precord;

//bool cmp(record a, record b) { return (a.word < b.word); } // 升序
//bool cmp2(record a, record b) { return (a.count > b.count); } // 降序
int cmp(const void *a, const void *b) // 升序
{
	if (((precord)a)->word > ((precord)b)->word)
		return 1;
	else if (((precord)a)->word == ((precord)b)->word)
		return 0;
	else
		return -1;
}

int cmp2(const void *a, const void *b) // 降序
{
	if (((precord)a)->count < ((precord)b)->count)
		return 1;
	else if (((precord)a)->count == ((precord)b)->count)
		return 0;
	else
		return -1;
}

int main()
{
	string line; stringstream buffer;
	vector<record> dictionary;

	while (getline(cin, line)) // 处理一行
	{
		string word;                 // 单个单词
		istringstream buffer(line);  // 将buffer绑定到刚读入的行

		while (buffer >> word)
		{
			// 处理单词
			for (auto c = word.begin(); c != word.end(); )
			{
				*c = tolower(*c);    // 小写形式
				if (*c == '\'')      // 去掉连字符后面的单词
				{
					word.erase(c, word.end());
					break;
				}
				if (ispunct(*c))         // 去掉标点符号
				{
					word.erase(c);
					if (c == word.end()) // 删掉结尾赶紧退出
						break;
					else
						continue;
				}
				c++;
			}
			// auto it = find(dictionary.begin(), dictionary.end(), word);
			vector<record>::iterator it;
			for (it = dictionary.begin(); it != dictionary.end() && it->word != word; it++);

			if (it == dictionary.end()) // 第一次出现
				dictionary.push_back({ word , 1 });
			else
				it->count++;
		}
	}
	//sort(dictionary.begin(), dictionary.end(), cmp);  // 按字母排序
	//sort(dictionary.begin(), dictionary.end(), cmp2); // 按单词出现次数排序

	qsort(&dictionary[0], dictionary.size(), sizeof(record), cmp);  // 按字母排序
	qsort(&dictionary[0], dictionary.size(), sizeof(record), cmp2); // 按单词出现次数排序

	for (auto temp : dictionary)
		cout << temp.word << endl;

	return 0;
}
