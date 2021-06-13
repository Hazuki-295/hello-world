#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	vector<int> sortArray(vector<int> &nums) {
		srand((unsigned)time(NULL));
		quickSort(nums, 0, (int)nums.size() - 1);
		return nums;
	}

	void quickSort(vector<int> &nums, int low, int high) {
		if (low < high) {
			int poi = partition(nums, low, high); // 划分
			quickSort(nums, low, poi - 1);        // 递归对两个子表进行排序
			quickSort(nums, poi + 1, high);
		}
	}

	int partition(vector<int> &nums, int low, int high) {
		int i = rand() % (high - low + 1) + low; // 随机选一个作为我们的主元
		swap(nums[low], nums[i]);

		int pivot = nums[low]; // 将当前表中的第一个元素设为枢轴，对表进行划分
		while (low < high) {   // 从两端交替地向中间扫描，low=high时一趟排序结束
			while (low < high && nums[high] >= pivot) // 右端找到第一个小于枢轴的元素
				high--;
			nums[low] = nums[high]; // 将比枢轴小的元素移动到左端

			while (low < high && nums[low] <= pivot) // 左端找到第一个大于枢轴的元素
				low++;
			nums[high] = nums[low]; // 将比枢轴大的元素移动到右端
		}
		nums[low] = pivot; // 枢轴元素存放到最终位置

		return low; // 返回划分点
	}
};
