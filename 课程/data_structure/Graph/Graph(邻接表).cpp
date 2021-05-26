#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include "../../../Ҷ��_hazuki/GitHub/hello-world/�γ�/data_structure/List/LinkList.cpp"
using namespace std;

#define MaxVertexNum 100  // ͼ�ж�����Ŀ�����ֵ

/* �߱���ģ���� */
template <typename InfoType> struct ArcNode {
	// ��Ա
	int adjvex; InfoType info; // �û���ָ��Ķ����λ��(�±�)����Ȩֵ��next������������
	// ���캯��
	ArcNode(int _adjvex, InfoType _info) :adjvex(_adjvex), info(_info) {};
};

/* �������ģ���� */
template <typename VertexType, typename InfoType> struct VNode {
	// ��Ա
	VertexType data;                     // ������Ϣ
	ListNode<ArcNode<InfoType>> *first;  // ָ���һ�������ö���Ļ���ָ��
	// ���캯��
	VNode() :data(0), first(nullptr) {}; // �����ʾ�������ڽӵ�
};

/* ͼGraphģ���ࣨ�ڽӱ� */
template <typename VertexType, typename InfoType> class Graph { // VertexType��������������ͣ�InfoType����Ȩͼ��"����Ȩֵ"����������

private:
	using VNode = VNode<VertexType, InfoType>;
	using ArcNode = ArcNode<InfoType>;

	/* ͼ���ڽӱ�洢�ṹ */
	vector<VNode> vertices = vector<VNode>(MaxVertexNum); // �����
	int vexnum, arcnum; // ͼ�Ķ������ͻ���

	// �����˳��洢������������ʡ��߱�(����������ڽӱ�)�ڶ������С�

	bool visited[MaxVertexNum]; // ���ʱ������


	queue<int> Q; // ��������Q

	/* �������飬�Ե�ǰV��U���е�ÿ�����㣬��¼�Ͷ��㼯U�ж��������ӵĴ�����С�ı� */
	struct Closedge { VertexType adjvex; InfoType lowcost; } closedge[MaxVertexNum];

public:
	queue<int> print; // ���ڴ���������

	/* (��Ȩ)����ͼ���� */
	Graph(int _vexnum, int _arcnum) :vexnum(_vexnum), arcnum(_arcnum)
	{
		/* ��ʼ�����㼯���߼� */
		for (int i = 0; i < vexnum; i++) Vex[i] = i + 1; // ������Ϣ��1����
		for (int i = 0; i < vexnum; i++)
			for (int j = 0; j < vexnum; j++)
				Edge[i][j] = INT_MAX/*0*/; // ��Ȩͼ(��Ȩͼ)

		int x, y, w, index_x, index_y;     // �ڽӵ��������㡢��Ȩֵ
		for (int i = 0; i < arcnum; i++)   // ����ÿ����
		{
			cin >> x >> y >> w;
			index_x = LocateVex(x); index_y = LocateVex(y);
			Edge[index_x][index_y] = w;
			Edge[index_y][index_x] = w;
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
			if (Edge[x][i] != INT_MAX/*0*/)   // �����ڵ�һ���ڽӵ㣬�򷵻ض����
				return i;

		return -1; // ��λ��Ϊx�Ķ���û���ڽӵ㣬����-1
	}

	/* ��ͼG��λ��Ϊx�Ķ���(�����y����)��һ���ڽӵ��λ�á���y��x�����һ���ڽӵ㣬�򷵻�-1 */
	int NextNeighbor(int x, int y)
	{
		for (int i = y + 1; i < vexnum; i++) // �ڱ߼��в��ҳ�y�ⶥ��x����һ���ڽӵ�
			if (Edge[x][i] != INT_MAX/*0*/)  // ��������һ���ڽӵ㣬�򷵻ض����
				return i;

		return -1; // ��y��x�����һ���ڽӵ㣬�򷵻�-1
	}

	/* ����ͼ��λ��Ϊx�Ķ��� */
	void visit(int x) { print.push(Vex[x]); }

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

	/* �ڸ�������closedge�У���V-U����ѡ����С��Խ��(lowcost��С)��Ӧ�Ķ���k��������λ�� */
	int minimum() // closedge[k].lowcost = min{closedge[v_i].lowcost | closedge[v_i].lowcost>0, v_i����V-U}
	{
		int min_adj; EdgeType min_cost = INT_MAX; // ��С��Խ�ߵ�V-U�����㡢��Ȩֵ
		for (int i = 0; i < arcnum; i++) // ����closedge����
		{
			if (closedge[i].lowcost != 0 && closedge[i].lowcost < min_cost) // V-U�������У���Խ��Ȩֵ��С
			{
				min_adj = i; // V-U���еĶ���k��λ��(��Ӧ��U��������closedge[i].adjvex��)
				min_cost = closedge[i].lowcost; // ��С��Խ�ߵ�Ȩֵ
			}
		}
		return min_adj; // ����V-U������k��λ��
	}

	/* ������ķ(Prim)�㷨�Ӷ���u����������G����С������T�����T�ĸ����ߡ� */
	void MiniSpanTree_Prim(VertexType u)
	{
		int k = LocateVex(u); int sum = 0; // ����u��λ�á�������Ȩֵ֮��
		for (int j = 0; j < vexnum; j++)   // ���������ʼ��
		{
			/* ��ʼʱ��U����������u���� U = {u} */
			if (j != k) closedge[j] = { u ,Edge[k][j] }; // ��ʱV-U���Ķ������ȼ���Ϊ������u�ڽӵı�Ȩֵ(�����ڱ���ΪINT_MAX)
		}
		closedge[k].lowcost = 0; // lowcost��Ϊ0���ʾ�Ѳ���U��

		for (int i = 1; i < vexnum; i++) // ѡ������vexnum-1�����㣬��������vexnum-1�Σ�ÿ��U������һ������
		{
			k = minimum(); // ��V-U����ѡ����С��Խ�߶�Ӧ�Ķ��㣬��������С������T����һ������
			// �� closedge[k].lowcost = min{closedge[v_i].lowcost | closedge[v_i].lowcost>0, v_i����V-U}

			// ����������ı�(��С��Խ��)
			cout << closedge[k].adjvex        // U���Ķ���(��ǰ�Ѳ���)
				<< ' ' << Vex[k]              // V-U���Ķ���
				<< ' ' << closedge[k].lowcost // ��Ȩֵ
				<< endl;
			sum += closedge[k].lowcost;       // ����Ȩֵ֮��

			closedge[k].lowcost = 0; // �¶���k����U��

			/* ���¶������ȼ������붥��k���������Ķ��㶼���迼�� */
			for (int v = 0; v < vexnum; v++) // ֻ���������k��ÿһ�ھ�v
			{
				if (Edge[k][v] < closedge[v].lowcost) // ����kv��Ȩֵ С�� ��ǰ�����ȼ���(֮ǰ��������Խ�ߵ�Ȩֵ����uv)
				{
					closedge[v] = { Vex[k] ,Edge[k][v] }; // ����¶������ȼ�
				}
			}
		}
		cout << sum << endl; // ��С������������ɣ������Ȩֵ
	}
};

int main()
{
	int n, m; cin >> n >> m;

	Graph<int, int> G(n, m); // ����ͼ

	int StartVex; cin >> StartVex;
	if (G.LocateVex(StartVex) == -1)
	{
		cout << "��ʼ���㲻����" << endl;
	}
	else
	{
		stringstream result; cout << endl;

		G.BFSTraverse(StartVex); cout << "BFS:";// �����������
		for (int i = 0; i < n - 1; i++)
		{
			cout << G.print.front() << ' ';
			G.print.pop();
		}
		cout << G.print.front() << endl << endl; G.print.pop();

		G.DFSTraverse(StartVex); cout << "DFS:";// �����������
		for (int i = 0; i < n - 1; i++)
		{
			cout << G.print.front() << ' ';
			G.print.pop();
		}
		cout << G.print.front() << endl << endl; G.print.pop();

		cout << "MST:" << endl;
		G.MiniSpanTree_Prim(StartVex); // ��С������
	}

	return 0;
}
