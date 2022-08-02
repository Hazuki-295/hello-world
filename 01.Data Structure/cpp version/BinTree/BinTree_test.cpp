#include <iostream>
#include <sstream>
#include "BinTree.h"

#include "../Sequence/Vector.h"

using namespace std;

Queue<string> *readTreeNodes(string const &sequence) {
    Queue<string> *treeNodes = new Queue<string>;
    int begin = sequence.find('['), end = sequence.rfind(']');
    stringstream buffer(sequence.substr(begin + 1, end - begin - 1));
    string token;
    while (getline(buffer, token, ',')) {
        treeNodes->enqueue(token.substr(token.find_first_not_of(' ')));
    }
    return treeNodes;
}

template<typename T>
BinTree<T> *createTree(Queue<string> &treeNodes) {
    BinTree<T> *binTree = new BinTree<T>; // 创建空树
    Queue<BinNodePosi<T>> Q; // 辅助队列

    stringstream buffer(treeNodes.dequeue()); // 首元素作为树根
    T elem;
    buffer >> elem;
    Q.enqueue(binTree->insertAsRoot(elem)); // 等待插入孩子节点

    while (!Q.empty()) {
        BinNodePosi<T> x = Q.dequeue();
        if (!treeNodes.empty()) {
            string token = treeNodes.dequeue(); // 左孩子
            if (token != "null") {
                buffer = stringstream(token);
                buffer >> elem;
                Q.enqueue(binTree->insertAsLC(x, elem));
            }
        }
        if (!treeNodes.empty()) {
            string token = treeNodes.dequeue(); // 右孩子
            if (token != "null") {
                buffer = stringstream(token);
                buffer >> elem;
                Q.enqueue(binTree->insertAsRC(x, elem));
            }
        }
    }
    return binTree;
}

template<typename T>
struct StoreInVector {
    Vector<T> elems; // 元素
    void operator()(T &e) { elems.insert(e); } // 存放元素
};

template<typename T> void testBinTree() {
    /* 初始化树 */
    printf("初始化树：\n");
    printf("[1] 请输入二叉树的层次扩展序列：");
    string sequence;
    getline(cin, sequence);
    Queue<string> treeNodes = *readTreeNodes(sequence);
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
    testBinTree<char>();
    return 0;
    // root = [i, d, l, c, h, k, n, a, null, f, null, j, null, m, p, null, b, e, g, null, null, null, null, o, null]
}