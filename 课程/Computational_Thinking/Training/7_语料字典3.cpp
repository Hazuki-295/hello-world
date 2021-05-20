#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

typedef struct { string word; unsigned count; } record, *precord;

bool cmp(record a, record b) { return (a.word < b.word); } // ����
bool cmp2(record a, record b) { return (a.count > b.count); } // ����

void bubblesort1(vector<record> &dictionary); // ���������㷨
void bubblesort2(vector<record> &dictionary); // ���������㷨

int main()
{
	string line; vector<record> dictionary;

	while (getline(cin, line)) // ����һ��
	{
		string word; // ��������

		/* Ԥ���� */
		for (auto &c : line)
		{
			if (c == '\'' || c == '-')
				continue;
			else if (isdigit(c) || iscntrl(c)) // ȥ�����֡����Ʒ�
				c = ' ';
			else if (!isgraph(c) || isspace(c))
				c = ' ';
			else if (!isalpha(c) && ispunct(c))
			c = '-'; // ����5 6
			//c = '.'; // ����5 6
			//c = ' '; // ����3 5
		/* ���� 3 �� 6 �����ַ��й� */
			else if (isalpha(c))
				c = tolower(c);    // Сд��ʽ
		}

		stringstream buffer(line);  // ��buffer�󶨵��ն������

		while (buffer >> word)
		{
			/* ��ȡ���� */
			auto c = word.begin();
			while (c != word.end())
			{
				if (*c == '\'') // ȥ�����и�
				{
					word.erase(c, word.end());
					break;
				}
				if (ispunct(*c))         // ȥ��������
				{
					word.erase(c);
					if (c == word.end()) // ɾ����β�˳�
						break;
					else
						continue;
				}
				c++;
			}

			vector<record>::iterator it;
			for (it = dictionary.begin(); it != dictionary.end() && it->word != word; it++);
			if (it == dictionary.end()) // ��һ�γ���
				dictionary.push_back({ word , 1 });
			else
				it->count++;
		}
	}

	// sort(dictionary.begin(), dictionary.end(), cmp);  // ����ĸ����
	// sort(dictionary.begin(), dictionary.end(), cmp2); // �����ʳ��ִ�������

	bubblesort1(dictionary); // ���������㷨������ĸ����
	bubblesort2(dictionary); // ���������㷨�������ʳ��ִ�������

	for (auto temp : dictionary)
		cout << temp.word << endl;

	return 0;
}

void bubblesort1(vector<record> &dictionary) // ���������㷨
{
	auto A = &dictionary[0]; int n = dictionary.size();
	bool sorted = false; // ���������־�����ȼٶ���δ����
	while (!sorted) {    // ����δȷ����ȫ������֮ǰ�����˽���ɨ�轻��
		sorted = true;   // �ٶ��Ѿ�����
		for (int i = 1; i < n; i++) { // ����������Լ�鵱ǰ��ΧA[0, n)�ڵĸ�����Ԫ��
			if (dictionary[i - 1].word > dictionary[i].word) {    // һ��A[i - 1]��A[i]������
				swap(A[i - 1], A[i]); // ����֮����
				sorted = false;       // �����������ܱ�֤����Ҫ��������־
			}
		}
		n--; //����ĩԪ�ر�Ȼ��λ���ʿ������̴��������е���Ч����
	} //���������ͱ�־λsorted���ɼ�ʱ��ǰ�˳���������������������n - 1��ɨ�轻��
}

void bubblesort2(vector<record> &dictionary) // ���������㷨
{
	auto A = &dictionary[0]; int n = dictionary.size();
	bool sorted = false; // ���������־�����ȼٶ���δ����
	while (!sorted) {    // ����δȷ����ȫ������֮ǰ�����˽���ɨ�轻��
		sorted = true;   // �ٶ��Ѿ�����
		for (int i = 1; i < n; i++) { // ����������Լ�鵱ǰ��ΧA[0, n)�ڵĸ�����Ԫ��
			if (dictionary[i - 1].count < dictionary[i].count) {    // һ��A[i - 1]��A[i]������
				swap(A[i - 1], A[i]); // ����֮����
				sorted = false;       // �����������ܱ�֤����Ҫ��������־
			}
		}
		n--; //����ĩԪ�ر�Ȼ��λ���ʿ������̴��������е���Ч����
	} //���������ͱ�־λsorted���ɼ�ʱ��ǰ�˳���������������������n - 1��ɨ�轻��
}