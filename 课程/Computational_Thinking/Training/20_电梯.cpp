#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include <set>
using namespace std;

enum class status { UP, DOWN };

struct request {
	// 数据成员
	int from; int to; status statu;
	// 构造函数
	request(int from, int to, status statu) :from(from), to(to), statu(statu) {}
};

int main()
{
	int cases = 0;
	int startfloor, uptime, downtime, standtime;

	while (cin >> startfloor >> uptime >> downtime >> standtime) {
		char c = getchar(); string line; getline(cin, line);
		cout << "Case " << ++cases << ": ";
		stringstream buffer(line); vector<request> moves;
		set<int> upfloor, downfloor;
		int from, to;
		while (buffer >> from >> c >> to) {
			if ((from - to) < 0) { // 上升
				moves.push_back(request(from, to, status::UP));
				upfloor.insert(from); upfloor.insert(to);
			}
			else { // 下降
				moves.push_back(request(from, to, status::DOWN));
				downfloor.insert(from); downfloor.insert(to);
			}
		}
		int standTime = (upfloor.size() + downfloor.size()) * standtime;
		vector<int> upFloor(upfloor.begin(), upfloor.end()), downFloor(downfloor.begin(), downfloor.end());
		int upTime = (upFloor.back() - upFloor.front()) * uptime;
		int downTime = (downFloor.back() - downFloor.front()) * downtime;
		int totalTime = standTime + upTime + downTime;
		cout << totalTime << endl;
		// 现有若干个楼层需要上下人，则满足这些请求"最少"需要耗费多长时间(包括最后的停留时间)
	}

	return 0;
}
