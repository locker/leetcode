#include <iostream>
#include <stack>
#include <utility>
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
	// Helper function that checks if there's a cycle in the schedule
	// graph by implementing DFS starting from the given node.
	bool canFinishFrom(int count, const vector<vector<int>>& edges,
			   int start, vector<bool>& visited) {
		// Flag i is set iff node i lays on the path from the
		// starting to the currently visited node.
		vector<bool> on_path(count);

		// "Two-pass" DFS stack of nodes: each node is visited twice,
		// when we go deeper and when we return; we use a flag to
		// differentiate between the two cases.
		stack<pair<int, bool>> todo;

		todo.emplace(start, false);
		while (!todo.empty()) {
			int node = todo.top().first;
			bool& seen = todo.top().second;

			if (seen) {
				// Back track. Remove the node from the path.
				on_path[node] = false;
				todo.pop();
				continue;
			}
			seen = true;

			if (on_path[node]) {
				// The node is already on the path: a cycle!
				return false;
			}

			if (visited[node]) {
				// No need to visit the node if we've already
				// iterated over it during our search.
				todo.pop();
				continue;
			}
			visited[node] = true;

			// Add the node to the path and schedule all adjacent
			// nodes to be visited next.
			on_path[node] = true;
			for (auto next: edges[node])
				todo.emplace(next, false);
		}
		return true;
	}
public:
	bool canFinish(int count, const vector<vector<int>>& prerequisites) {
		//
		// Represent prerequisites by a graph in which there's an edge
		// from node i to node j iff job j depends on job i. Then the
		// schedule can be finished iff there's no cycle in the graph.
		// To detect a cycle implement DFS.
		//

		// Map: node i => node j such that there's edge i->j.
		vector<vector<int>> edges(count);
		for (const auto& it: prerequisites)
			edges[it[1]].push_back(it[0]);

		// Flag i is set iff node i has been visited by DFS.
		vector<bool> visited(count);

		for (int i = 0; i < count; ++i) {
			if (!canFinishFrom(count, edges, i, visited))
				return false;
		}
		return true;
	}
};

int main()
{
	pair<int, vector<vector<int>>> input[] = {
		{1, {{0,0}}}, // false
		{2, {{1,0}}}, // true
		{2, {{1,0},{0,1}}}, // false
		{3, {{1,0},{2,0},{2,1}}}, // true
		{3, {{1,0},{0,2},{2,1}}}, // false
		{4, {{1,0},{3,1},{3,2},{3,0}}}, // true
		{4, {{1,0},{2,1},{3,2},{1,3}}}, // false
	};
	Solution solution;
	for (const auto& p: input) {
		auto count = p.first;
		const auto& prerequisites = p.second;
		bool can_finish = solution.canFinish(count, prerequisites);
		cout << "Input: " << count << ", " << prerequisites << endl <<
			"Output: " << (can_finish ? "true" : "false") << endl;
	}
	return 0;
}
