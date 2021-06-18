#include <iostream>
using namespace std;

#define MaxSize 50 // ���Ա����󳤶�

/* ˳���б�ģ���� */
template <typename T> class List {

private:
	using ElemType = T;

	/* ���Ա��˳��洢�ṹ(��̬����) */
	ElemType *data; // ˳����Ԫ��
	int length;     // ˳���ĵ�ǰ����

public:
	// ���캯��
	List() { InitList(); } //Ĭ��

	/* ��ʼ��һ���յ�˳���(Ϊ˳������洢�ռ�) */
	void InitList()
	{
		data = new ElemType[MaxSize];
		length = 0;  // �ձ���Ϊ0
	}

	void CreatList(int n)
	{
		length = n; ElemType temp;
		for (int i = 0; i < n; i++)
		{
			cin >> temp;
			data[i] = temp;
		}
	}

	/* ����������ڱ�L�е�x��λ��֮ǰ�����µ�����Ԫ��e */
	bool ListInsert(int x, ElemType e)
	{
		if (x<1 || x > length + 1) // �����λ�÷Ƿ�
			return false;

		if (length >= MaxSize) // ��ǰ�洢�ռ����������ܲ���
			return false;

		ElemType *p, *q;    // p��qΪ����ָ�� 
		q = &(data[x - 1]); // qΪ����λ��
		for (p = &(data[length - 1]); p >= q; p--) // ����λ�ü�֮���Ԫ������
		{
			*(p + 1) = *p;
		}
		*q = e;     // �ڲ���λ�� q �����µ�Ԫ��e
		length++; // ����1
		return true;
	}

	/* ɾ��������ɾ����L�е�x��λ�õ�Ԫ�أ�����e����ɾ��Ԫ�ص�ֵ */
	bool ListDelete(int x, ElemType &e)
	{
		if (x<1 || x>length) // ɾ����λ�÷Ƿ�
			return false;

		ElemType *p, *q; // p��qΪ����ָ�� 

		p = &(data[x - 1]);        // pΪ��ɾ��Ԫ�ص�λ��
		e = *p;                    // ��ɾ��Ԫ�ص�ֵ����e
		q = &(data[length - 1]);   // ��βԪ�ص�λ��
		for (p++; p <= q; p++)     // ��ɾ��Ԫ��֮���Ԫ������
		{
			*(p - 1) = *p;
		}
		length--; // ����1
		return true;
	}

	/* ��ֵ���Ҳ������ڱ�L�в��Ҿ��и����ؼ���(e)ֵ��Ԫ�� */
	int LocateElem(ElemType e)
	{
		for (int i = 0; i < length; i++)
			if (data[i] == e)
				return i + 1; // �±�Ϊi��Ԫ��ֵ����e��������λ��i+1
		return 0;             // �˳�ѭ����˵������ʧ��(0��ʾδ�ҵ�)
	}

	/* ��λ���Ҳ������ҵ���L�е�i��λ�õ�Ԫ�أ�����e������ֵ */
	bool GetElem(int x, ElemType &e)
	{
		if (x<1 || x>length)
			return false;
		e = data[x - 1]; // λ��Ϊi��Ԫ�أ����±�Ϊi-1
		return true;
	}

	/* ���������˳��������Ա�L������Ԫ��ֵ */
	void PrintList()
	{
		for (int i = 0; i < length; i++)
		{
			cout << data[i] << ' ';
		}
		cout << endl;
	}

	int LinkLength() { return length; };

	void ListTest();
}; // SqList

template<typename T> void List<T>::ListTest()
{
	cout << "�����������������" << endl;
	int n; cin >> n; cout << '\n';

	cout << "������" << n << "������Ԫ�أ�\n";
	CreatList(n);

	cout << "\n��ʼ����ɡ�\n";
	/* ���Դ��� */
	cout << "��ǰ������Ϊ��\n" << LinkLength() << '\n';
	cout << "��ǰ����Ԫ��Ϊ��\n"; PrintList(); cout << "\n\n";

	/* �������� */
	int delete1, insert1; ElemType temp;
	cout << "ɾ����x��Ԫ�أ�"; cin >> delete1;
	ListDelete(delete1, temp);
	/* ���Դ��� */
	cout << "��ǰ������Ϊ��\n" << LinkLength() << '\n';
	cout << "��ǰ����Ԫ��Ϊ��\n"; PrintList(); cout << "\n\n";

	cout << "�ڵ�x��Ԫ��֮ǰ����Ԫ�أ�"; cin >> insert1;
	cout << "�����Ԫ�أ�"; cin >> temp;
	ListInsert(insert1, temp);
	/* ���Դ��� */
	cout << "��ǰ������Ϊ��\n" << LinkLength() << '\n';
	cout << "��ǰ����Ԫ��Ϊ��\n"; PrintList(); cout << "\n\n";
}

int main()
{
	List<int> L;
	L.ListTest();
}
