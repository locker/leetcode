#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<int>>& grid)
{
	for (auto row = grid.begin(); row != grid.end(); ++row) {
		for (auto cell = row->begin(); cell != row->end(); ++cell)
			cout << *cell;
		cout << endl;
	}
	return out;
}

class Solution {
public:
	int islandPerimeter(const vector<vector<int>>& grid) {
		if (grid.empty())
			return 0;
		int n_rows = grid.size();
		int n_cols = grid[0].size();
		int perimeter = 0;
		for (int row = 0; row < n_rows; ++row) {
			for (int col = 0; col < n_cols; ++col) {
				if (grid[row][col] == 0)
					continue;
				if (row == 0 || grid[row - 1][col] == 0)
					++perimeter;
				if (row == n_rows - 1 ||
				    grid[row + 1][col] == 0)
					++perimeter;
				if (col == 0 || grid[row][col - 1] == 0)
					++perimeter;
				if (col == n_cols - 1 ||
				    grid[row][col + 1] == 0)
					++perimeter;
			}
		}
		return perimeter;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{}, // 0
		{{0}}, // 0
		{{1}}, // 4
		{{1, 1}}, // 6
		{
			{1, 1},
			{1, 0},
		}, // 8
		{
			{1, 1, 1},
			{0, 1, 0},
		}, // 10
		{
			{0, 1, 0, 0},
			{1, 1, 1, 0},
			{0, 1, 0, 0},
			{1, 1, 0, 0},
		}, // 16
	};
	Solution solution;
	for (const auto& grid: input) {
		cout << "Input:" << endl << grid << "Output: " <<
			solution.islandPerimeter(grid) << endl;
	}
	return 0;
}
