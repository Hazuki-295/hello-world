#include <iostream>
#include <vector>

using namespace std;

/* 快速排序 */
class Solution {
public:
    vector<int> sortArray(vector<int> &nums) {
        srand((unsigned) time(NULL));
        quickSort(nums, 0, (int) nums.size() - 1);
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

/* 堆排序 */
class Solution2 {
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
            } else {
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