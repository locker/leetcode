#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<int>>& grid)
{
	for (auto row = grid.begin(); row != grid.end(); ++row) {
		for (auto cell = row->begin(); cell != row->end(); ++cell)
			out << ' ' << setw(3) << *cell;
		out << endl;
	}
	return out;
}

class Solution {
public:
	int swimInWater(const vector<vector<int>>& grid) {
		int n_rows = grid.size();
		int n_cols = grid[0].size();

		// Entry (i, j) stores the least time to get from (i, j)
		// to the bottom-right cell or -1 if not yet known.
		vector<vector<int>> time(n_rows, vector<int>(n_cols, -1));
		time[n_rows - 1][n_cols - 1] = grid[n_rows - 1][n_cols - 1];

		// Traverse the grid starting from the bottom-right cell
		// and initializing least times. At each iteration choose
		// the cell that has the smallest time.
		struct Cell {
			int row, col, time;
			Cell(int r, int c, int t) : row(r), col(c), time(t) {}
			bool operator<(const Cell& other) const {
				return time > other.time;
			}
		};
		priority_queue<Cell> todo;
		todo.emplace(n_rows - 1, n_cols - 1,
			     grid[n_rows - 1][n_cols - 1]);
		while (time[0][0] < 0) {
			int r = todo.top().row;
			int c = todo.top().col;
			int t = todo.top().time;
			todo.pop();
			if (r > 0 && time[r - 1][c] < 0) {
				time[r - 1][c] = max(grid[r - 1][c], t);
				todo.emplace(r - 1, c, time[r - 1][c]);
			}
			if (r < n_rows - 1 && time[r + 1][c] < 0) {
				time[r + 1][c] = max(grid[r + 1][c], t);
				todo.emplace(r + 1, c, time[r + 1][c]);
			}
			if (c > 0 && time[r][c - 1] < 0) {
				time[r][c - 1] = max(grid[r][c - 1], t);
				todo.emplace(r, c - 1, time[r][c - 1]);
			}
			if (c < n_cols - 1 && time[r][c + 1] < 0) {
				time[r][c + 1] = max(grid[r][c + 1], t);
				todo.emplace(r, c + 1, time[r][c + 1]);
			}
		}
		return time[0][0];
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{{1}}, // 1
		{{2, 1}}, // 2
		{{0, 2},
		 {1, 3}}, // 3
		{{1, 1, 1},
		 {4, 5, 5},
		 {2, 3, 2}}, // 4
		{{ 0,  1,  2,  3,  4},
		 {24, 23, 22, 21,  5},
		 {12, 13, 14, 15, 16},
		 {11, 17, 18, 19, 20},
		 {10,  9,  8,  7,  6}}, // 16
	};
	Solution solution;
	for (const auto& grid: input) {
		cout << "Input:" << endl << grid <<
			"Output: " << solution.swimInWater(grid) << endl;
	}
	return 0;
}
