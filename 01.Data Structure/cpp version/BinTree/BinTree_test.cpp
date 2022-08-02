#include <iostream>
#include <vector>
#include "BinTree.h"

using namespace std;

template<typename T> void testBinTree() {
    BinTree<T> myBinTree;

    /* 初始化树 */
    printf("初始化树：\n");
    printf("[1] 请输入二叉树的先序扩展序列：");
    string treeNodes;
}

vector<string> readTreeNodes() {
    vector<string> treeNodes;


    return treeNodes;
}

int main() {
    testBinTree<string>();
    // root = [i, d, l, c, h, k, n, a, null, f, null, j, null, m, p, null, b, e, g, null, null, null, null, o, null, null, null, null, null, null, null, null, null]
    // root = [
    // i,
    // d, l,
    // c, h, k, n,
    // a, null, f, null, j, null, m, p,
    // null, b, e, g, null, null, null, null, o, null,
    // null, null, null, null, null, null, null, null
    // ]
    return 0;
}