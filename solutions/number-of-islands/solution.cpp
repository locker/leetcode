#include <iostream>
#include <stack>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<char>> grid)
{
	for (auto row = grid.begin(); row != grid.end(); ++row) {
		cout << ' ';
		for (auto cell = row->begin(); cell != row->end(); ++cell)
			cout << *cell;
		cout << endl;
	}
	return cout;
}

class Solution {
	struct Coord {
		int row, col;
		Coord(int r, int c) : row(r), col(c) {}
	};
	stack<Coord> todo;

	void markIsland(vector<vector<char>>& grid, int row, int col) {
		int n_rows = grid.size();
		int n_cols = grid[0].size();

		todo.emplace(row, col);
		while (!todo.empty()) {
			int row, col;
			row = todo.top().row;
			col = todo.top().col;
			todo.pop();
			if (grid[row][col] == 'X')
				continue;
			grid[row][col] = 'X';
			if (row > 0 && grid[row - 1][col] == '1')
				todo.emplace(row - 1, col);
			if (row < n_rows - 1 && grid[row + 1][col] == '1')
				todo.emplace(row + 1, col);
			if (col > 0 && grid[row][col - 1] == '1')
				todo.emplace(row, col - 1);
			if (col < n_cols - 1 && grid[row][col + 1] == '1')
				todo.emplace(row, col + 1);
		}
	}
public:
	int numIslands(vector<vector<char>>& grid) {
		if (grid.empty())
			return 0;

		int n_rows = grid.size();
		int n_cols = grid[0].size();

		int n_islands = 0;
		for (int row = 0; row < n_rows; ++row) {
			for (int col = 0; col < n_cols; ++col) {
				if (grid[row][col] == '1') {
					markIsland(grid, row, col);
					++n_islands;
				}
			}
		}
		return n_islands;
	}
};

int main()
{
	vector<vector<char>> input[] = {
		{}, // 0
		{{'0'}}, // 0
		{{'1'}}, // 1
		{{'1', '1'}}, // 1
		{{'1', '0', '1'}}, // 2
		{
			{'0', '0'},
			{'0', '0'},
		}, // 0
		{
			{'1', '1'},
			{'0', '1'},
		}, // 1
		{
			{'1', '0'},
			{'0', '1'},
		}, // 2
		{
			{'1', '1', '0'},
			{'1', '0', '1'}
		}, // 2
		{
			{'1', '1', '1'},
			{'1', '1', '1'},
			{'1', '1', '1'},
		}, // 1
		{
			{'1', '0', '1'},
			{'1', '0', '1'},
			{'0', '1', '0'},
		}, // 3
		{
			{'1', '1', '1', '1', '0'},
			{'1', '1', '0', '1', '0'},
			{'1', '1', '0', '0', '0'},
			{'0', '0', '0', '0', '0'},
		}, // 1
	};
	Solution solution;
	for (auto& grid: input) {
		cout << "Input:" << endl << grid;
		cout << "Output: " << solution.numIslands(grid) << endl;
	}
	return 0;
}
