#include <iostream>	
#include <vector>
using namespace std;

class Solution {
public:
	bool isUgly(int n) {
		if (n <= 0) return false;
		vector<int> factors = { 2,3,5 }; // 只含有质因子2,3,5
		for (auto factor : factors) {
			while (n % factor == 0) // 除尽所含的2,3,5因子
				n /= factor;
		}
		return n == 1; // 若能结果为1，即为丑数
	}
};