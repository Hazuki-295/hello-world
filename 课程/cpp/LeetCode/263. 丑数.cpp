#include <iostream>	
#include <vector>
using namespace std;

class Solution {
public:
	bool isUgly(int n) {
		if (n <= 0) return false;
		vector<int> factors = { 2,3,5 }; // ֻ����������2,3,5
		for (auto factor : factors) {
			while (n % factor == 0) // ����������2,3,5����
				n /= factor;
		}
		return n == 1; // ���ܽ��Ϊ1����Ϊ����
	}
};