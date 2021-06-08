#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
private:
	unordered_map<int, bool> vis; // ���ʱ��
	vector<int> output; // ��ŵõ���һ������
public:
	/* ���ݷ���һ��ͨ��̽�����п��ܵĺ�ѡ�����ҳ����еĽ���㷨�� */
	void backtrack(vector<vector<int>> &res, vector<int> &nums) {
		if (output.size() == nums.size()) { // ��������������
			res.emplace_back(output); // �õ�һ�����еĽ��
			return;
		}

		// �����ѡ�ⱻȷ�ϲ���һ���⣨�������ٲ������һ���⣩�������㷨��ͨ������һ������һЩ�仯�����ý⣬�����ݲ����ٴγ���
		for (int i = 0; i < nums.size(); i++) { // ��һö�٣�ѡ��һ����
		
			if (vis[nums[i]]) continue; // ʹ�ù���Ԫ�أ�ֱ������

			output.push_back(nums[i]); vis[nums[i]] = true; // ʹ�ø�Ԫ��
			backtrack(res, nums); // ���µݹ�����һ����
			output.pop_back(); vis[nums[i]] = false; // ���ݣ���������(״̬����)
			// ������ȱ����ڻص���һ����ʱ��"״̬����"���������ڻص���֮ǰ��״̬���ſ��Կ�ʼ��һ��ѡ��ĳ��ԡ�
		}
	}

	vector<vector<int>> permute(vector<int> &nums) {
		vector<vector<int>> res; // ���ȫ���еĽ��
		vis.clear();             // ��շ��ʱ��
		backtrack(res, nums);    // ���ݷ��õ�ȫ����(���ֵ���˳��)
		return res;
	}
};

int main()
{
	vector<int> nums;
	for (int i = 0; i <= 9; i++) { // ��ʼΪ{0,1,2,3,4 | 5,6,7,8,9}
		nums.push_back(i);
	}
	Solution *obj = new Solution;
	vector<vector<int>> result(obj->permute(nums));
	return 0;
}