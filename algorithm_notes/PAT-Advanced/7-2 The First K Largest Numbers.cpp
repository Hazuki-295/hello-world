#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

/* 7-2 The First K Largest Numbers */

int main() {
    int N, K;
    cin >> N >> K;

    priority_queue<int, vector<int>, greater<int>> num;  // 优先级队列，存放最大的5个元素

    int temp;
    for (int i = 0; i < N; i++) {  // 处理 N 个数

        scanf("%d", &temp);

        if (num.size() <= 5) {  // 只存放最大的5个元素
            num.push(temp);
        } else {
            if (temp > num.top()) {  // 新输入的数，比队列中最小的要大
                num.pop();           // 最小元素出列
                num.push(temp);
            }
        }
    }

    /* 可优化代码段 */
    vector<int> ans;
    while (num.size() != 0) {
        ans.push_back(num.top());  // 从小到大
        num.pop();
    }
    sort(ans.begin(), ans.end(), greater<int>());  // 从大到小

    if (K > ans.size()) {  // 题目挖的小坑
        K = ans.size();
    }

    for (int i = 0; i < K - 1; i++) {
        printf("%d ", ans[i]);
    }
    printf("%d\n", ans[K - 1]);

    return 0;
}