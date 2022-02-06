#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
private:
	struct Choice {
		// Cell position.
		int i, j;
		// Current position in the array of allowed digits.
		int curr;
		// Array of allowed digits.
		vector<int> allowed;
	};
	// Returns the digit at (i, j) - 1 or -1 if not set.
	int digitAt(const vector<vector<char>>& board, int i, int j) {
		int c = board[i][j];
		if (c == '.')
			return -1;
		return c - '0' - 1;
	}
	// Checks if d0 is allowed at (i0, j0).
	bool isAllowed(const vector<vector<char>>& board,
		       int i0, int j0, int d0) {
		for (int i = 0; i < 9; ++i) {
			int d = digitAt(board, i, j0);
			if (d == d0)
				return false;
		}
		for (int j = 0; j < 9; ++j) {
			int d = digitAt(board, i0, j);
			if (d == d0)
				return false;
		}
		int i1 = i0 / 3 * 3;
		int j1 = j0 / 3 * 3;
		for (int i = i1; i < i1 + 3; ++i) {
			for (int j = j1; j < j1 + 3; ++j) {
				int d = digitAt(board, i, j);
				if (d == d0)
					return false;
			}
		}
		return true;
	}
	// Returns all possible choices for (i, j).
	Choice getChoice(const vector<vector<char>>& board, int i, int j) {
		Choice choice;
		choice.i = i;
		choice.j = j;
		choice.curr = 0;
		for (int d = 0; d < 9; ++d) {
			if (isAllowed(board, i, j, d))
				choice.allowed.push_back(d);
		}
		assert(choice.allowed.size() > 0);
		return choice;
	}
public:
	void solveSudoku(vector<vector<char>>& board) {
		vector<Choice> choices;
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (digitAt(board, i, j) < 0) {
					choices.push_back(
						getChoice(board, i, j));
				}
			}
		}
		int n = 0;
		while (n < (int)choices.size()) {
			auto& choice = choices[n];
			if (choice.curr >= (int)choice.allowed.size()) {
				board[choice.i][choice.j] = '.';
				choice.curr = 0;
				assert(n > 0);
				--n;
				continue;
			}
			int d = choice.allowed[choice.curr];
			if (!isAllowed(board, choice.i, choice.j, d)) {
				++choice.curr;
				continue;
			}
			board[choice.i][choice.j] = '0' + d + 1;
			++n;
		}
	}
};

static void print_board(const vector<vector<char>>& board)
{
	for (const auto& row : board) {
		for (char cell : row) {
			cout << cell << ' ';
		}
		cout << endl;
	}
}

int main()
{
	pair<vector<vector<char>>, vector<vector<char>>> test_data[] = {
		{
			{
				{'5','3','.','.','7','.','.','.','.'},
				{'6','.','.','1','9','5','.','.','.'},
				{'.','9','8','.','.','.','.','6','.'},
				{'8','.','.','.','6','.','.','.','3'},
				{'4','.','.','8','.','3','.','.','1'},
				{'7','.','.','.','2','.','.','.','6'},
				{'.','6','.','.','.','.','2','8','.'},
				{'.','.','.','4','1','9','.','.','5'},
				{'.','.','.','.','8','.','.','7','9'},
			},
			{
				{'5','3','4','6','7','8','9','1','2'},
				{'6','7','2','1','9','5','3','4','8'},
				{'1','9','8','3','4','2','5','6','7'},
				{'8','5','9','7','6','1','4','2','3'},
				{'4','2','6','8','5','3','7','9','1'},
				{'7','1','3','9','2','4','8','5','6'},
				{'9','6','1','5','3','7','2','8','4'},
				{'2','8','7','4','1','9','6','3','5'},
				{'3','4','5','2','8','6','1','7','9'},
			},
		},
	};
	bool success = true;
	Solution solution;
	for (auto& [board, expected] : test_data) {
		cout << "Input:" << endl;
		print_board(board);
		solution.solveSudoku(board);
		cout << "Output:" << endl;
		print_board(board);
		if (board != expected) {
			cout << "ERROR: expected" << endl;
			print_board(expected);
			success = false;
		}
		cout << endl;
	}
	return success ? 0 : 1;
}
