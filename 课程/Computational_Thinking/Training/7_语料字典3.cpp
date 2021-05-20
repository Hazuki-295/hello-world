#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

typedef struct { string word; unsigned count; } record, *precord;

bool cmp(record a, record b) { return (a.word < b.word); } // 升序
bool cmp2(record a, record b) { return (a.count > b.count); } // 降序

void bubblesort1(vector<record> &dictionary); // 起泡排序算法
void bubblesort2(vector<record> &dictionary); // 起泡排序算法

int main()
{
	string line; vector<record> dictionary;

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
			else if (!isalpha(c) && ispunct(c))
			c = '-'; // 错误5 6
			//c = '.'; // 错误5 6
			//c = ' '; // 错误3 5
		/* 错误 3 和 6 与连字符有关 */
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

	// sort(dictionary.begin(), dictionary.end(), cmp);  // 按字母排序
	// sort(dictionary.begin(), dictionary.end(), cmp2); // 按单词出现次数排序

	bubblesort1(dictionary); // 起泡排序算法，按字母排序
	bubblesort2(dictionary); // 起泡排序算法，按单词出现次数排序

	for (auto temp : dictionary)
		cout << temp.word << endl;

	return 0;
}

void bubblesort1(vector<record> &dictionary) // 起泡排序算法
{
	auto A = &dictionary[0]; int n = dictionary.size();
	bool sorted = false; // 整体排序标志，首先假定尚未排序
	while (!sorted) {    // 在尚未确认已全局排序之前，逐趟进行扫描交换
		sorted = true;   // 假定已经排序
		for (int i = 1; i < n; i++) { // 自左向右逐对检查当前范围A[0, n)内的各相邻元素
			if (dictionary[i - 1].word > dictionary[i].word) {    // 一旦A[i - 1]与A[i]逆序，则
				swap(A[i - 1], A[i]); // 交换之，并
				sorted = false;       // 因整体排序不能保证，需要清除排序标志
			}
		}
		n--; //至此末元素必然就位，故可以缩短待排序序列的有效长度
	} //借助布尔型标志位sorted，可及时提前退出，而不致总是蛮力地做n - 1趟扫描交换
}

void bubblesort2(vector<record> &dictionary) // 起泡排序算法
{
	auto A = &dictionary[0]; int n = dictionary.size();
	bool sorted = false; // 整体排序标志，首先假定尚未排序
	while (!sorted) {    // 在尚未确认已全局排序之前，逐趟进行扫描交换
		sorted = true;   // 假定已经排序
		for (int i = 1; i < n; i++) { // 自左向右逐对检查当前范围A[0, n)内的各相邻元素
			if (dictionary[i - 1].count < dictionary[i].count) {    // 一旦A[i - 1]与A[i]逆序，则
				swap(A[i - 1], A[i]); // 交换之，并
				sorted = false;       // 因整体排序不能保证，需要清除排序标志
			}
		}
		n--; //至此末元素必然就位，故可以缩短待排序序列的有效长度
	} //借助布尔型标志位sorted，可及时提前退出，而不致总是蛮力地做n - 1趟扫描交换
}