#include <iostream>
#include <stack>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<char>>& board)
{
	for (auto row = board.begin(); row != board.end(); ++row) {
		for (auto cell = row->begin(); cell != row->end(); ++cell) {
			if (cell != row->begin())
				cout << ' ';
			cout << *cell;
		}
		cout << endl;
	}
	return out;
}

class Solution {
public:
	void solve(vector<vector<char>>& board) {
		int n_rows = board.size();
		if (n_rows <= 2)
			return;
		int n_cols = board[0].size();
		if (n_cols <= 2)
			return;

		// Represents a coordinate on the board.
		struct Coord {
			int row, col;
			Coord(int r, int c) : row(r), col(c) {}
		};

		// Iterate the board starting from the borders,
		// turning all O's that must not be flipped to Z's.
		stack<Coord> todo;
		for (int col = 0; col < n_cols; ++col) {
			if (board[0][col] == 'O')
				todo.emplace(0, col);
			if (board[n_rows - 1][col] == 'O')
				todo.emplace(n_rows - 1, col);
		}
		for (int row = 1; row < n_rows - 1; ++row) {
			if (board[row][0] == 'O')
				todo.emplace(row, 0);
			if (board[row][n_cols - 1] == 'O')
				todo.emplace(row, n_cols - 1);
		}
		while (!todo.empty()) {
			int row = todo.top().row;
			int col = todo.top().col;
			todo.pop();
			board[row][col] = 'Z';
			if (row > 0 && board[row - 1][col] == 'O')
				todo.emplace(row - 1, col);
			if (row < n_rows - 1 && board[row + 1][col] == 'O')
				todo.emplace(row + 1, col);
			if (col > 0 && board[row][col - 1] == 'O')
				todo.emplace(row, col - 1);
			if (col < n_cols - 1 && board[row][col + 1] == 'O')
				todo.emplace(row, col + 1);
		}

		// Then overwrite all remaining O's with X's and
		// turn Z's back to O's.
		for (int row = 0; row < n_rows; ++row) {
			for (int col = 0; col < n_cols; ++col) {
				switch (board[row][col]) {
				case 'O':
					board[row][col] = 'X';
					break;
				case 'Z':
					board[row][col] = 'O';
					break;
				default:
					break;
				}
			}
		}
	}
};

int main()
{
	vector<vector<char>> input[] = {
		{
			{'O', 'X', 'X'},
			{'X', 'O', 'O'},
			{'X', 'O', 'X'},
		},
		{
			{'X', 'O', 'X'},
			{'X', 'X', 'O'},
			{'X', 'O', 'X'},
			{'O', 'X', 'X'},
		},
		{
			{'X', 'X', 'X', 'X'},
			{'X', 'O', 'O', 'X'},
			{'X', 'X', 'O', 'X'},
			{'X', 'O', 'X', 'X'},
		},
	};
	Solution solution;
	for (auto& board: input) {
		cout << "Input:" << endl << board << endl;
		solution.solve(board);
		cout << "Output:" << endl << board << endl;
	}
	return 0;
}
