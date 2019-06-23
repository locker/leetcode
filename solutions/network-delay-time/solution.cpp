#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int networkDelayTime(const vector<vector<int>>& times, int n, int k) {
		struct Node {
			int id;
			int delay;
			Node(int i, int d): id(i), delay(d) {}
			bool operator<(const Node& other) const {
				return delay > other.delay;
			}
		};

		vector<vector<Node>> destinations(n);
		for (const auto& t: times)
			destinations[t[0] - 1].emplace_back(t[1] - 1, t[2]);

		int n_visited = 0;
		vector<bool> visited(n);

		priority_queue<Node> todo;
		todo.emplace(k - 1, 0);

		int max_delay = 0;
		while (!todo.empty()) {
			Node node = todo.top();
			todo.pop();

			if (visited[node.id])
				continue;
			++n_visited;
			visited[node.id] = true;
			max_delay = max(max_delay, node.delay);

			for (const auto& other: destinations[node.id]) {
				if (!visited[other.id]) {
					todo.emplace(other.id,
						     node.delay + other.delay);
				}
			}
		}
		if (n_visited < n)
			return -1;
		return max_delay;
	}
};

int main()
{
	tuple<vector<vector<int>>, int, int> input[] = {
		{{}, 1, 1}, // 0
		{{}, 2, 1}, // -1
		{{{1, 2, 1}}, 2, 1}, // 1
		{{{1, 2, 1}}, 2, 2}, // -1
		{{{2, 1, 1}, {2, 3, 1}, {3, 4, 1}}, 4, 2}, // 2
		{{{1, 2, 5}, {1, 3, 2}, {3, 2, 1}}, 3, 3}, // -1
		{{{1, 2, 5}, {1, 3, 2}, {3, 2, 1}}, 3, 1}, // 3
	};
	Solution solution;
	for (const auto& t: input) {
		const auto& times = get<0>(t);
		int n = get<1>(t);
		int k = get<2>(t);
		int delay = solution.networkDelayTime(times, n, k);
		cout << "Input: times = " << times <<
			", N = " << n << ", K = " << k << endl <<
			"Output: " << delay << endl;
	}
	return 0;
}
