#include <iostream>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

#define MaxVertexNum 100  // 图中顶点数目的最大值

/* 边表结点模板类 */
template <typename InfoType> struct ArcNode {
	// 成员
	int adjvex; InfoType info; ArcNode *nextarc; // 该弧所指向的顶点的位置(下标)、边权值，指向下一条邻接弧的指针
	// 构造函数
	ArcNode(int _adjvex, InfoType _info) :adjvex(_adjvex), info(_info), nextarc(nullptr) {};

};

/* 顶点表结点模板类 */
template <typename VertexType, typename InfoType> struct VNode {
	// 成员
	VertexType data;              // 顶点信息
	ArcNode<InfoType> *firstarc;  // 指向第一条依附该顶点的弧的指针
	// 构造函数
	VNode() :data(0), firstarc(nullptr) {}; // 空则表示不存在邻接点
};

/* 图Graph模板类（邻接表） */
template <typename VertexType, typename InfoType> class Graph { // VertexType：顶点的数据类型，InfoType：带权图中"边上权值"的数据类型

private:
	using VNode = VNode<VertexType, InfoType>;
	using ArcNode = ArcNode<InfoType>;

	/* 图的邻接表存储结构 */
	vector<VNode> vertices; // 顶点表
	int vexnum, arcnum;     // 图的顶点数和弧数

	// 顶点表顺序存储，便于随机访问。边表(各个顶点的邻接表)在顶点结点中。

	bool visited[MaxVertexNum]; // 访问标记数组


	queue<int> Q; // 辅助队列Q

	/* 辅助数组，对当前V－U集中的每个顶点，记录和顶点集U中顶点相连接的代价最小的边 */
	struct Closedge { VertexType adjvex; InfoType lowcost; } closedge[MaxVertexNum];

public:
	queue<int> print; // 用于处理输出结果

	/* (带权)无向图构造 */
	Graph(int _vexnum, int _arcnum) :vexnum(_vexnum), arcnum(_arcnum)
	{
		/* 初始化顶点集、边集 */
		vertices = vector<VNode>(vexnum);
		for (int i = 0; i < vexnum; i++) vertices[i].data = i + 1; // 顶点信息从1计起

		VertexType x, y; InfoType w; // 邻接的两个顶点、边权值
		for (int i = 0; i < arcnum; i++) // 输入每条边
		{
			cin >> x >> y >> w;
			InsertArc(x, y, w); InsertArc(y, x, w); // 无向图对称弧
		}
	}

	/* 在图G中增添弧<x,y>，权值为w */
	bool InsertArc(VertexType x, VertexType y, InfoType w)
	{
		int index_x = LocateVex(x), index_y = LocateVex(y);
		ArcNode *p; // 辅助指针
		for (p = vertices[index_x].firstarc; p != nullptr; p = p->nextarc) // 若x没有邻接边，则直接退出循环
		{
			if (p->nextarc == nullptr) // 找到该顶点的最后一个邻接边
				break;
		}
		if (p == nullptr) // 若x没有邻接点
			vertices[index_x].firstarc = new ArcNode(index_y, w); // 添加第一条弧
		else // 若x有邻接点，则p指向最后一个邻接边
			p->nextarc = new ArcNode(index_y, w); // 添加下一条弧
		return true;
	}

	/* 判断图G是否存在弧<x,y> */
	bool Adjacent()
	{

	}

	/* 获取图G中弧<x,y>对应的权值 */
	InfoType Get_edge_value(VertexType x, VertexType y)
	{
		int index_x = LocateVex(x), index_y = LocateVex(y);
	}

	/* 按值查找。若图G中存在值为val的顶点，则返回该顶点在图中的位置，否则返回-1 */
	int LocateVex(VertexType val)
	{
		for (int i = 0; i < vexnum; i++) // 顶点集中查找值为val的顶点
			if (vertices[i].data == val)
				return i;
		return -1; // 不存在则返回-1
	}

	/* 求图G中位置为x的顶点的第一个邻接点，若有则返回顶点号。若其没有邻接点或在图中不存在，则返回-1 */
	int FirstNeighbor(int x)
	{
		if (x < 0 || x >= vexnum) return -1; // 图中不存在位置为x的顶点，返回-1

		ArcNode *p = vertices[x].firstarc;   // 第一个邻接点

		if (p != nullptr)     // 若存在第一个邻接点，则返回顶点号
			return p->adjvex;

		return -1;            // 若位置为x的顶点没有邻接点，返回-1
	}

	/* 求图G中位置为x的顶点(相对于y处的)下一个邻接点的位置。若y是x的最后一个邻接点，则返回-1 */
	int NextNeighbor(int x, int y)
	{
		ArcNode *p; // 辅助指针
		for (p = vertices[x].firstarc; p->adjvex != y; p = p->nextarc); // 找到邻接边<x,y>
		if (p->nextarc != nullptr)
			return p->nextarc->adjvex; // 若存在下一个邻接点，则返回顶点号

		return -1; // 若y是x的最后一个邻接点，则返回-1
	}

	/* 访问图中位置为x的顶点 */
	void visit(int x) { print.push(vertices[x].data); }

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

	/* 在辅助数组closedge中，从V-U集中选择最小跨越边(lowcost最小)对应的顶点k，返回其位置 */
	int minimum() // closedge[k].lowcost = min{closedge[v_i].lowcost | closedge[v_i].lowcost>0, v_i属于V-U}
	{
		int min_adj; InfoType min_cost = INT_MAX; // 最小跨越边的V-U集顶点、边权值
		for (int i = 0; i < arcnum; i++) // 遍历closedge数组
		{
			if (closedge[i].lowcost != 0 && closedge[i].lowcost < min_cost) // V-U集顶点中，跨越边权值最小
			{
				min_adj = i; // V-U集中的顶点k的位置(对应的U集顶点在closedge[i].adjvex中)
				min_cost = closedge[i].lowcost; // 最小跨越边的权值
			}
		}
		return min_adj; // 返回V-U集顶点k的位置
	}

	/* 用普里姆(Prim)算法从顶点u出发构造网G的最小生成树T，输出T的各条边。 */
	void MiniSpanTree_Prim(VertexType u)
	{
		int k = LocateVex(u); int sum = 0; // 顶点u的位置、生成树权值之和
		ArcNode *p; // 辅助指针
		for (int j = 0; j < vexnum; j++) // 辅助数组初始化
		{
			if (j != k) closedge[j] = { u ,INT_MAX }; // 不存在边则为INT_MAX
		}
		/* 初始时，U仅包含顶点u，即 U = {u} */
		for (p = vertices[k].firstarc; p != nullptr; p = p->nextarc) // 枚举k的所有邻居
		{
			closedge[p->adjvex] = { u, p->info }; // V-U集的顶点，优先级即为顶点与u邻接的边权值
		}
		closedge[k].lowcost = 0; // lowcost置为0则表示已并入U集

		for (int i = 1; i < vexnum; i++) // 选择其余vexnum-1个顶点，因此需迭代vexnum-1次，每次U集并入一个顶点
		{
			k = minimum(); // 从V-U集中选择最小跨越边对应的顶点，它将是最小生成树T的下一个顶点
			// 即 closedge[k].lowcost = min{closedge[v_i].lowcost | closedge[v_i].lowcost>0, v_i属于V-U}

			// 输出生成树的边(最小跨越边)
			cout << closedge[k].adjvex        // U集的顶点(此前已并入)
				<< ' ' << vertices[k].data    // V-U集的顶点
				<< ' ' << closedge[k].lowcost // 边权值
				<< endl;
			sum += closedge[k].lowcost;       // 记入权值之和

			closedge[k].lowcost = 0; // 新顶点k并入U集

			/* 更新顶点优先级数，与顶点k互不关联的顶点都无需考虑 */
			for (p = vertices[k].firstarc; p != nullptr; p = p->nextarc) // 只需遍历顶点k的每一邻居v
			{
				if (p->info < closedge[p->adjvex].lowcost) // 若边kv的权值 小于 当前的优先级数(之前的其他跨越边的权值，如uv)
				{
					closedge[p->adjvex] = { vertices[k].data ,p->info }; // 则更新顶点优先级
				}
			}
		}
		cout << sum << endl; // 最小生成树构造完成，输出总权值
	}
};

int main()
{
	int n, m; cin >> n >> m;

	Graph<int, int> G(n, m); // 构造图

	int StartVex; cin >> StartVex;
	if (G.LocateVex(StartVex) == -1)
	{
		cout << "起始顶点不存在" << endl;
	}
	else
	{
		stringstream result; cout << endl;

		G.BFSTraverse(StartVex); cout << "BFS:";// 广度优先搜索
		for (int i = 0; i < n - 1; i++)
		{
			cout << G.print.front() << ' ';
			G.print.pop();
		}
		cout << G.print.front() << endl << endl; G.print.pop();

		G.DFSTraverse(StartVex); cout << "DFS:";// 深度优先搜索
		for (int i = 0; i < n - 1; i++)
		{
			cout << G.print.front() << ' ';
			G.print.pop();
		}
		cout << G.print.front() << endl << endl; G.print.pop();

		cout << "MST:" << endl;
		G.MiniSpanTree_Prim(StartVex); // 最小生成树
	}

	return 0;
}
