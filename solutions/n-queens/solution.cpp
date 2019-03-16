#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<string>>& v)
{
	out << '[' << endl;
	for (auto it1 = v.begin(); it1 != v.end(); ++it1) {
		out << " [";
		for (auto it2 = it1->begin(); it2 != it1->end(); ++it2) {
			if (it2 != it1->begin())
				out << "  ";
			out << '"' << *it2 << '"';
			if (it2 != it1->end() - 1)
				out << ',' << endl;
		}
		out << ']';
		if (it1 != v.end() - 1)
			out << ',';
		out << endl;
	}
	out << ']' << endl;
	return out;
}

class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		// Array of solutions found so far.
		vector<vector<string>> result;
		if (n == 0)
			return result;

		// Current solution.
		vector<int> solution(n, -1);

		// Append the current solution to the result.
		auto append_solution = [&]() {
			vector<string> v;
			v.reserve(n);
			for (int row = 0; row < n; ++row) {
				int col = solution[row];
				string s(n, '.');
				s[col] = 'Q';
				v.push_back(move(s));
			}
			result.push_back(move(v));
		};

		// Check if cell (row0, col0) can accommodate a queen.
		// Assume rows >= row0 are empty.
		auto check_cell = [&](int row0, int col0) {
			for (int row = 0; row < row0; ++row) {
				if (solution[row] == col0)
					return false;
				if (solution[row] + row0 - row == col0)
					return false;
				if (solution[row] - row0 + row == col0)
					return false;
			}
			return true;
		};

		int row = 0;
		while (row >= 0) {
			int col;
			for (col = solution[row] + 1; col < n; ++col) {
				if (check_cell(row, col))
					break;
			}
			if (col < n) {
				solution[row] = col;
				if (row == n - 1)
					append_solution();
				else
					++row;
			} else {
				solution[row] = -1;
				--row;
			}
		}
		return result;
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n < 5; ++n) {
		cout << "Input: " << n << endl;
		cout << "Output: " << endl;
		cout << solution.solveNQueens(n) << endl;
	}
	return 0;
}
