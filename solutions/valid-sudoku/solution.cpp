#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
	bool isValidSudoku(const vector<vector<char>>& board) {
		// Check rows.
		vector<bool> used(9);
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				char c = board[i][j];
				if (c != '.') {
					int v = c - '0' - 1;
					if (used[v])
						return false;
					used[v] = true;
				}
			}
			fill(used.begin(), used.end(), false);
		}
		// Check columns.
		for (int j = 0; j < 9; ++j) {
			for (int i = 0; i < 9; ++i) {
				char c = board[i][j];
				if (c != '.') {
					int v = c - '0' - 1;
					if (used[v])
						return false;
					used[v] = true;
				}
			}
			fill(used.begin(), used.end(), false);
		}
		// Check squares.
		for (int n = 0; n < 9; ++n) {
			int i0 = (n / 3) * 3;
			int j0 = (n % 3) * 3;
			for (int i = i0; i < i0 + 3; ++i) {
				for (int j = j0; j < j0 + 3; ++j) {
					char c = board[i][j];
					if (c != '.') {
						int v = c - '0' - 1;
						if (used[v])
							return false;
						used[v] = true;
					}
				}
			}
			fill(used.begin(), used.end(), false);
		}
		return true;
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
	pair<vector<vector<char>>, bool> test_data[] = {
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
			true
		},
		{
			{
				{'8','3','.','.','7','.','.','.','.'},
				{'6','.','.','1','9','5','.','.','.'},
				{'.','9','8','.','.','.','.','6','.'},
				{'8','.','.','.','6','.','.','.','3'},
				{'4','.','.','8','.','3','.','.','1'},
				{'7','.','.','.','2','.','.','.','6'},
				{'.','6','.','.','.','.','2','8','.'},
				{'.','.','.','4','1','9','.','.','5'},
				{'.','.','.','.','8','.','.','7','9'},
			},
			false
		},
		{
			{
				{'9','3','.','.','7','.','.','.','.'},
				{'6','.','.','1','9','5','.','.','.'},
				{'.','9','8','.','.','.','.','6','.'},
				{'8','.','.','.','6','.','.','.','3'},
				{'4','.','.','8','.','3','.','.','1'},
				{'7','.','.','.','2','.','.','.','6'},
				{'.','6','.','.','.','.','2','8','.'},
				{'.','.','.','4','1','9','.','.','5'},
				{'.','.','.','.','8','.','.','7','9'},
			},
			false
		},
		{
			{
				{'.','.','.','.','5','.','.','1','.'},
				{'.','4','.','3','.','.','.','.','.'},
				{'.','.','.','.','.','3','.','.','1'},
				{'8','.','.','.','.','.','.','2','.'},
				{'.','.','2','.','7','.','.','.','.'},
				{'.','1','5','.','.','.','.','.','.'},
				{'.','.','.','.','.','2','.','.','.'},
				{'.','2','.','9','.','.','.','.','.'},
				{'.','.','4','.','.','.','.','.','.'},
			},
			false
		}
	};
	bool success = true;
	Solution solution;
	for (const auto& [board, expected] : test_data) {
		bool result = solution.isValidSudoku(board);
		cout << "Board:" << endl;
		print_board(board);
		cout << "Solvable? " << (result ? "Yes" : "No") << endl;
		if (result != expected) {
			cout << "  ERROR: expected " <<
				(expected ? "Yes" : "No") << endl;
			success = false;
		}
		cout << endl;
	}
	return success ? 0 : 1;
}
