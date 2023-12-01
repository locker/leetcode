#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

namespace {

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
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
private:
	void reverseFlow(const vector<vector<int>> &heights,
			 vector<vector<bool>>& flow) {
		const int m = heights.size();
		const int n = heights[0].size();
		queue<pair<int, int>> todo;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (flow[i][j])
					todo.emplace(i, j);
			}
		}
		while (!todo.empty()) {
			auto [i0, j0] = todo.front();
			todo.pop();
			for (int i = i0 - 1; i <= i0 + 1; ++i) {
				for (int j = j0 - 1; j <= j0 + 1; ++j) {
					if (i != i0 && j != j0)
						continue;
					if (i < 0 || i >= m || j < 0 || j >= n)
						continue;
					if (flow[i][j] ||
					    heights[i][j] < heights[i0][j0])
						continue;
					flow[i][j] = true;
					todo.emplace(i, j);
				}
			}
		}
	}
public:
	vector<vector<int>> pacificAtlantic(const vector<vector<int>>& heights) {
		const int m = heights.size();
		const int n = heights[0].size();
		vector<vector<bool>> pacific(m);
		vector<vector<bool>> atlantic(m);
		for (int i = 0; i < m; ++i) {
			if (i == 0) {
				pacific[i].resize(n, true);
			} else {
				pacific[i].resize(n, false);
				pacific[i][0] = true;
			}
			if (i == m - 1) {
				atlantic[i].resize(n, true);
			} else {
				atlantic[i].resize(n, false);
				atlantic[i][n - 1] = true;
			}
		}
		reverseFlow(heights, pacific);
		reverseFlow(heights, atlantic);
		vector<vector<int>> result;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (pacific[i][j] && atlantic[i][j])
					result.push_back({i, j});
			}
		}
		return result;
	}
};

} // namespace

int main()
{
	const tuple<vector<vector<int>>, vector<vector<int>>> test_data[] = {
		{
			{
				{1,2,2,3,5},
				{3,2,3,4,4},
				{2,4,5,3,1},
				{6,7,1,4,5},
				{5,1,1,2,4}
			}, {
				{0,4},{1,3},{1,4},{2,2},{3,0},{3,1},{4,0},
			},
		},
		{
			{{1}}, {{0, 0}},
		},
	};
	bool success = true;
	Solution solution;
	for (const auto& [heights, expected] : test_data) {
		auto result = solution.pacificAtlantic(heights);
		cout << heights << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
