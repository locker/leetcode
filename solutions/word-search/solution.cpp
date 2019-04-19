#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<char>>& board)
{
	out << '[';
	for (auto row = board.begin(); row != board.end(); ++row) {
		if (row != board.begin())
			out << ',';
		out << endl << "  [";
		for (auto cell = row->begin(); cell != row->end(); ++cell) {
			if (cell != row->begin())
				out << ',';
			out << '\'' << *cell << '\'';
		}
		out << ']';
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	bool exist(vector<vector<char>>& board, const string& word) {
		int len = word.length();
		if (len == 0)
			return false;
		if (board.empty())
			return false;

		int n_rows = board.size();
		int n_cols = board[0].size();

		struct Cell {
			int row, col;
			Cell(int r, int c): row(r), col(c) {}
		};

		stack<Cell> todo;
		for (int row = 0; row < n_rows; ++row) {
			for (int col = 0; col < n_cols; ++col) {
				if (board[row][col] == word[0])
					todo.emplace(row, col);
			}
		}

		int pos = 0;
		bool found = false;
		while (!todo.empty()) {
			auto& cell = todo.top();
			if (board[cell.row][cell.col] == 0) {
				board[cell.row][cell.col] = word[--pos];
				todo.pop();
				continue;
			}
			board[cell.row][cell.col] = 0;
			if (++pos == len)
				found = true;
			if (found)
				continue;
			if (cell.row > 0 &&
			    board[cell.row - 1][cell.col] == word[pos])
				todo.emplace(cell.row - 1, cell.col);
			if (cell.row < n_rows - 1 &&
			    board[cell.row + 1][cell.col] == word[pos])
				todo.emplace(cell.row + 1, cell.col);
			if (cell.col > 0 &&
			    board[cell.row][cell.col - 1] == word[pos])
				todo.emplace(cell.row, cell.col - 1);
			if (cell.col < n_cols - 1 &&
			    board[cell.row][cell.col + 1] == word[pos])
				todo.emplace(cell.row, cell.col + 1);
		}
		return found;
	}
};

int main()
{
	vector<vector<char>> board = {
		{'A', 'B', 'C', 'E'},
		{'S', 'F', 'C', 'S'},
		{'A', 'D', 'E', 'E'}
	};
	const string words[] = {
		"ABCCED", // true
		"SEE", // true
		"ABCB", // false
		"ABCA", // false
		"EE", // true
		"ESCE", // true
		"ESCCEE", // false
		"DFBASAD", // false
	};
	Solution solution;
	cout << "board = " << board << endl;
	for (const auto& word: words) {
		cout << "word = \"" << word << "\": ";
		if (!solution.exist(board, word))
			cout << "not ";
		cout << "found" << endl;
	}
	return 0;
}
