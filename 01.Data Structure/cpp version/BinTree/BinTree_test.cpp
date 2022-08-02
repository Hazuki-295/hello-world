#include <iostream>
#include <vector>
#include <sstream>
#include "BinTree.h"
#include "../Sequence/Vector.h"

using namespace std;

Queue<string> readTreeNodes(string sequence) {
    Queue<string> treeNodes;
    int begin = sequence.find('['), end = sequence.rfind(']');
    sequence = sequence.substr(begin + 1, end - begin - 1);
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
            if (lc != "null") Q.enqueue(binTree->insertAsLC(x, lc));
        }
        if (!treeNodes.empty()) {
            string rc = treeNodes.dequeue();
            if (rc != "null") Q.enqueue(binTree->insertAsRC(x, rc));
        }
    }
    return binTree;
}

template<typename T>
struct PrintVector {
    Vector<T> elems; // 元素
    virtual void operator()(T &e) { elems.insert(e); } // 存放元素
};

template<typename T>
ostream &operator<<(ostream &os, Vector<T> const &V) {
    if (V.empty()) return os << "[ ]";
    os << "[ ";
    for (int i = 0; i < V.size() - 1; i++) {
        os << V[i] << ", ";
    }
    os << V[V.size() - 1] << " ]";
    return os;
}

template<typename T> void testBinTree() {
    BinTree<T> myBinTree;

    /* 初始化树 */
    printf("初始化树：\n");
    printf("[1] 请输入二叉树的层次扩展序列：");
    string sequence;
    getline(cin, sequence);
    Queue<string> treeNodes = readTreeNodes(sequence);
    myBinTree = *createTree(treeNodes);
    printf("[2] 二叉树创建完成。");
    cout << '\n' << endl;

    printf("遍历二叉树：\n");
    PrintVector<T> pre, in, post, level;
    myBinTree.travPre(pre);
    printf("[1] 先序遍历序列：");
    cout << pre.elems << endl;
    myBinTree.travIn(in);
    printf("[2] 中序遍历序列：");
    cout << in.elems << endl;
    myBinTree.travPost(post);
    printf("[3] 后序遍历序列：");
    cout << post.elems << endl;
    myBinTree.travLevel(level);
    printf("[4] 层次遍历序列：");
    cout << level.elems << endl;

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