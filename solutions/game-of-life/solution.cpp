#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<int>>& board)
{
	for (const auto& row : board) {
		for (int val : row) {
			cout << val << ' ';
		}
		cout << endl;
	}
	return out;
}

class Solution {
public:
	void gameOfLife(vector<vector<int>>& board) {
		if (board.empty())
			return;
		int m = board.size();
		int n = board[0].size();
		for (int i0 = 0; i0 < m; ++i0) {
			for (int j0 = 0; j0 < n; ++j0) {
				int& val = board[i0][j0];
				int live_neighbors = 0;
				for (int i = max(0, i0 - 1);
				     i < min(m, i0 + 2); ++i) {
					for (int j = max(0, j0 - 1);
					     j < min(n, j0 + 2); ++j) {
						if ((i != i0 || j != j0) &&
						    (board[i][j] & 1) != 0) {
							++live_neighbors;
						}
					}
				}
				if (val != 0) {
					if (live_neighbors < 2 ||
					    live_neighbors > 3) {
						// dies
					} else {
						// lives
						val |= 2;
					}
				} else {
					if (live_neighbors == 3) {
						// becomes live
						val |= 2;
					}
				}
			}
		}
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				board[i][j] >>= 1;
			}
		}
	}
};

int main()
{
	pair<vector<vector<int>>, vector<vector<int>>> test_data[] = {
		{{}, {}},
		{{{0}}, {{0}}},
		{{{1}}, {{0}}},
		{{{1, 1}}, {{0, 0}}},
		{{{1, 1}, {1, 0}}, {{1, 1}, {1, 1}}},
		{{{1, 0}, {1, 0}}, {{0, 0}, {0, 0}}},
		{
			{{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}},
			{{0, 0, 0}, {1, 0, 1}, {0, 1, 1}, {0, 1, 0}},
		}
	};
	bool success = true;
	Solution solution;
	for (auto& [board, expected] : test_data) {
		cout << "Input:" << endl << board;
		solution.gameOfLife(board);
		cout << "Output:" << endl << board;
		if (board != expected) {
			cout << "ERROR! Expected:" << endl << expected;
			success = false;
		}
	}
	return success ? 0 : 1;
}
