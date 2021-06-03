#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <sstream>
#include <unordered_map>
using namespace std;

struct Program {
	// 数据成员
	queue<string> statements; // 语句序列
	int rank;  // 程序编号
	int quota; // 当前时间配额

	// 构造函数
	Program(int rank, int quota) :quota(quota), rank(rank) {
		string temp;
		while (getline(cin, temp)) {
			statements.push(temp);
			if (temp == "end") // 每个程序以end语句结束
				break;
		}
	}
};

class Concurrent {
private:
	// 数据成员
	int programNum;      // 程序个数
	int quota;           // 每次执行的时间配额
	int lockedRank = 0;  // 锁变量的程序号(并未使用)
	bool locked = false; // 锁
	deque<Program> waiting; // 等待队列(因存在插队，使用双端队列)
	queue<Program> block;   // 阻塞队列

	vector<int> Time; // 每条语句的执行时间

	// 公共变量
	unordered_map<char, int> variables;

	// 操作数 和 操作符
	char operand1 = 0;
	string op, operand2;

public:
	Concurrent() {
		cin >> programNum;  // 程序个数
		Time.resize(8);     // 7种语句，0号未用
		for (int i = 1; i <= 7; i++) cin >> Time[i];
		cin >> quota;       // 每次执行的时间配额

		char c = getchar(); // 处理换行符

		for (int i = 1; i <= programNum; i++) {   // 初始化每个程序
			waiting.push_back(Program(i, quota));
		}
	}

	/* 调度任务 */
	void dispatch()
	{
		while (!waiting.empty())
		{
			Program *cur = &(waiting.front()); // 当前执行的程序
			string curStatement; int id;       // 当前执行的任务、任务id

			bool changeProgram = false; // 退出while循环
			while (cur->quota > 0 && changeProgram == false) // 有时间额度(可以透支)
			{
				/* 执行语句 */
				curStatement = cur->statements.front();
				id = patternMatch(curStatement);
				cur->quota -= Time[id]; // 扣除时间额度

				switch (id) {
				case 1:
					/*if (!locked || (locked && lockedRank == cur->rank)) {*/ // 如果没锁，或是自己锁的
					if (isalpha(operand2[0])) // 变量赋值
						variables[operand1] = variables[operand2[0]];
					else { // 常量赋值
						int temp = stoi(operand2);
						variables[operand1] = temp;
					}
					/*}*/
					cur->statements.pop(); // 执行下一条语句
					break;
				case 2:
					/*if (!locked || (locked && lockedRank == cur->rank)) {*/ // 如果没锁，或是自己锁的
					if (isalpha(operand2[0])) // 变量赋值
						variables[operand1] += variables[operand2[0]];
					else { // 常量赋值
						int temp = stoi(operand2);
						variables[operand1] += temp;
					}
					/*}*/
					cur->statements.pop(); // 执行下一条语句
					break;
				case 3:
					/*if (!locked || (locked && lockedRank == cur->rank)) {*/ // 如果没锁，或是自己锁的
					if (isalpha(operand2[0])) // 变量赋值
						variables[operand1] -= variables[operand2[0]];
					else { // 常量赋值
						int temp = stoi(operand2);
						variables[operand1] -= temp;
					}
					/*}*/
					cur->statements.pop(); // 执行下一条语句
					break;

				case 4: /* 其他操作 4. print, 5. lock, 6. unlock, 7. end */
					cout << cur->rank << ": " << variables[operand1] << endl;
					cur->statements.pop(); // 执行下一条语句
					break;
				case 5: // lock锁
					if (locked == false) {
						locked = true;
						lockedRank = cur->rank;
						cur->statements.pop(); // 执行下一条语句
						break;
					}
					else { // 其他程序锁了
						cur->quota = quota; // 没有用完的配额就浪费了
						block.push(*cur);   // 放入阻塞队列的尾部
						waiting.pop_front();
						changeProgram = true;
						break;
					}
				case 6: // unlock解锁
					locked = false;
					if (!block.empty()) { // 阻塞队列不空
						// waiting.push_front(block.front()); // 插队到队头
						waiting.insert(waiting.begin() + 1, block.front()); // 注意，当前的程序还没处理完
						block.pop();
						cur = &(waiting.front()); // 注意：因为头插会改变当前指针所指的元素，需要显式地重新取队头
					}
					cur->statements.pop(); // 执行下一条语句
					break;
				case 7: // end结束
					waiting.pop_front();
					changeProgram = true;
					break;
				}
			}

			if (cur->quota <= 0 && changeProgram == false) { // 时间额度不足，还有剩余语句
				cur->quota = quota;      // 重新分配时间
				waiting.push_back(*cur); // 不执行任务，进入等待队列中排队
				waiting.pop_front();
			}
		}
	}

	/* 语句识别，返回对应的语句编号。 */
	int patternMatch(string &statement)
	{
		/* 其他操作 4. print, 5. lock, 6. unlock, 7. end */
		if (statement.find("print") != string::npos)
		{
			stringstream buffer(statement);
			buffer >> op >> operand1; // op读入print，operand1读入var
			return 4;
		}
		if (statement == "lock")   return 5;
		if (statement == "unlock") return 6;
		if (statement == "end")    return 7;

		/* 运算操作 1. = , 2. += , 3. -= */
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
