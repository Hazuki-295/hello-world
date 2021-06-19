#include <iostream>
using namespace std;

typedef int ElemType;

/* 栈的顺序存储表示(动态大小) */
#define STACK_INIT_SIZE 100 // 存储空间初始分配量
#define STACKINCREMENT 10   // 存储空间分配增量

typedef struct {
	ElemType *base; // 基地址
	ElemType *top;  // 栈顶指针
	int stacksize;  // 当前已分配的存储空间(以元素为单位)
} SqStack;

/* 构造一个空栈 */
bool InitStack(SqStack &S) {
	S.base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (!S.base) {
		return false; // 存储分配失败
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return true;
}

/* 判栈空 */
bool StackEmpty(SqStack S) {
	return S.top == S.base;
}

/* 进栈操作 */
bool Push(SqStack &S, ElemType x) {
	if (S.top - S.base == S.stacksize) { // 栈满，扩容
		S.base = (ElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(ElemType));
		if (!S.base) {
			return false;
		}
		S.top = S.base + S.stacksize; // 之前的栈满条件
		S.stacksize += STACKINCREMENT;
	}
	*(S.top++) = x;  // 与前一种方法不同，先进栈，指针再加1（栈顶指针始终指向栈顶元素的下一个位置）
	return true;

}

/* 出栈操作 */
bool Pop(SqStack &S, ElemType &x) {
	if (S.top == S.base) { // 栈空，报错
		return false;
	}
	x = *(--S.top);      // 指针先减1，再取值给x
	return true;
}

/* 读栈顶元素，若栈非空，则用x返回栈顶元素 */
bool GetTop(SqStack S, ElemType &x) {
	if (S.top == S.base)     // 栈空，报错
		return false;
	x = *(S.top - 1);   // x记录栈顶元素
	return true;
}

int main() {
	SqStack S; InitStack(S);

	cout << "请输入入栈元素个数：";
	int num; cin >> num;

	cout << "请输入" << num << "个入栈元素：";
	int delete1, insert1;
	for (int i = 0; i < num; i++) {
		cin >> insert1;
		Push(S, insert1);
	}

	/* 取栈顶 */
	int top; GetTop(S, top);
	cout << "栈顶元素：" << top << endl;

	/* 出栈测试 */
	cout << "出栈元素：\n";
	while (!StackEmpty(S)) {
		Pop(S, delete1);
		cout << delete1 << " ";
	}
	cout << endl;

}
