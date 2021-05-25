#include <iostream>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

#define MaxVertexNum 100 // 顶点数目的最大值

/* 图Graph模板类（邻接矩阵） */
template <typename VertexType, typename EdgeType> class Graph { // VertexType：顶点的数据类型，EdgeType：带权图中"边上权值"的数据类型

private:
	/* 图的邻接矩阵存储结构 */
	VertexType Vex[MaxVertexNum];              // 顶点表
	EdgeType Edge[MaxVertexNum][MaxVertexNum]; // 邻接矩阵，边表
	int vexnum, arcnum;                        // 图的当前顶点数和弧数

	bool visited[MaxVertexNum]; // 访问标记数组

	queue<int> Q; // 辅助队列Q

	/* 辅助数组，对当前V－U集中的每个顶点，记录和顶点集U中顶点相连接的代价最小的边 */
	struct Closedge { VertexType adjvex; EdgeType lowcost; } closedge[MaxVertexNum];

public:
	stringstream ss; // 用于处理结果

	/* (带权)无向图构造 */
	Graph(int _vexnum, int _arcnum) :vexnum(_vexnum), arcnum(_arcnum)
	{
		/* 初始化顶点集、边集 */
		for (int i = 0; i < vexnum; i++) Vex[i] = i + 1; // 顶点信息从1计起
		for (int i = 0; i < vexnum; i++)
			for (int j = 0; j < vexnum; j++)
				Edge[i][j] = 0/*INT_MAX*/; // 无权图(带权图)

		int x, y, index_x, index_y;    // 邻接的两个顶点、边权值
		for (int i = 0; i < arcnum; i++) // 输入每条边
		{
			cin >> x >> y;
			index_x = LocateVex(x); index_y = LocateVex(y);
			if (Edge[index_x][index_y] == 1)
			{
				i--;
				continue;
			}
			Edge[index_x][index_y] = 1;
			Edge[index_y][index_x] = 1;
		}
	}

	/* 按值查找。若图G中存在值为val的顶点，则返回该顶点在图中的位置，否则返回-1 */
	int LocateVex(VertexType val)
	{
		for (int i = 0; i < vexnum; i++) // 顶点集中查找值为val的顶点
			if (Vex[i] == val)
				return i;
		return -1; // 不存在则返回-1
	}

	/* 求图G中位置为x的顶点的第一个邻接点，若有则返回顶点号。若其没有邻接点或在图中不存在，则返回-1 */
	int FirstNeighbor(int x)
	{
		if (x < 0 || x >= vexnum) return -1;  // 图中不存在位置为x的顶点，返回-1

		for (int i = 0; i < vexnum; i++)      // 在边集中查找其邻接点
			if (Edge[x][i] != 0/*INT_MAX*/)   // 若存在第一个邻接点，则返回顶点号
				return i;

		return -1; // 若位置为x的顶点没有邻接点，返回-1
	}

	/* 求图G中位置为x的顶点(相对于y处的)下一个邻接点的位置。若y是x的最后一个邻接点，则返回-1 */
	int NextNeighbor(int x, int y)
	{
		for (int i = y + 1; i < vexnum; i++) // 在边集中查找除y外顶点x的下一个邻接点
			if (Edge[x][i] != 0/*INT_MAX*/)  // 若存在下一个邻接点，则返回顶点号
				return i;

		return -1; // 若y是x的最后一个邻接点，则返回-1
	}

	/* 访问图中位置为x的顶点 */
	void visit(int x) { ss << Vex[x] << " "; }

	/* 深度优先遍历，从第一个顶点出发 */
	void DFSTraverse()
	{
		for (int i = 0; i < vexnum; i++) // 初始化访问标记数组
			visited[i] = false;
		for (int i = 0; i < vexnum; i++) // 本代码中是从v=0(第一个顶点)开始遍历
			if (!visited[i]) DFS(i);
	}
	/* 深度优先遍历，从给定顶点v出发 */
	void DFSTraverse(VertexType v)
	{
		for (int i = 0; i < vexnum; i++) // 初始化访问标记数组
			visited[i] = false;

		int index = LocateVex(v);        // 找到起始顶点的位置
		DFS(index);                      // 首先深度优先遍历该顶点(所在的连通分量)

		for (int i = 0; i < vexnum; i++) // 遍历其他连通分量
			if (!visited[i]) DFS(i);
	}
	/* 从位置为v的顶点出发，递归地深度优先遍历图G */
	void DFS(int v)
	{
		visit(v); visited[v] = true; // 访问顶点v
		for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w)) // w为v的尚未访问的邻接点
			if (!visited[w]) DFS(w); // 递归地遍历其邻接点(深度优先)
	}

	/* 广度优先遍历，从第一个顶点出发 */
	void BFSTraverse()
	{
		for (int i = 0; i < vexnum; i++)  // 初始化访问标记数组
			visited[i] = false;

		Q = queue<int>();                 // 初始化辅助队列Q

		for (int i = 0; i < vexnum; i++)  // 从0号顶点开始遍历
			if (!visited[i]) BFS(i);      // 对每个"连通分量"调用一次BFS
	}
	/* 广度优先遍历，从给定顶点v出发 */
	void BFSTraverse(VertexType v)
	{
		for (int i = 0; i < vexnum; i++)  // 初始化访问标记数组
			visited[i] = false;

		Q = queue<int>();                 // 初始化辅助队列Q

		int index = LocateVex(v);         // 找到起始顶点的位置
		BFS(index);                       // 首先广度优先遍历该顶点(所在的连通分量)

		for (int i = 0; i < vexnum; i++)  // 遍历其他连通分量
			if (!visited[i]) BFS(i);
	}
	/* 从位置为v的顶点出发，非递归地广度优先遍历图G */
	void BFS(int v)
	{
		visit(v); visited[v] = true; // 访问顶点v
		Q.push(v);                   // 顶点v入队列Q(以检测其所有邻接点)

		/* 开始迭代访问与v有路径相通且路径长度为1,2,3...的顶点 */
		while (!Q.empty())
		{
			v = Q.front(); Q.pop(); // 顶点v出队列
			for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w)) // 检测v所有邻接点
			{
				if (!visited[w]) // w为v的尚未访问的邻接点
				{
					visit(w); visited[w] = true; // 访问顶点w
					Q.push(w); // 顶点w入队列(其邻接点为下一批被访问的顶点)
				}
			}
		}
	}

	/* closedge[k].lowcost = min{closedge[vi].lowcost | closedge[vi].lowcost>0, vi属于V-U} */
	int minimum()
	{

		int index = -1, min;
		/* 找到第一个连通的点 */
		for (int i = 0; i < vexnum; i++)
		{
			if (closedge[i].lowcost > 0)
			{
				index = i;
				min = closedge[i].lowcost;
				break;
			}
		}
		if (index == -1)
			return -1;

		for (int i = index + 1; i < vexnum; i++)
		{
			if (closedge[i].lowcost > 0)
			{
				if (closedge[i].lowcost < min)
				{
					index = i;
					min = closedge[i].lowcost;
				}
			}
		}

		return index;
	}

	void MiniSpanTree_PRIM(int u)
	{
		// 用普里姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边。
		// 记录从顶点集U到V-U的代价最小的边的辅助数组定义：
		// struct { VertexType adjvex; EdgeType lowcost; } closedge[MaxVertexNum];
		// closedge[j].lowcost表示在集合U中顶点与第j个顶点对应最小权值

		int k = LocateVex(u); int sum = 0;
		for (int j = 0; j < vexnum; j++) // 辅助数组的初始化
		{
			if (j != k)
			{
				closedge[j] = { u ,Edge[k][j] }; // {adjvex, lowcost}
			}
		}
		closedge[k].lowcost = 0; // 初始，U = {u}

		for (int i = 1; i < vexnum; i++) // 选择其余vexnum-1个顶点，因此i从1开始循环
		{
			k = minimum(); // 求出最小生成树T的下一个结点：第k顶点
			if (k == -1) break;
			/* 此时closedge[k].lowcost = min{closedge[vi].lowcost | closedge[vi].lowcost>0, vi属于V-U} */
			cout << closedge[k].adjvex + 1 << ' ' << Vex[k] + 1 << ' ' << closedge[k].lowcost << endl; // 输出生成树的边
			sum += closedge[k].lowcost;

			closedge[k].lowcost = 0; // 第k顶点并入U集
			for (int j = 0; j < vexnum; j++)
			{
				if (Edge[k][j] <= closedge[j].lowcost) // 新顶点并入U后重新选择最小边
				{
					closedge[j] = { Vex[k] ,Edge[k][j] };
				}

			}
		}
		cout << sum << endl;
	}
};

int main()
{
	int n, m;
	cin >> n >> m;

	Graph<int, int> G(n, m); // 构造图

	int StartVex; cin >> StartVex;
	if (G.LocateVex(StartVex) == -1)
		cout << "起始顶点不存在" << endl;
	else
		// G.MiniSpanTree_PRIM(StartVex - 1);
	{
		string result;

		G.BFSTraverse(StartVex);
		getline(G.ss, result); result.pop_back();
		cout << result << endl;

		G.ss.clear(); G.ss.str(string());

		G.DFSTraverse(StartVex);
		getline(G.ss, result); result.pop_back();
		cout << result << endl;
	}


}
