typedef int ElemType;
#include <iostream>
using namespace std;


/* 定义双链表结点类型 */
typedef struct DNode {

	ElemType data; //数据域
	struct DNode *prior, *next; //前驱和后继指针

} DNode, *DLinkList;

#define MAXSIZE 50 //静态链表的最大长度

/* 静态链表结构类型的定义 */
typedef struct {
	ElemType data; //存储数据元素
	int next; //下一个元素的数组下标
} SLinkList[MAXSIZE];