#include <iostream>
using namespace std;

/* 图的邻接矩阵存储结构 */
#define MaxVertexNum 100 // 顶点数目的最大值
typedef char VertexType; // 顶点的数据类型
typedef int EdgeType;    // 带权图中"边上权值"的数据类型
typedef struct
{
	VertexType Vex[MaxVertexNum];              // 顶点表
	EdgeType Edge[MaxVertexNum][MaxVertexNum]; // 邻接矩阵，边表
	int vexnum, arcnum; // 图的当前顶点数和弧数
} MGraph;


/* 图的邻接表存储结构 */
#define MaxVertexNum 100  // 图中顶点数目的最大值

typedef struct ArcNode {  // 边(表)结点
	int adjvex;           // 该弧所指向的顶点的位置(下标)
	struct ArcNode *next; // 指向下一条邻接弧的指针
	//InfoType info;      // 边权值
} ArcNode;

typedef struct VNode {    // 顶点(表)结点
	VertexType data;      // 顶点信息
	ArcNode *first;       // 指向第一条依附该顶点的弧的指针
} VNode, AdjList[MaxVertexNum];

typedef struct {
	AdjList vertices;   // 邻接表
	int vexnum, arcnum; // 图的顶点数和弧数
} ALGraph; // ALGraph是以邻接表(AL)存储的图类型

bool visited[MaxVertexNum]; // 访问标记数组