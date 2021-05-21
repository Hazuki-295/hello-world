#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
using namespace std;

string TrimWord(string word) // 转换成统一格式
{
	for (auto &c : word) c = tolower(c); // 转小写
	sort(word.begin(), word.end());      // 排序
	return word;
}

int main()
{
	string line; // 存放一行

	set<string> result;             // 存放结果(原格式)，自动排序
	map<string, string> dictionary; // key：转换后的格式，value：原格式

	while (getline(cin, line) && line != "#") // 处理一行
	{
		string word, trim;          // 单个单词，处理后的单个单词
		istringstream buffer(line); // 将buffer绑定到刚读入的行

		while (buffer >> word)
		{
			map<string, string>::iterator temp; // 用于检查是否重复
			trim = TrimWord(word); // 处理单词
			if ((temp = dictionary.find(trim)) == dictionary.end())  // 第一次出现
				dictionary.insert(pair<string, string>(trim, word)); // 以其第一次出现的形式加入字典
			else if (word == temp->second) // 若与其第一次出现的格式相同
				continue; // 不做处理
			else // 是特殊单词
				result.insert(temp->second); // 存入其原格式
		}
	}

	for (auto word : result) cout << word << endl;

	return 0;
}