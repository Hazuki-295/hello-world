typedef int ElemType;
#include <iostream>
using namespace std;


/* ����˫���������� */
typedef struct DNode {

	ElemType data; //������
	struct DNode *prior, *next; //ǰ���ͺ��ָ��

} DNode, *DLinkList;

#define MAXSIZE 50 //��̬�������󳤶�

/* ��̬����ṹ���͵Ķ��� */
typedef struct {
	ElemType data; //�洢����Ԫ��
	int next; //��һ��Ԫ�ص������±�
} SLinkList[MAXSIZE];