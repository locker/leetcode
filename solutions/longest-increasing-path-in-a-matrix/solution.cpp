#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<int>>& matrix)
{
	for (auto row = matrix.begin(); row != matrix.end(); ++row) {
		for (auto cell = row->begin(); cell != row->end(); ++cell)
			cout << ' ' << setw(3) << *cell;
		cout << endl;
	}
	return out;
}

class Solution {
	// Keep todo here rather than on function stack so as not to
	// recreate it for each call to longestIncreasingPathAt() -
	// this is okay as the function leaves todo empty upon return.
	struct Cell {
		int row, col;
		Cell(int r, int c): row(r), col(c) {}
	};
	stack<Cell> todo;

	// Return the length of the longest increasing path starting
	// at the intersection of the given row and column.
	int longestIncreasingPathAt(const vector<vector<int>>& matrix,
				    vector<vector<int>>& memo,
				    int start_row, int start_col) {
		if (memo[start_row][start_col] > 0)
			return memo[start_row][start_col];

		int n_rows = matrix.size();
		int n_cols = matrix[0].size();

		todo.emplace(start_row, start_col);
		while (!todo.empty()) {
			int row = todo.top().row;
			int col = todo.top().col;
			int val = matrix[row][col];

			// If we didn't visit a neighbour that has a greater
			// value, then visit it, otherwise update this cell
			// memo with the max increasing path.
			int len = 0;
			if (row > 0 && matrix[row - 1][col] > val) {
				if (memo[row - 1][col] == 0) {
					todo.emplace(row - 1, col);
					continue;
				}
				len = max(len, memo[row - 1][col]);
			}
			if (row < n_rows - 1 && matrix[row + 1][col] > val) {
				if (memo[row + 1][col] == 0) {
					todo.emplace(row + 1, col);
					continue;
				}
				len = max(len, memo[row + 1][col]);
			}
			if (col > 0 && matrix[row][col - 1] > val) {
				if (memo[row][col - 1] == 0) {
					todo.emplace(row, col - 1);
					continue;
				}
				len = max(len, memo[row][col - 1]);
			}
			if (col < n_cols - 1 && matrix[row][col + 1] > val) {
				if (memo[row][col + 1] == 0) {
					todo.emplace(row, col + 1);
					continue;
				}
				len = max(len, memo[row][col + 1]);
			}
			memo[row][col] = len + 1;
			todo.pop();
		}
		return memo[start_row][start_col];
	}
public:
	int longestIncreasingPath(const vector<vector<int>>& matrix) {
		if (matrix.empty())
			return 0;

		int n_rows = matrix.size();
		int n_cols = matrix[0].size();

		// Memo matrix that stores the max increasing path length
		// starting at the corresponding cell or 0 if the cell has
		// not been examined yet.
		vector<vector<int>> memo(n_rows, vector<int>(n_cols));

		int max_len = 0;
		for (int i = 0; i < n_rows; ++i) {
			for (int j = 0; j < n_cols; ++j) {
				int len = longestIncreasingPathAt(matrix, memo,
								  i, j);
				max_len = max(max_len, len);
			}
		}
		return max_len;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{}, // []

		{{1}}, // [1]

		{{2, 1, 2}}, // [1, 2]

		{{1, 2, 3}}, // [1, 2, 3]
		{{1, 2, 3},

		 {2, 5, 4}}, // [1, 2, 3, 4, 5]

		{{9, 9, 4},
		 {6, 6, 8},
		 {2, 1, 1}}, // [1, 2, 6, 9]

		{{3, 4, 5},
		 {3, 2, 6},
		 {3, 2, 1}}, // [3, 4, 5, 6]
	};
	Solution solution;
	for (const auto& matrix: input) {
		cout << "Input:" << endl << matrix << "Output: " <<
			solution.longestIncreasingPath(matrix) << endl << endl;
	}
	return 0;
}
