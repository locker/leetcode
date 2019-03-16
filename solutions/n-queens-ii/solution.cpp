#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	int totalNQueens(int n) {
		int result = 0;
		if (n == 0)
			return result;

		// Current solution.
		vector<int> solution(n, -1);

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
					++result;
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
	for (int n = 0; n < 10; ++n)
		cout << n << " => " << solution.totalNQueens(n) << endl;
	return 0;
}
