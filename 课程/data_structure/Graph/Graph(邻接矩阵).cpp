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

	/* (��Ȩ)����ͼ���� */
	Graph(int _vexnum, int _arcnum) :vexnum(_vexnum), arcnum(_arcnum)
	{
		/* ��ʼ�����㼯���߼� */
		for (int i = 0; i < vexnum; i++) Vex[i] = i + 1; // ������Ϣ��1����
		for (int i = 0; i < vexnum; i++)
			for (int j = 0; j < vexnum; j++)
				Edge[i][j] = 0/*INT_MAX*/; // ��Ȩͼ(��Ȩͼ)

		int x, y, index_x, index_y;    // �ڽӵ��������㡢��Ȩֵ
		for (int i = 0; i < arcnum; i++) // ����ÿ����
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

	/* ��ֵ���ҡ���ͼG�д���ֵΪval�Ķ��㣬�򷵻ظö�����ͼ�е�λ�ã����򷵻�-1 */
	int LocateVex(VertexType val)
	{
		for (int i = 0; i < vexnum; i++) // ���㼯�в���ֵΪval�Ķ���
			if (Vex[i] == val)
				return i;
		return -1; // �������򷵻�-1
	}

	/* ��ͼG��λ��Ϊx�Ķ���ĵ�һ���ڽӵ㣬�����򷵻ض���š�����û���ڽӵ����ͼ�в����ڣ��򷵻�-1 */
	int FirstNeighbor(int x)
	{
		if (x < 0 || x >= vexnum) return -1;  // ͼ�в�����λ��Ϊx�Ķ��㣬����-1

		for (int i = 0; i < vexnum; i++)      // �ڱ߼��в������ڽӵ�
			if (Edge[x][i] != 0/*INT_MAX*/)   // �����ڵ�һ���ڽӵ㣬�򷵻ض����
				return i;

		return -1; // ��λ��Ϊx�Ķ���û���ڽӵ㣬����-1
	}

	/* ��ͼG��λ��Ϊx�Ķ���(�����y����)��һ���ڽӵ��λ�á���y��x�����һ���ڽӵ㣬�򷵻�-1 */
	int NextNeighbor(int x, int y)
	{
		for (int i = y + 1; i < vexnum; i++) // �ڱ߼��в��ҳ�y�ⶥ��x����һ���ڽӵ�
			if (Edge[x][i] != 0/*INT_MAX*/)  // ��������һ���ڽӵ㣬�򷵻ض����
				return i;

		return -1; // ��y��x�����һ���ڽӵ㣬�򷵻�-1
	}

	/* ����ͼ��λ��Ϊx�Ķ��� */
	void visit(int x) { ss << Vex[x] << " "; }

	/* ������ȱ������ӵ�һ��������� */
	void DFSTraverse()
	{
		for (int i = 0; i < vexnum; i++) // ��ʼ�����ʱ������
			visited[i] = false;
		for (int i = 0; i < vexnum; i++) // ���������Ǵ�v=0(��һ������)��ʼ����
			if (!visited[i]) DFS(i);
	}
	/* ������ȱ������Ӹ�������v���� */
	void DFSTraverse(VertexType v)
	{
		for (int i = 0; i < vexnum; i++) // ��ʼ�����ʱ������
			visited[i] = false;

		int index = LocateVex(v);        // �ҵ���ʼ�����λ��
		DFS(index);                      // ����������ȱ����ö���(���ڵ���ͨ����)

		for (int i = 0; i < vexnum; i++) // ����������ͨ����
			if (!visited[i]) DFS(i);
	}
	/* ��λ��Ϊv�Ķ���������ݹ��������ȱ���ͼG */
	void DFS(int v)
	{
		visit(v); visited[v] = true; // ���ʶ���v
		for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w)) // wΪv����δ���ʵ��ڽӵ�
			if (!visited[w]) DFS(w); // �ݹ�ر������ڽӵ�(�������)
	}

	/* ������ȱ������ӵ�һ��������� */
	void BFSTraverse()
	{
		for (int i = 0; i < vexnum; i++)  // ��ʼ�����ʱ������
			visited[i] = false;

		Q = queue<int>();                 // ��ʼ����������Q

		for (int i = 0; i < vexnum; i++)  // ��0�Ŷ��㿪ʼ����
			if (!visited[i]) BFS(i);      // ��ÿ��"��ͨ����"����һ��BFS
	}
	/* ������ȱ������Ӹ�������v���� */
	void BFSTraverse(VertexType v)
	{
		for (int i = 0; i < vexnum; i++)  // ��ʼ�����ʱ������
			visited[i] = false;

		Q = queue<int>();                 // ��ʼ����������Q

		int index = LocateVex(v);         // �ҵ���ʼ�����λ��
		BFS(index);                       // ���ȹ�����ȱ����ö���(���ڵ���ͨ����)

		for (int i = 0; i < vexnum; i++)  // ����������ͨ����
			if (!visited[i]) BFS(i);
	}
	/* ��λ��Ϊv�Ķ���������ǵݹ�ع�����ȱ���ͼG */
	void BFS(int v)
	{
		visit(v); visited[v] = true; // ���ʶ���v
		Q.push(v);                   // ����v�����Q(�Լ���������ڽӵ�)

		/* ��ʼ����������v��·����ͨ��·������Ϊ1,2,3...�Ķ��� */
		while (!Q.empty())
		{
			v = Q.front(); Q.pop(); // ����v������
			for (int w = FirstNeighbor(v); w >= 0; w = NextNeighbor(v, w)) // ���v�����ڽӵ�
			{
				if (!visited[w]) // wΪv����δ���ʵ��ڽӵ�
				{
					visit(w); visited[w] = true; // ���ʶ���w
					Q.push(w); // ����w�����(���ڽӵ�Ϊ��һ�������ʵĶ���)
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

	int StartVex; cin >> StartVex;
	if (G.LocateVex(StartVex) == -1)
		cout << "��ʼ���㲻����" << endl;
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
