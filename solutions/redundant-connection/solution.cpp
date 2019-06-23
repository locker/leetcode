#include <iostream>
#include <queue>
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
	vector<int> findRedundantConnection(const vector<vector<int>>& edges) {
		// Number of nodes in the graph.
		int n = 0;
		// Number of edges coming from each node.
		vector<int> degree;
		// List of neighbors of each node.
		vector<vector<int>> neighbors;
		for (const auto& edge: edges) {
			// Edges are 1-base while we use 0-base indexes.
			int u = edge[0] - 1;
			int v = edge[1] - 1;
			// Extend the arrays if necessary.
			if (u >= n) {
				degree.resize(u + 1);
				neighbors.resize(u + 1);
				n = u + 1;
			}
			if (v >= n) {
				degree.resize(v + 1);
				neighbors.resize(v + 1);
				n = v + 1;
			}
			++degree[u];
			++degree[v];
			neighbors[u].push_back(v);
			neighbors[v].push_back(u);
		}
		// Iteratively remove nodes that have degree 1.
		queue<int> todo;
		for (int u = 0; u < n; ++u) {
			if (degree[u] <= 1)
				todo.push(u);
		}
		vector<bool> visited(n);
		while (!todo.empty()) {
			int u = todo.front();
			if (degree[u] > 1) {
				// A cycle is found. Since only one extra edge
				// was added to the tree, it consists of nodes
				// that haven't been visited.
				break;
			}
			todo.pop();
			if (visited[u])
				continue;
			visited[u] = true;
			for (int v: neighbors[u]) {
				if (!visited[v] && --degree[v] <= 1)
					todo.push(v);
			}
		}
		// Find the last edge in the list that belongs to the cycle.
		for (auto it = edges.rbegin(); it != edges.rend(); ++it) {
			const auto& edge = *it;
			// Edges are 1-base while we use 0-base indexes.
			int u = edge[0] - 1;
			int v = edge[1] - 1;
			if (!visited[u] && !visited[v])
				return edge;
		}
		return {};
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{{1, 2}, {1, 3}, {2, 3}}, // [2, 3]
		{{1, 2}, {2, 3}, {1, 3}}, // [1, 3]
		{{1, 2}, {1, 3}, {1, 4}, {3, 4}}, // [3, 4]
		{{1, 2}, {1, 3}, {1, 4}, {3, 5}, {4, 5}}, // [4, 5]
		{{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}}, // [1, 4]
	};
	Solution solution;
	for (const auto& edges: input) {
		cout << edges << " => " <<
			solution.findRedundantConnection(edges) << endl;
	}
	return 0;
}
