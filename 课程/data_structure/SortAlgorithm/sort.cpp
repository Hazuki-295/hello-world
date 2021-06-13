#include <iostream>
#include <vector>
using namespace std;

/* 插入排序 */
void insertSort(vector<int> &A) { // 直接插入排序
	int length = A.size(), j;
	/* 测试 */A.insert(A.begin(), 0);   // 插入哨兵
	for (int i = 2; i <= length; i++) { // 依次将A[2]~A[n]插入到前面已排序的序列
		if (A[i] < A[i - 1]) { // 若发现逆序，则需要插入。否则跳过。
			A[0] = A[i];       // 复制为哨兵，暂存
			for (j = i - 1; A[0] < A[j]; j--) { // 查找插入位置，仍然逆序时继续(若遇哨兵，则相等退出)
				A[j + 1] = A[j]; // 同时后移元素，腾出位置
			}
			A[j + 1] = A[0]; // 插入到正确位置(A[0]<A[j]不满足，为不大于A[0]的最大元素，插入到后面)
		}
	}
	/* 测试 */A.erase(A.begin()); // 完成后移除哨兵
}

void binaryInsertSort(vector<int> &A) { // 折半插入排序
	int length = A.size(), low, high, mid;
	/* 测试 */A.insert(A.begin(), 0);   // 插入哨兵
	for (int i = 2; i <= length; i++) { // 依次将A[2]~A[n]插入到前面已排序的序列
		A[0] = A[i]; // 将A[i]暂存到A[0]
		low = 1; high = i - 1;
		while (low <= high) {  // 折半查找找到A[i]的插入位置
			mid = (low + high) / 2;
			if (A[0] < A[mid]) // 插入点在左半区
				high = mid - 1;
			else               // 插入点在右半区
				low = mid + 1;
		}
		for (int j = i - 1; j >= high + 1; j--) { // 插入位置及之后的元素后移
			A[j + 1] = A[j];
		}
		A[high + 1] = A[0]; // 插入
	}
	/* 测试 */A.erase(A.begin()); // 完成后移除哨兵
}

void shellSort(vector<int> &A) { // 希尔排序
	int length = A.size(), dk, j;
	/* 测试 */A.insert(A.begin(), 0);   // 插入哨兵
	for (dk = length / 2; dk >= 1; dk = dk / 2) { // 步长变化
		for (int i = dk + 1; i <= length; i++) {
			if (A[i] < A[i - dk]) { // 若发现逆序，则需要插入。否则跳过。
				A[0] = A[i];        // 复制为哨兵，暂存
				for (j = i - dk; j > 0 && A[0] < A[j]; j -= dk) { // 查找插入位置，仍然逆序时继续(j<=0时，插入位置已找到)
					A[j + dk] = A[j]; // 同时后移元素，腾出位置
				}
				A[j + dk] = A[0]; // 插入到正确位置
			}
		}
	}
	/* 测试 */A.erase(A.begin()); // 完成后移除哨兵
}

/* 交换排序 */
void bubblesort(vector<int> &A) { // 起泡排序算法
	int n = A.size();
	bool sorted = false; // 整体排序标志，首先假定尚未排序
	while (!sorted) {    // 在尚未确认已全局排序之前，逐趟进行扫描交换
		sorted = true;   // 假定已经排序
		for (int i = 1; i < n; i++) { // 自左向右逐对检查当前范围A[0, n)内的各相邻元素
			if (A[i - 1] > A[i]) {    // 一旦A[i - 1]与A[i]逆序，则
				swap(A[i - 1], A[i]); // 交换之，并
				sorted = false;       // 因整体排序不能保证，需要清除排序标志
			}
		}
		n--; // 至此末元素必然就位，故可以缩短待排序序列的有效长度
	}
} // 借助布尔型标志位sorted，可及时提前退出，而不致总是蛮力地做n - 1趟扫描交换

void bubblesort2(vector<int> &A) { // 起泡排序算法(复杂版)
	int n = A.size();
	bool changed = true;  // 本趟冒泡是否发生交换(发生则表示尚未整体有序)
	for (int i = 0; i < n - 1 && changed; i++) { // 最多n-1趟扫描交换，每次一个元素起泡
		changed = false;  // 假定没有发生交换
		for (int j = n - 1; j > i; j--) { // 自右向左逐对检查当前范围A[i, n-1]内的各相邻元素
			if (A[j - 1] > A[j]) {        // 一旦A[i - 1]与A[i]逆序，则
				swap(A[j - 1], A[j]);     // 交换之，并
				changed = true;           // 因发生了交换，整体排序不能保证
			}
		}
	}
}

class QuickSort {
public:
	vector<int> sortArray(vector<int> &nums) {
		quickSort(nums, 0, (int)nums.size() - 1);
		return nums;
	}

	void quickSort(vector<int> &nums, int low, int high) { // 快速排序
		if (low < high) {
			int poi = partition(nums, low, high); // 划分
			quickSort(nums, low, poi - 1);        // 递归对两个子表进行排序
			quickSort(nums, poi + 1, high);
		}
	}

	int partition(vector<int> &nums, int low, int high) {
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

/* 选择排序 */
void selectSort(vector<int> &A) { // 简单选择排序
	int n = A.size(), min;
	for (int i = 0; i < n - 1; i++) { // 共进行n-1趟
		min = i; // 记录最小元素位置
		for (int j = i + 1; j < n; j++) { // 在A[i,n-1]中选择最小的元素
			if (A[j] < A[min]) {          // 更新最小元素位置
				min = j;
			}
		}
		if (min != i) {         // 若最小的元素确实在A[i]的右边，则
			swap(A[i], A[min]); // 交换之
		}
	}
}

class HeapSort {
public:
	vector<int> sortArray(vector<int> &nums) {
		heapSort(nums);
		return nums;
	}

	/* 建立大根堆 */
	void buildMaxHeap(vector<int> &nums, int length) {
		for (int i = length / 2; i >= 1; i--) { // 从最后一个非终端节点开始调整
			heapAdjust(nums, i, length);
		}
	}
	void heapAdjust(vector<int> &nums, int k, int length) { // 自堆顶k至叶子调整
		nums[0] = nums[k]; // A[0]暂存子树的根结点(待调整元素)
		for (int i = 2 * k; i <= length; i *= 2) {     // 沿key较大的孩子结点向下筛选
			if (i < length && nums[i] < nums[i + 1]) { // 选择key较大的孩子结点作为下标(注意防止下标越界)
				i = i + 1;
			}
			if (nums[0] >= nums[i]) { // 根结点(待调整元素)比左右孩子都大，无需调整
				break;                // 则调整结束
			}
			else {
				nums[k] = nums[i]; // 将孩子结点A[i]调整到双亲结点上
				k = i;             // 修改k值为其孩子位置，继续向下筛选
			}
		}
		nums[k] = nums[0]; // 被筛选结点的值放入最终位置
	}

	void heapSort(vector<int> &nums) {
		int length = nums.size();
		nums.insert(nums.begin(), 0); // 插入哨兵(使得完全二叉树满足计算式)

		buildMaxHeap(nums, length);        // 无序序列建成大顶堆
		for (int i = length; i > 1; i--) { // (调整建新堆将调用n-1次)
			swap(nums[i], nums[1]);        // 输出堆顶元素(和堆底元素交换)
			heapAdjust(nums, 1, i - 1);    // 调整，把剩余的i-1个元素整理成堆
		}

		nums.erase(nums.begin()); // 完成后移除哨兵
	}
};

/* 归并排序 */
class MergeSort {
private:
	vector<int> B; // 辅助数组B
public:
	vector<int> sortArray(vector<int> &nums) {
		B.resize(nums.size());
		mergeSort(nums, 0, nums.size() - 1);
		return nums;
	}

	// 表A的两段 A[low...mid] 和 A[mid+1...high] 各自有序，将它们合并成一个有序表。
	void merge(vector<int> &A, int low, int mid, int high) {
		int i, j, k;

		for (int k = low; k <= high; k++) { // 将A中所有元素复制到B中
			B[k] = A[k];
		}
		for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++) {
			if (B[i] <= B[j]) { // 比较B的左右两段中的元素
				A[k] = B[i++];  // 将较小值复制到A中
			}
			else {
				A[k] = B[j++];
			}
		}
		while (i <= mid)  A[k++] = B[i++]; // 若第一个表未检测完，复制
		while (j <= high) A[k++] = B[j++]; // 若第二个表未检测完，复制
	}

	void mergeSort(vector<int> &A, int low, int high) {
		if (low < high) {
			int mid = (low + high) / 2;   // 从中间划分两个子序列
			mergeSort(A, low, mid);       // 对左侧子序列递归
			mergeSort(A, mid + 1, high);  // 对右侧子序列递归
			merge(A, low, mid, high);     // 归并
		}
	}
};

int main()
{
	int size, temp; vector<int> num; cin >> size;
	for (int i = 0; i < size; i++) {
		cin >> temp;
		num.push_back(temp);
	}
	vector<vector<int>> nums(9, num);
	QuickSort *obj = new QuickSort;
	HeapSort *obj2 = new HeapSort;
	MergeSort *obj3 = new MergeSort;

	/* 插入排序 */
	insertSort(nums[0]);       // 插入排序
	binaryInsertSort(nums[1]); // 折半插入排序
	shellSort(nums[2]);        // 希尔排序
	/* 交换排序 */
	bubblesort(nums[3]);       // 冒泡排序
	bubblesort2(nums[4]);      // 冒泡排序2
	obj->quickSort(nums[5], 0, (int)nums[5].size() - 1); // 快速排序
	/* 选择排序 */
	selectSort(nums[6]);       // 简单选择排序
	obj2->heapSort(nums[7]);   // 堆排序
	/* 归并排序 */
	obj3->sortArray(nums[8]);  // 归并排序

	cout << endl;
	for (int i = 0; i < nums.size(); i++) {
		for (int j = 0; j < nums[i].size() - 1; j++) {
			cout << nums[i][j] << " ";
		}
		cout << nums[i].back() << endl;
	}

	return 0;
}