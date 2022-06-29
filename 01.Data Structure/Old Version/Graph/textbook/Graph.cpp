#include <iostream>
using namespace std;

/* ͼ���ڽӾ���洢�ṹ */
#define MaxVertexNum 100 // ������Ŀ�����ֵ
typedef char VertexType; // �������������
typedef int EdgeType;    // ��Ȩͼ��"����Ȩֵ"����������
typedef struct
{
	VertexType Vex[MaxVertexNum];              // �����
	EdgeType Edge[MaxVertexNum][MaxVertexNum]; // �ڽӾ��󣬱߱�
	int vexnum, arcnum; // ͼ�ĵ�ǰ�������ͻ���
} MGraph;


/* ͼ���ڽӱ�洢�ṹ */
#define MaxVertexNum 100  // ͼ�ж�����Ŀ�����ֵ

typedef struct ArcNode {  // ��(��)���
	int adjvex;           // �û���ָ��Ķ����λ��(�±�)
	struct ArcNode *next; // ָ����һ���ڽӻ���ָ��
	//InfoType info;      // ��Ȩֵ
} ArcNode;

typedef struct VNode {    // ����(��)���
	VertexType data;      // ������Ϣ
	ArcNode *first;       // ָ���һ�������ö���Ļ���ָ��
} VNode, AdjList[MaxVertexNum];

typedef struct {
	AdjList vertices;   // �ڽӱ�
	int vexnum, arcnum; // ͼ�Ķ������ͻ���
} ALGraph; // ALGraph�����ڽӱ�(AL)�洢��ͼ����

bool visited[MaxVertexNum]; // ���ʱ������