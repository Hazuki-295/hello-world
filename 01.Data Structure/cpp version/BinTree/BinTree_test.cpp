#include <iostream>
#include <vector>
#include <sstream>
#include "BinTree.h"
#include "../Stack_Queue/Queue.h"

using namespace std;

Queue<string> readTreeNodes(string sequence) {
    Queue<string> treeNodes;
    sequence = sequence.substr(sequence.find('[') + 1, sequence.rfind(']') - 1);
    stringstream buffer(sequence);
    string token;
    while (getline(buffer, token, ',')) {
        treeNodes.enqueue(token.substr(token.find_first_not_of(' ')));
    }
    return treeNodes;
}

BinTree<string> *createTree(Queue<string> &treeNodes) {
    BinTree<string> *binTree = new BinTree<string>; // 创建空树
    Queue<BinNodePosi<string>> Q; // 辅助队列

    BinNodePosi<string> root = binTree->insertAsRoot(treeNodes.dequeue()); // 首元素作为树根
    Q.enqueue(root); // 等待插入孩子节点

    while (!Q.empty()) {
        BinNodePosi<string> x = Q.dequeue();
        if (!treeNodes.empty()) {
            string lc = treeNodes.dequeue();
            if (lc != "null") Q.enqueue(x->insertAsLC(lc));
        }
        if (!treeNodes.empty()) {
            string rc = treeNodes.dequeue();
            if (rc != "null") Q.enqueue(x->insertAsRC(rc));
        }
    }
    return binTree;
}

template<typename T> void testBinTree() {
    BinTree<T> *myBinTree;

    /* 初始化树 */
    printf("初始化树：\n");
    printf("[1] 请输入二叉树的层次扩展序列：");
    string sequence;
    getline(cin, sequence);
    Queue<string> treeNodes = readTreeNodes(sequence);
    myBinTree = createTree(treeNodes);
    printf("[2] 二叉树创建完成。");
    cout << '\n' << endl;

    printf("遍历二叉树：\n");
    printf("[1] 先序遍历序列：");
    // myBinTree->travPre();

    return;
}

int main() {
    testBinTree<string>();
    // root = [i, d, l, c, h, k, n, a, null, f, null, j, null, m, p, null, b, e, g, null, null, null, null, o, null]
    // root = [
    // i,
    // d, l,
    // c, h, k, n,
    // a, null, f, null, j, null, m, p,
    // null, b, e, g, null, null, null, null, o, null,
    // ]
    return 0;
}