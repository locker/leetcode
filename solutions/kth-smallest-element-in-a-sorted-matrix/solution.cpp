#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<int>>& matrix)
{
	for (int i = 0; i < (int)matrix.size(); ++i) {
		for (int j = 0; j < (int)matrix[i].size(); ++j) {
			out << matrix[i][j] << ' ';
		}
		out << endl;
	}
	return out;
}

namespace {

class Solution {
public:
	int kthSmallest(const vector<vector<int>>& matrix, int k) {
		int n = matrix.size();
		struct Pos {
			int x, y;
			Pos(int x0, int y0) : x(x0), y(y0) {}
		};
		auto cmp = [&matrix](const Pos& a, const Pos& b) {
			return matrix[a.x][a.y] > matrix[b.x][b.y];
		};
		vector<Pos> q;
		int q_size = min(n, k);
		q.reserve(q_size);
		for (int x = 0; x < q_size; ++x)
			q.emplace_back(x, 0);
		make_heap(q.begin(), q.begin() + q_size, cmp);
		while (true) {
			pop_heap(q.begin(), q.begin() + q_size, cmp);
			auto& p = q[q_size - 1];
			if (--k == 0)
				return matrix[p.x][p.y];
			if (++p.y < n) {
				push_heap(q.begin(), q.begin() + q_size, cmp);
			} else {
				--q_size;
			}
		}
	}
};

} // namespace

int main()
{
	const tuple<vector<vector<int>>, int, int> test_data[] = {
		{
			{
				{1, 5, 9},
				{10, 11, 13},
				{12, 13, 15},
			},
			8, 13,
		},
		{
			{
				{-5},
			},
			1, -5,
		},
	};
	bool success = true;
	Solution solution;
	for (const auto& [matrix, k, expected] : test_data) {
		int result = solution.kthSmallest(matrix, k);
		cout << matrix << "k = " << k << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
		cout << endl;
	}
	return success ? 0 : 1;
}
