#include <iostream>
#include <string>
#include <vector>
using namespace std;

void getNext(string T, vector<int> &next) {
	int size = T.size();
	T.insert(T.begin(), ' ');
	next.resize(size + 1);

	int i = 1, j = 0;
	next[1] = 0;
	while (i < size) {
		if (j == 0 || T[i] == T[j]) {
			i++; j++;
			next[i] = j;
		}
		else {
			j = next[j];
		}
	}
}

void getNextval(string T, vector<int> &nextval) {
	int size = T.size();
	T.insert(T.begin(), ' ');
	nextval.resize(size + 1);

	int i = 1, j = 0;
	nextval[1] = 0;
	while (i < size) {
		if (j == 0 || T[i] == T[j]) {
			i++; j++;
			nextval[i] = (T[i] != T[j] ? j : nextval[j]);
		}
		else {
			j = nextval[j];
		}
	}
}

int main() {
	string test = "abaabcaba";
	vector<int> next, nextval;
	getNext(test, next);
	getNextval(test, nextval);

	for (size_t i = 1; i < next.size(); i++) {
		cout << next[i] << " ";
	}
	cout << endl;
	for (size_t i = 1; i < nextval.size(); i++) {
		cout << nextval[i] << " ";
	}
	cout << endl;
}
