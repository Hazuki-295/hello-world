#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <sstream>
#include <unordered_map>
using namespace std;

struct Program {
	// ���ݳ�Ա
	queue<string> statements; // �������
	int rank;  // ������
	int quota; // ��ǰʱ�����

	// ���캯��
	Program(int rank, int quota) :quota(quota), rank(rank) {
		string temp;
		while (getline(cin, temp)) {
			statements.push(temp);
			if (temp == "end") // ÿ��������end������
				break;
		}
	}
};

class Concurrent {
private:
	// ���ݳ�Ա
	int programNum;      // �������
	int quota;           // ÿ��ִ�е�ʱ�����
	int lockedRank = 0;  // �������ĳ����(��δʹ��)
	bool locked = false; // ��
	deque<Program> waiting; // �ȴ�����(����ڲ�ӣ�ʹ��˫�˶���)
	queue<Program> block;   // ��������

	vector<int> Time; // ÿ������ִ��ʱ��

	// ��������
	unordered_map<char, int> variables;

	// ������ �� ������
	char operand1 = 0;
	string op, operand2;

public:
	Concurrent() {
		cin >> programNum;  // �������
		Time.resize(8);     // 7����䣬0��δ��
		for (int i = 1; i <= 7; i++) cin >> Time[i];
		cin >> quota;       // ÿ��ִ�е�ʱ�����

		char c = getchar(); // �����з�

		for (int i = 1; i <= programNum; i++) {   // ��ʼ��ÿ������
			waiting.push_back(Program(i, quota));
		}
	}

	/* �������� */
	void dispatch()
	{
		while (!waiting.empty())
		{
			Program *cur = &(waiting.front()); // ��ǰִ�еĳ���
			string curStatement; int id;       // ��ǰִ�е���������id

			bool changeProgram = false; // �˳�whileѭ��
			while (cur->quota > 0 && changeProgram == false) // ��ʱ����(����͸֧)
			{
				/* ִ����� */
				curStatement = cur->statements.front();
				id = patternMatch(curStatement);
				cur->quota -= Time[id]; // �۳�ʱ����

				switch (id) {
				case 1:
					/*if (!locked || (locked && lockedRank == cur->rank)) {*/ // ���û���������Լ�����
					if (isalpha(operand2[0])) // ������ֵ
						variables[operand1] = variables[operand2[0]];
					else { // ������ֵ
						int temp = stoi(operand2);
						variables[operand1] = temp;
					}
					/*}*/
					cur->statements.pop(); // ִ����һ�����
					break;
				case 2:
					/*if (!locked || (locked && lockedRank == cur->rank)) {*/ // ���û���������Լ�����
					if (isalpha(operand2[0])) // ������ֵ
						variables[operand1] += variables[operand2[0]];
					else { // ������ֵ
						int temp = stoi(operand2);
						variables[operand1] += temp;
					}
					/*}*/
					cur->statements.pop(); // ִ����һ�����
					break;
				case 3:
					/*if (!locked || (locked && lockedRank == cur->rank)) {*/ // ���û���������Լ�����
					if (isalpha(operand2[0])) // ������ֵ
						variables[operand1] -= variables[operand2[0]];
					else { // ������ֵ
						int temp = stoi(operand2);
						variables[operand1] -= temp;
					}
					/*}*/
					cur->statements.pop(); // ִ����һ�����
					break;

				case 4: /* �������� 4. print, 5. lock, 6. unlock, 7. end */
					cout << cur->rank << ": " << variables[operand1] << endl;
					cur->statements.pop(); // ִ����һ�����
					break;
				case 5: // lock��
					if (locked == false) {
						locked = true;
						lockedRank = cur->rank;
						cur->statements.pop(); // ִ����һ�����
						break;
					}
					else { // ������������
						cur->quota = quota; // û������������˷���
						block.push(*cur);   // �����������е�β��
						waiting.pop_front();
						changeProgram = true;
						break;
					}
				case 6: // unlock����
					locked = false;
					if (!block.empty()) { // �������в���
						// waiting.push_front(block.front()); // ��ӵ���ͷ
						waiting.insert(waiting.begin() + 1, block.front()); // ע�⣬��ǰ�ĳ���û������
						block.pop();
						cur = &(waiting.front()); // ע�⣺��Ϊͷ���ı䵱ǰָ����ָ��Ԫ�أ���Ҫ��ʽ������ȡ��ͷ
					}
					cur->statements.pop(); // ִ����һ�����
					break;
				case 7: // end����
					waiting.pop_front();
					changeProgram = true;
					break;
				}
			}

			if (cur->quota <= 0 && changeProgram == false) { // ʱ���Ȳ��㣬����ʣ�����
				cur->quota = quota;      // ���·���ʱ��
				waiting.push_back(*cur); // ��ִ�����񣬽���ȴ��������Ŷ�
				waiting.pop_front();
			}
		}
	}

	/* ���ʶ�𣬷��ض�Ӧ������š� */
	int patternMatch(string &statement)
	{
		/* �������� 4. print, 5. lock, 6. unlock, 7. end */
		if (statement.find("print") != string::npos)
		{
			stringstream buffer(statement);
			buffer >> op >> operand1; // op����print��operand1����var
			return 4;
		}
		if (statement == "lock")   return 5;
		if (statement == "unlock") return 6;
		if (statement == "end")    return 7;

		/* ������� 1. = , 2. += , 3. -= */
		stringstream buffer(statement);
		buffer >> operand1 >> op >> operand2;
		if (op == "=")  return 1;
		if (op == "+=") return 2;
		if (op == "-=") return 3;
	}
};

int main()
{
	Concurrent *obj = new Concurrent;
	obj->dispatch();

	return 0;
}
