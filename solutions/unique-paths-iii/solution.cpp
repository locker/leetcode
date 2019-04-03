#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& matrix)
{
	out << '[';
	for (auto row = matrix.begin(); row != matrix.end(); ++row) {
		if (row != matrix.begin())
			out << ',';
		out << endl << "  [";
		for (auto elem = row->begin(); elem != row->end(); ++elem) {
			if (elem != row->begin())
				out << ',';
			out << setw(2) << *elem;
		}
		out << ']';
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	int uniquePathsIII(vector<vector<int>>& grid) {
		const int EMPTY = 0;
		const int START = 1;
		const int END = 2;
		const int OBSTACLE = -1;

		struct point {
			int row, col;
			point(int r, int c) : row(r), col(c) {}
		};

		int n_rows = grid.size();
		int n_cols = grid[0].size();

		int n_empty = 0;
		stack<point> todo;
		for (int i = 0; i < n_rows; ++i) {
			for (int j = 0; j < n_cols; ++j) {
				switch (grid[i][j]) {
				case START:
					todo.emplace(i, j);
					++n_empty;
					break;
				case EMPTY:
					++n_empty;
					break;
				default:
					break;
				}
			}
		}

		int result = 0;
		while (!todo.empty()) {
			const auto& p = todo.top();
			switch (grid[p.row][p.col]) {
			case EMPTY:
			case START:
				grid[p.row][p.col] = OBSTACLE;
				if (p.row > 0 &&
				    grid[p.row - 1][p.col] != OBSTACLE)
					todo.emplace(p.row - 1, p.col);
				if (p.row < n_rows - 1 &&
				    grid[p.row + 1][p.col] != OBSTACLE)
					todo.emplace(p.row + 1, p.col);
				if (p.col > 0 &&
				    grid[p.row][p.col - 1] != OBSTACLE)
					todo.emplace(p.row, p.col - 1);
				if (p.col < n_cols - 1 &&
				    grid[p.row][p.col + 1] != OBSTACLE)
					todo.emplace(p.row, p.col + 1);
				--n_empty;
				break;
			case END:
				if (n_empty == 0)
					++result;
				todo.pop();
				break;
			case OBSTACLE:
				grid[p.row][p.col] = EMPTY;
				++n_empty;
				todo.pop();
				break;
			default:
				break;
			}
		}
		return result;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{
			{ 1, 0, 0, 0},
			{ 0, 0, 0, 0},
			{ 0, 0, 2,-1},
		}, // 2
		{
			{ 1, 0, 0, 0},
			{ 0, 0, 0, 0},
			{ 0, 0, 0, 2}
		}, // 4
		{
			{ 0, 1},
			{ 2, 0},
		}, // 0
	};
	Solution solution;
	for (auto& grid: input) {
		cout << "Input:" << endl << grid << endl;
		cout << "Output: " << solution.uniquePathsIII(grid) << endl;
		cout << endl;
	}
	return 0;
}
