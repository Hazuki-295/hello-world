#include <iostream>
#include <string>
#include <sstream>
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

public:
	stringstream ss; // 用于处理结果

	Graph(int Vexnum, int Edgenum) :vexnum(Vexnum), arcnum(Edgenum)
	{
		/* 初始化 */
		for (int i = 0; i < vexnum; i++) Vex[i] = i + 1; // 顶点信息从1计起

		int x, y; // 邻接的两个顶点
		for (int i = 0; i < arcnum; i++) // 输入每条边
		{
			cin >> x >> y;
			if (Edge[x - 1][y - 1] != 0)
			{
				i--; 
				continue;
			}
			else
			{
				Edge[x - 1][y - 1] = 1;
				Edge[y - 1][x - 1] = 1;
			}
		}
	}

	/* 求图G中顶点x的第一个邻接点，若有则返回顶点号。若x没有邻接点或图中不存在x，则返回-1 */
	int FirstNeighbor(int x)
	{
		if (x >= vexnum) return -1; // 图中不存在x，返回-1

		for (int i = 0; i < vexnum; i++)
			if (Edge[x][i] != 0)    // 若存在第一个邻接点，则返回顶点号
				return i;

		return -1; // 若x没有邻接点，返回-1
	}

	/* 假设图G中顶点y是顶点x的一个邻接点，则返回除y外顶点x的下一个邻接点的顶点号。若y是x的最后一个邻接点，则返回-1 */
	int NextNeighbor(int x, int y)
	{
		if (y == vexnum - 1) return -1; // 越界，y+1将会等于vexnum，则循环不会执行
		for (int i = y + 1; i < vexnum; i++)
			if (Edge[x][i] != 0) // 除y外顶点x的下一个邻接点
				return i;

		return -1; // 若y是x的最后一个邻接点，则返回-1
	}

	/* 访问图中的顶点v */
	void visit(int v) { ss << Vex[v] << " "; }

	/* 对图G进行深度优先遍历 */
	void DFSTraverse()
	{
		for (int v = 0; v < vexnum; v++) // 初始化访问标记数组
			visited[v] = false;
		for (int v = 0; v < vexnum; v++) // 本代码中是从v=0开始遍历
			if (!visited[v]) DFS(v);
	}
	void DFSTraverse(int x)
	{
		for (int v = 0; v < vexnum; v++) // 初始化访问标记数组
			visited[v] = false;
		for (int v = x; v < vexnum; v++) // 本代码中是从v=x开始遍历
			if (!visited[v]) DFS(v);
	}
	void DFS(int v) // 从顶点v出发，深度优先遍历图G
	{
		visit(v); visited[v] = true; // 访问顶点v
		for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w))
			if (!visited[w]) DFS(w); //w为v的尚未访问的邻接顶点
	}

	/* 对图G进行广度优先遍历 */
	void BFSTraverse()
	{
		for (int i = 0; i < vexnum; i++)  // 初始化访问标记数组
			visited[i] = false;

		Q = queue<int>();                 // 初始化辅助队列Q

		for (int i = 0; i < vexnum; i++)  // 从0号顶点开始遍历
			if (!visited[i]) BFS(i);      // 对每个连通分量调用一次BFS
	}
	void BFSTraverse(int x)
	{
		for (int i = 0; i < vexnum; i++)  // 初始化访问标记数组
			visited[i] = false;

		Q = queue<int>();                 // 初始化辅助队列Q

		for (int i = x; i < vexnum; i++)  // 从x号顶点开始遍历
			if (!visited[i]) BFS(i);      // 对每个连通分量调用一次BFS
	}
	void BFS(int v) // 从顶点v出发，广度优先遍历图G
	{
		visit(v); visited[v] = true; // 访问顶点v
		Q.push(v);                   // 顶点v入队列Q

		while (!Q.empty())
		{
			v = Q.front(); Q.pop(); // 顶点v出队列
			for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w)) // 检测v所有邻接点
			{
				if (!visited[w]) // w为v的尚未访问的邻接点
				{
					visit(w); visited[w] = true;
					Q.push(w); // 顶点w入队列(下一批被访问的顶点)
				}
			}
		}
	}
};

int main()
{
	int n, m;
	cin >> n >> m;

	Graph<int, int> G(n, m); // 构造图

	int StartVex;
	cin >> StartVex;
	if (StartVex > n)
		cout << "起始顶点不存在" << endl;
	else
	{
		string result;
		G.BFSTraverse(StartVex - 1);
		getline(G.ss, result); result.pop_back();
		cout << result << endl;

		G.ss.clear(); G.ss.str(string());

		G.DFSTraverse(StartVex - 1);
		getline(G.ss, result); result.pop_back();
		cout << result << endl;
	}
}
