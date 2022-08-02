#include <iostream>
#include <sstream>
#include "BinTree.h"

#include "../Sequence/Vector.h"

using namespace std;

template<typename T>
Queue<T> *readTreeNodes(string sequence) {
    Queue<T> *treeNodes = new Queue<T>;
    int begin = sequence.find('['), end = sequence.rfind(']');
    sequence = sequence.substr(begin + 1, end - begin - 1);
    stringstream buffer(sequence);
    string token;
    while (getline(buffer, token, ',')) {
        stringstream os(token.substr(token.find_first_not_of(' ')));
        T elem;
        os >> elem;
        treeNodes->enqueue(elem);
    }
    return treeNodes;
}

template<typename T>
BinTree<T> *createTree(Queue<T> &treeNodes) {
    BinTree<T> *binTree = new BinTree<T>; // 创建空树
    Queue<BinNodePosi<T>> Q; // 辅助队列

    BinNodePosi<T> root = binTree->insertAsRoot(treeNodes.dequeue()); // 首元素作为树根
    Q.enqueue(root); // 等待插入孩子节点

    while (!Q.empty()) {
        BinNodePosi<T> x = Q.dequeue();
        if (!treeNodes.empty()) {
            T lc = treeNodes.dequeue();
            if (lc != "null") Q.enqueue(binTree->insertAsLC(x, lc));
        }
        if (!treeNodes.empty()) {
            T rc = treeNodes.dequeue();
            if (rc != "null") Q.enqueue(binTree->insertAsRC(x, rc));
        }
    }
    return binTree;
}

template<typename T>
struct StoreInVector {
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
    /* 初始化树 */
    printf("初始化树：\n");
    printf("[1] 请输入二叉树的层次扩展序列：");
    string sequence;
    getline(cin, sequence);
    Queue<T> treeNodes = *readTreeNodes<T>(sequence);
    BinTree<T> myBinTree = *createTree<T>(treeNodes);
    printf("[2] 二叉树创建完成。");
    cout << '\n' << endl;

    printf("遍历二叉树：\n");
    StoreInVector<T> pre, in, post, level;
    myBinTree.travPre(pre);
    cout << "[1] 先序遍历序列：" << pre.elems << endl;
    myBinTree.travIn(in);
    cout << "[2] 中序遍历序列：" << in.elems << endl;
    myBinTree.travPost(post);
    cout << "[3] 后序遍历序列：" << post.elems << endl;
    myBinTree.travLevel(level);
    cout << "[4] 层次遍历序列：" << level.elems << endl;
}

int main() {
    testBinTree<string>();
    return 0;
    // root = [i, d, l, c, h, k, n, a, null, f, null, j, null, m, p, null, b, e, g, null, null, null, null, o, null]
}