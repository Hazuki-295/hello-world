#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

#define NULLKEY -999

template <typename K, typename V> struct Entry { //����ģ����
	K key; V value; //�ؼ��롢��ֵ
	Entry(K k = K(), V v = V()) : key(k), value(v) {}; //Ĭ�Ϲ��캯��
	Entry(Entry<K, V> const &e) : key(e.key), value(e.value) {}; //���ڿ�¡�Ĺ��캯��
	bool operator< (Entry<K, V> const &e) { return key < e.key; }  //�Ƚ�����С��
	bool operator> (Entry<K, V> const &e) { return key > e.key; }  //�Ƚ���������
	bool operator== (Entry<K, V> const &e) { return key == e.key; } //�е���������
	bool operator!= (Entry<K, V> const &e) { return key != e.key; } //�е�����������
}; //�����ڱȽ������е������Ӵ����󣬲����ϸ����ִ��������Ӧ�Ĺؼ���

template<typename KeyType, typename ValueType> struct hashElem {
	// ���ݳ�Ա
	KeyType key; ValueType val; // ��Ϣֻ��һ�����ؼ���key����
	// ���캯��
	hashElem(KeyType key = KeyType(), ValueType val = ValueType()) :key(NULLKEY), val(val) {}
	hashElem(KeyType key, ValueType val = ValueType()) :key(key), val(0) {}
};

template<typename KeyType> struct hashElem {
	// ���ݳ�Ա
	KeyType key; int val; // ��Ϣֻ��һ�����ؼ���key����
	// ���캯��
	hashElem() :key(NULLKEY), val(0) {}
	hashElem(KeyType key) :key(key), val(0) {}
};

istream &operator>>(istream &is, hashElem<int> &temp) {
	is >> temp.key;
	return is;
}

ostream &operator<<(ostream &os, hashElem<int> &temp) {
	os << temp.key;
	return os;
}

/* ���Ŷ�ַ��ϣ�� */
template<typename KeyType, typename ElemType> class HashTable // keyΪ�ؼ���
{
private:
	vector<ElemType> elem;
	int hashsize = 15;
public:
	queue<ElemType> print; // ���ڴ���������

	HashTable(int size) {
		elem.resize(hashsize); // ��ϣ��Ϊ15����ַΪ0��14����ʼ��Ϊ-999
		ElemType temp;
		for (int i = 0; i < size; i++) {
			cin >> temp;
			insertHash(temp);
		}
	}

	int Hash(KeyType key) { return key % 11; } // ��ϣ����ΪH(key)=key mod 11

	bool searchHash(KeyType key, int &poi, int &count) { // �ؼ��룬����λ�ã����Ҵ���
		poi = Hash(key); // ��ù�ϣ��ַ
		while (elem[poi].key != NULLKEY && elem[poi].key != key) { // ��λ�����м�¼�����ҹؼ��ֲ���
			count++; // �����һ̽���ַp
			collision(poi);
		}
		if (elem[poi].key == key) { // ���ҳɹ�
			count++; // �����˱ȽϾ�+1
			cout << "���ҳɹ� " << count << endl; /* ���Դ��� */
			return true;
		}

		return false; // ���Ҳ��ɹ�����poiΪ����λ��(elem[poi].key == NULLKEY)
	}

	void collision(int &key) { // �����ͻ
		key = (key + 1) % hashsize;  // ����̽����ɢ��(Ӧ�Ա�ȡ��)
	}

	bool insertHash(ElemType e) {
		int poi, count = 0; // �����ַ�����Ҵ���������
		if (searchHash(e.key, poi, count) == true) // ����������e����ͬ�ؼ��ֵ�Ԫ��
			return false;
		else {
			elem[poi] = e;
			return true;
		}
	}
	bool insertHash2(ElemType e) {
		int poi, count = 0; // �����ַ�����Ҵ���������
		if (searchHash(e.key, poi, count) == true) // ����������e����ͬ�ؼ��ֵ�Ԫ��
			return false;
		else {
			elem[poi] = e;
			cout << "����ɹ� " << poi << endl; /* ���Դ��� */
			return true;
		}
	}

	void printHash() {
		cout << elem[0].key; // �����ϣ���е����йؼ��֣��ո�ָ�
		for (int i = 1; i < hashsize; i++) {
			cout << " " << elem[i].key;
		}
		cout << endl;
	}
};

int main()
{
	int keyNum; cin >> keyNum;
	HashTable<int, hashElem<int>> *obj = new HashTable<int, hashElem<int>>(keyNum);
	obj->printHash();
	int key; cin >> key;
	obj->insertHash2(hashElem<int>(key));

	return 0;
}
