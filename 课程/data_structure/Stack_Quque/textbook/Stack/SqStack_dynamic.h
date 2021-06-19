#include <iostream>
using namespace std;

typedef int ElemType;

/* ջ��˳��洢��ʾ(��̬��С) */
#define STACK_INIT_SIZE 100 // �洢�ռ��ʼ������
#define STACKINCREMENT 10   // �洢�ռ��������

typedef struct {
	ElemType *base; // ����ַ
	ElemType *top;  // ջ��ָ��
	int stacksize;  // ��ǰ�ѷ���Ĵ洢�ռ�(��Ԫ��Ϊ��λ)
} SqStack;

/* ����һ����ջ */
bool InitStack(SqStack &S) {
	S.base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (!S.base) {
		return false; // �洢����ʧ��
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return true;
}

/* ��ջ�� */
bool StackEmpty(SqStack S) {
	return S.top == S.base;
}

/* ��ջ���� */
bool Push(SqStack &S, ElemType x) {
	if (S.top - S.base == S.stacksize) { // ջ��������
		S.base = (ElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(ElemType));
		if (!S.base) {
			return false;
		}
		S.top = S.base + S.stacksize; // ֮ǰ��ջ������
		S.stacksize += STACKINCREMENT;
	}
	*(S.top++) = x;  // ��ǰһ�ַ�����ͬ���Ƚ�ջ��ָ���ټ�1��ջ��ָ��ʼ��ָ��ջ��Ԫ�ص���һ��λ�ã�
	return true;

}

/* ��ջ���� */
bool Pop(SqStack &S, ElemType &x) {
	if (S.top == S.base) { // ջ�գ�����
		return false;
	}
	x = *(--S.top);      // ָ���ȼ�1����ȡֵ��x
	return true;
}

/* ��ջ��Ԫ�أ���ջ�ǿգ�����x����ջ��Ԫ�� */
bool GetTop(SqStack S, ElemType &x) {
	if (S.top == S.base)     // ջ�գ�����
		return false;
	x = *(S.top - 1);   // x��¼ջ��Ԫ��
	return true;
}

int main() {
	SqStack S; InitStack(S);

	cout << "��������ջԪ�ظ�����";
	int num; cin >> num;

	cout << "������" << num << "����ջԪ�أ�";
	int delete1, insert1;
	for (int i = 0; i < num; i++) {
		cin >> insert1;
		Push(S, insert1);
	}

	/* ȡջ�� */
	int top; GetTop(S, top);
	cout << "ջ��Ԫ�أ�" << top << endl;

	/* ��ջ���� */
	cout << "��ջԪ�أ�\n";
	while (!StackEmpty(S)) {
		Pop(S, delete1);
		cout << delete1 << " ";
	}
	cout << endl;

}
