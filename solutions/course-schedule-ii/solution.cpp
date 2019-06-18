#include <iostream>
#include <queue>
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
public:
	vector<int> findOrder(int count, const vector<vector<int>>& prerequisites) {
		//
		// What we have is a graph in which vertexes represent courses
		// and edges represent dependencies: there's an edge coming
		// from vertex i to vertex j iff course i depends on course j.
		// The algorithm is trivial:
		//
		//  1. Take any vertex which doesn't any incoming edges
		//     (a course that doesn't depend on any other course).
		//  2. Remove the vertex and all edges originating from it.
		//  3. Add the course corresponding to the vertex to the
		//     resulting schedule.
		//  4. Unless the graph is empty, go to step 1.
		//

		// Map: vertex i => array of vertexes j such that there's
		// an edge coming from i to j.
		vector<vector<int>> edges(count);

		// Map: vertex i => number of incoming edges.
		vector<int> order(count);

		for (const auto& it: prerequisites) {
			edges[it[1]].push_back(it[0]);
			++order[it[0]];
		}

		queue<int> todo;
		for (int i = 0; i < count; ++i) {
			if (order[i] == 0)
				todo.push(i);
		}

		vector<int> schedule;
		schedule.reserve(count);

		while (!todo.empty()) {
			auto i = todo.front();
			todo.pop();
			for (auto j: edges[i]) {
				if (--order[j] == 0)
					todo.push(j);
			}
			schedule.push_back(i);
		}

		if (static_cast<int>(schedule.size()) < count) {
			// Looks like there's a cycle in the graph
			// hence there's no schedule such that all
			// courses are finished.
			schedule.clear();
		}
		return schedule;
	}
};

int main()
{
	pair<int, vector<vector<int>>> input[] = {
		{1, {{0,0}}}, // []
		{2, {{1,0}}}, // [0,1]
		{2, {{1,0},{0,1}}}, // []
		{3, {{1,0},{2,0},{2,1}}}, // [0,1,2]
		{3, {{1,0},{0,2},{2,1}}}, // []
		{4, {{1,0},{3,1},{3,2},{3,0}}}, // [0,2,1,3]
		{4, {{1,0},{2,1},{3,2},{1,3}}}, // []
	};
	Solution solution;
	for (const auto& p: input) {
		auto count = p.first;
		const auto& prerequisites = p.second;
		auto order = solution.findOrder(count, prerequisites);
		cout << "Input: " << count << ", " << prerequisites << endl <<
			"Output: " << order << endl;
	}
	return 0;
}
