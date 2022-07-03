#include <iostream>
#include "Vector.h"

using namespace std;

template<typename T>
void permute(Vector<T> &V) { // 随机置乱向量，使各元素等概率出现于各位置
    for (int i = V.size(); i > 0; i--) {    // 自后向前
        std::swap(V[i - 1], V[rand() % i]); // 将V[i - 1]与V[0, i)中某一元素随机交换
    }
}

int main() {
    int array[5] = {1, 2, 3, 4, 5};
    Vector<int> vector(array, 5);

    permute(vector);

    return 0;
}

