#include <algorithm>
#include <cassert>
#include <iostream>
#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		out << x;
		first = false;
	}
	out << ']';
	return out;
}

class Solution {
public:
	vector<int> findMinHeightTrees(int n, const vector<vector<int>>& edges) {
		vector<unordered_set<int>> neighbors(n);
		for (const auto& e : edges) {
			int i = e[0];
			int j = e[1];
			assert(i != j);
			assert(i >= 0 && i < n);
			assert(j >= 0 && j < n);
			neighbors[i].insert(j);
			neighbors[j].insert(i);
		}
		vector<int> todo;
		for (int i = 0; i < n; ++i) {
			if (neighbors[i].size() <= 1)
				todo.push_back(i);
		}
		vector<int> leaves;
		while (!todo.empty()) {
			swap(leaves, todo);
			todo.clear();
			for (int i : leaves) {
				if (neighbors[i].empty())
					continue;
				int j = *neighbors[i].begin();
				if (neighbors[j].erase(i) == 0)
					assert(false);
				if (neighbors[j].size() == 1)
					todo.push_back(j);
			}
		}
		return leaves;
	}
};

int main()
{
	const tuple<int, vector<vector<int>>, vector<int>> test_data[] = {
		{1, {}, {0}},
		{2, {{1, 0}}, {0, 1}},
		{3, {{0, 1}, {1, 2}}, {1}},
		{4, {{1, 0}, {1, 2}, {1, 3}}, {1}},
		{6, {{3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}}, {3, 4}}
	};
	bool success = true;
	Solution solution;
	for (const auto& [n, edges, expected] : test_data) {
		auto result = solution.findMinHeightTrees(n, edges);
		cout << edges << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
