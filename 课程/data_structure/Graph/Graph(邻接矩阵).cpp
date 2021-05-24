#include <iostream>
#include <string>
#include <sstream>
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

public:
	stringstream ss; // ���ڴ�����

	Graph(int Vexnum, int Edgenum) :vexnum(Vexnum), arcnum(Edgenum)
	{
		/* ��ʼ�� */
		for (int i = 0; i < vexnum; i++) Vex[i] = i + 1; // ������Ϣ��1����

		int x, y; // �ڽӵ���������
		for (int i = 0; i < arcnum; i++) // ����ÿ����
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
