#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;

#define NULLKEY -999

template <typename K, typename V> struct Entry { //词条模板类
	K key; V value; //关键码、数值
	Entry(K k = K(), V v = V()) : key(k), value(v) {}; //默认构造函数
	Entry(Entry<K, V> const &e) : key(e.key), value(e.value) {}; //基于克隆的构造函数
	bool operator< (Entry<K, V> const &e) { return key < e.key; }  //比较器：小于
	bool operator> (Entry<K, V> const &e) { return key > e.key; }  //比较器：大于
	bool operator== (Entry<K, V> const &e) { return key == e.key; } //判等器：等于
	bool operator!= (Entry<K, V> const &e) { return key != e.key; } //判等器：不等于
}; //得益于比较器和判等器，从此往后，不必严格区分词条及其对应的关键码

template<typename KeyType, typename ValueType> struct hashElem {
	// 数据成员
	KeyType key; ValueType val; // 信息只有一个，关键码key本身
	// 构造函数
	hashElem(KeyType key = KeyType(), ValueType val = ValueType()) :key(NULLKEY), val(val) {}
	hashElem(KeyType key, ValueType val = ValueType()) :key(key), val(0) {}
};

template<typename KeyType> struct hashElem {
	// 数据成员
	KeyType key; int val; // 信息只有一个，关键码key本身
	// 构造函数
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

/* 开放定址哈希表 */
template<typename KeyType, typename ElemType> class HashTable // key为关键码
{
private:
	vector<ElemType> elem;
	int hashsize = 15;
public:
	queue<ElemType> print; // 用于处理输出结果

	HashTable(int size) {
		elem.resize(hashsize); // 哈希表长为15，地址为0…14，初始均为-999
		ElemType temp;
		for (int i = 0; i < size; i++) {
			cin >> temp;
			insertHash(temp);
		}
	}

	int Hash(KeyType key) { return key % 11; } // 哈希函数为H(key)=key mod 11

	bool searchHash(KeyType key, int &poi, int &count) { // 关键码，插入位置，查找次数
		poi = Hash(key); // 求得哈希地址
		while (elem[poi].key != NULLKEY && elem[poi].key != key) { // 该位置填有记录，并且关键字不等
			count++; // 求得下一探查地址p
			collision(poi);
		}
		if (elem[poi].key == key) { // 查找成功
			count++; // 进行了比较就+1
			cout << "查找成功 " << count << endl; /* 测试代码 */
			return true;
		}

		return false; // 查找不成功，则poi为插入位置(elem[poi].key == NULLKEY)
	}

	void collision(int &key) { // 处理冲突
		key = (key + 1) % hashsize;  // 线性探测再散列(应对表长取余)
	}

	bool insertHash(ElemType e) {
		int poi, count = 0; // 插入地址，查找次数计数器
		if (searchHash(e.key, poi, count) == true) // 表中已有与e有相同关键字的元素
			return false;
		else {
			elem[poi] = e;
			return true;
		}
	}
	bool insertHash2(ElemType e) {
		int poi, count = 0; // 插入地址，查找次数计数器
		if (searchHash(e.key, poi, count) == true) // 表中已有与e有相同关键字的元素
			return false;
		else {
			elem[poi] = e;
			cout << "插入成功 " << poi << endl; /* 测试代码 */
			return true;
		}
	}

	void printHash() {
		cout << elem[0].key; // 输出哈希表中的所有关键字，空格分隔
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
