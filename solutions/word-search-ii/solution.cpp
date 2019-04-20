#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<string>& words)
{
	out << '[';
	for (auto it = words.begin(); it != words.end(); ++it) {
		if (it != words.begin())
			out << ',';
		out << '"' << *it << '"';
	}
	out << ']';
	return out;
}

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
	vector<string> findWords(vector<vector<char>>& board,
				 vector<string>& words) {
		vector<string> result;
		if (board.empty() || words.empty())
			return result;

		int n_rows = board.size();
		int n_cols = board[0].size();
		int word_count = words.size();

		sort(words.begin(), words.end());

		struct Cell {
			int row, col;
			int begin, end;
			Cell(int r, int c, int b, int e):
				row(r), col(c), begin(b), end(e) {}
		};

		stack<Cell> todo;
		vector<bool> found(word_count);

		int begin, end;
		for (begin = 0; begin < word_count; begin = end) {
			end = begin + 1;
			char c = words[begin][0];
			while (end < word_count && words[end][0] == c)
				++end;
			for (int row = 0; row < n_rows; ++row) {
				for (int col = 0; col < n_cols; ++col) {
					if (board[row][col] == c)
						todo.emplace(row, col, begin, end);
				}
			}
		}

		int pos = 0;
		while (!todo.empty()) {
			auto& cell = todo.top();
			int row = cell.row;
			int col = cell.col;
			if (board[row][col] == 0) {
				board[row][col] = words[cell.begin][--pos];
				todo.pop();
				continue;
			}
			board[row][col] = 0;
			++pos;
			for (begin = cell.begin; begin < cell.end; begin = end) {
				end = begin + 1;
				if (found[begin])
					continue;
				int len = words[begin].length();
				if (pos == len) {
					result.push_back(words[begin]);
					found[begin] = true;
					continue;
				}
				char c = words[begin][pos];
				while (end < cell.end && words[end][pos] == c)
					++end;
				if (row > 0 && board[row - 1][col] == c)
					todo.emplace(row - 1, col, begin, end);
				if (row < n_rows - 1 && board[row + 1][col] == c)
					todo.emplace(row + 1, col, begin, end);
				if (col > 0 && board[row][col - 1] == c)
					todo.emplace(row, col - 1, begin, end);
				if (col < n_cols - 1 && board[row][col + 1] == c)
					todo.emplace(row, col + 1, begin, end);
			}
		}
		return result;
	}
};

int main()
{
	vector<vector<char>> board = {
		{'o','a','a','n'},
		{'e','t','a','e'},
		{'i','h','k','r'},
		{'i','f','l','v'}
	};
	vector<string> words = {
		"a", "oath", "pea", "eat", "rain",
		"oathie", "oathieo", "oa", "ea",
		"eaan", "eaane", "fii", "fiih",
		"fiihf", "fiihkl", "ffiihklf",
	};
	Solution solution;
	cout << "Input:" << endl;
	cout << "board = " << board << endl;
	cout << "words = " << words << endl;
	cout << "Output: " << solution.findWords(board, words) << endl;
	return 0;
}
