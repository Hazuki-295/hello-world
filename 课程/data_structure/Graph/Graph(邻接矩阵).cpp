#include <iostream>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

#define MaxVertexNum 100 // ������Ŀ�����ֵ

/* ͼGraphģ���ࣨ�ڽӾ��� */
template <typename VertexType, typename EdgeType> class Graph { // VertexType��������������ͣ�EdgeType����Ȩͼ��"����Ȩֵ"����������

private:
	/* ͼ���ڽӾ���洢�ṹ */
	VertexType Vex[MaxVertexNum];              // �����
	EdgeType Edge[MaxVertexNum][MaxVertexNum]; // �ڽӾ��󣬱߱�
	int vexnum, arcnum;                        // ͼ�ĵ�ǰ�������ͻ���

	bool visited[MaxVertexNum]; // ���ʱ������

	queue<int> Q; // ��������Q

	/* �������飬�Ե�ǰV��U���е�ÿ�����㣬��¼�Ͷ��㼯U�ж��������ӵĴ�����С�ı� */
	struct Closedge { VertexType adjvex; EdgeType lowcost; } closedge[MaxVertexNum];

public:
	stringstream ss; // ���ڴ�����

	Graph(int Vexnum, int Edgenum) :vexnum(Vexnum), arcnum(Edgenum)
	{
		/* ��ʼ�� */
		for (int i = 0; i < vexnum; i++) Vex[i] = i; // ������Ϣ��0����
		for (int i = 0; i < vexnum; i++)
			for (int j = 0; j < vexnum; j++)
				Edge[i][j] = INT_MAX;

		int x, y, w; // �ڽӵ��������㡢Ȩֵ
		for (int i = 0; i < arcnum; i++) // ����ÿ����
		{
			cin >> x >> y >> w;
			Edge[x - 1][y - 1] = w;
			Edge[y - 1][x - 1] = w;
		}
	}

	int LocateVex(int u)
	{
		if (u >= vexnum)
			return -1;
		else
			return u;
	}

	/* ��ͼG�ж���x�ĵ�һ���ڽӵ㣬�����򷵻ض���š���xû���ڽӵ��ͼ�в�����x���򷵻�-1 */
	int FirstNeighbor(int x)
	{
		if (x >= vexnum) return -1; // ͼ�в�����x������-1

		for (int i = 0; i < vexnum; i++)
			if (Edge[x][i] != 0)    // �����ڵ�һ���ڽӵ㣬�򷵻ض����
				return i;

		return -1; // ��xû���ڽӵ㣬����-1
	}

	/* ����ͼG�ж���y�Ƕ���x��һ���ڽӵ㣬�򷵻س�y�ⶥ��x����һ���ڽӵ�Ķ���š���y��x�����һ���ڽӵ㣬�򷵻�-1 */
	int NextNeighbor(int x, int y)
	{
		if (y == vexnum - 1) return -1; // Խ�磬y+1�������vexnum����ѭ������ִ��
		for (int i = y + 1; i < vexnum; i++)
			if (Edge[x][i] != 0) // ��y�ⶥ��x����һ���ڽӵ�
				return i;

		return -1; // ��y��x�����һ���ڽӵ㣬�򷵻�-1
	}

	/* ����ͼ�еĶ���v */
	void visit(int v) { ss << Vex[v] << " "; }

	/* ��ͼG����������ȱ��� */
	void DFSTraverse()
	{
		for (int v = 0; v < vexnum; v++) // ��ʼ�����ʱ������
			visited[v] = false;
		for (int v = 0; v < vexnum; v++) // ���������Ǵ�v=0��ʼ����
			if (!visited[v]) DFS(v);
	}
	void DFSTraverse(int x)
	{
		for (int v = 0; v < vexnum; v++) // ��ʼ�����ʱ������
			visited[v] = false;
		for (int v = x; v < vexnum; v++) // ���������Ǵ�v=x��ʼ����
			if (!visited[v]) DFS(v);
	}
	void DFS(int v) // �Ӷ���v������������ȱ���ͼG
	{
		visit(v); visited[v] = true; // ���ʶ���v
		for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w))
			if (!visited[w]) DFS(w); //wΪv����δ���ʵ��ڽӶ���
	}

	/* ��ͼG���й�����ȱ��� */
	void BFSTraverse()
	{
		for (int i = 0; i < vexnum; i++)  // ��ʼ�����ʱ������
			visited[i] = false;

		Q = queue<int>();                 // ��ʼ����������Q

		for (int i = 0; i < vexnum; i++)  // ��0�Ŷ��㿪ʼ����
			if (!visited[i]) BFS(i);      // ��ÿ����ͨ��������һ��BFS
	}
	void BFSTraverse(int x)
	{
		for (int i = 0; i < vexnum; i++)  // ��ʼ�����ʱ������
			visited[i] = false;

		Q = queue<int>();                 // ��ʼ����������Q

		for (int i = x; i < vexnum; i++)  // ��x�Ŷ��㿪ʼ����
			if (!visited[i]) BFS(i);      // ��ÿ����ͨ��������һ��BFS
	}
	void BFS(int v) // �Ӷ���v������������ȱ���ͼG
	{
		visit(v); visited[v] = true; // ���ʶ���v
		Q.push(v);                   // ����v�����Q

		while (!Q.empty())
		{
			v = Q.front(); Q.pop(); // ����v������
			for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w)) // ���v�����ڽӵ�
			{
				if (!visited[w]) // wΪv����δ���ʵ��ڽӵ�
				{
					visit(w); visited[w] = true;
					Q.push(w); // ����w�����(��һ�������ʵĶ���)
				}
			}
		}
	}

	/* closedge[k].lowcost = min{closedge[vi].lowcost | closedge[vi].lowcost>0, vi����V-U} */
	int minimum()
	{

		int index = -1, min;
		/* �ҵ���һ����ͨ�ĵ� */
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
		// ������ķ�㷨�ӵ�u���������������G����С������T�����T�ĸ����ߡ�
		// ��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ������鶨�壺
		// struct { VertexType adjvex; EdgeType lowcost; } closedge[MaxVertexNum];
		// closedge[j].lowcost��ʾ�ڼ���U�ж������j�������Ӧ��СȨֵ

		int k = LocateVex(u); int sum = 0;
		for (int j = 0; j < vexnum; j++) // ��������ĳ�ʼ��
		{
			if (j != k)
			{
				closedge[j] = { u ,Edge[k][j] }; // {adjvex, lowcost}
			}
		}
		closedge[k].lowcost = 0; // ��ʼ��U = {u}

		for (int i = 1; i < vexnum; i++) // ѡ������vexnum-1�����㣬���i��1��ʼѭ��
		{
			k = minimum(); // �����С������T����һ����㣺��k����
			if (k == -1) break;
			/* ��ʱclosedge[k].lowcost = min{closedge[vi].lowcost | closedge[vi].lowcost>0, vi����V-U} */
			cout << closedge[k].adjvex + 1 << ' ' << Vex[k] + 1 << ' ' << closedge[k].lowcost << endl; // ����������ı�
			sum += closedge[k].lowcost;

			closedge[k].lowcost = 0; // ��k���㲢��U��
			for (int j = 0; j < vexnum; j++)
			{
				if (Edge[k][j] <= closedge[j].lowcost) // �¶��㲢��U������ѡ����С��
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

	Graph<int, int> G(n, m); // ����ͼ

	int StartVex;
	cin >> StartVex;
	if (StartVex > n)
		cout << "��ʼ���㲻����" << endl;
	else
		G.MiniSpanTree_PRIM(StartVex - 1);
}
