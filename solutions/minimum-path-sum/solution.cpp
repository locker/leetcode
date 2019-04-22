#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<int>>& grid)
{
	int max = 0;
	for (auto row = grid.begin(); row != grid.end(); ++row) {
		for (auto cell = row->begin(); cell != row->end(); ++cell) {
			if (max < *cell)
				max = *cell;
		}
	}
	int width = 0;
	while (max > 0) {
		max /= 10;
		++width;
	}
	out << '[';
	for (auto row = grid.begin(); row != grid.end(); ++row) {
		if (row != grid.begin())
			out << ',';
		out << endl << "  [";
		for (auto cell = row->begin(); cell != row->end(); ++cell) {
			if (cell != row->begin())
				out << ',';
			out << setw(width) << *cell;
		}
		out << ']';
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		int n_rows = grid.size();
		int n_cols = grid[0].size();
		for (int col = n_cols - 2; col >= 0; --col)
			grid[n_rows - 1][col] += grid[n_rows - 1][col + 1];
		for (int row = n_rows - 2; row >= 0; --row)
			grid[row][n_cols - 1] += grid[row + 1][n_cols - 1];
		for (int row = n_rows - 2; row >= 0; --row) {
			for (int col = n_cols - 2; col >= 0; --col) {
				grid[row][col] += min(grid[row + 1][col],
						      grid[row][col + 1]);
			}
		}
		return grid[0][0];
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{{1}},
		{{1, 2}},
		{
			{10, 20},
			{1, 100},
			{1, 200},
		},
		{
			{1, 3, 1},
			{1, 5, 1},
			{4, 2, 1},
		},
		{
			{1, 1, 1, 10},
			{2, 2, 2, 20},
			{3, 3, 3, 30},
			{4, 4, 4, 40},
		},
	};
	Solution solution;
	for (auto& grid: input) {
		cout << "Input: " << grid << endl;
		cout << "Output: " << solution.minPathSum(grid) << endl;
	}
	return 0;
}
