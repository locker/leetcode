#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<char>>& matrix)
{
	out << '[';
	for (auto row = matrix.begin(); row != matrix.end(); ++row) {
		if (row != matrix.begin())
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
	int maximalSquare(const vector<vector<char>>& matrix) {
		if (matrix.empty())
			return 0;

		int max_area = 0;
		int n_rows = matrix.size();
		int n_cols = matrix[0].size();

		//
		// Area between (i,j) and (i+len,j+len) is a square of 1s
		// iff matrix[i][j] stores 1 and all the three areas below
		// are squares of 1s, too:
		// 1. (i+1,j) - (i+len,j+len-1)
		// 2. (i,j+1) - (i+len-1,j+len)
		// 3. (i+1,j+1) - (i+len-1,j+len-1)
		//

		// Array entry i stores the size of the max square of 1s
		// starting at column i.
		vector<int> max_square(n_cols + 1);

		for (int row = n_rows - 1; row >= 0; --row) {
			int bottom_right = 0;
			for (int col = n_cols - 1; col >= 0; --col) {
				int bottom = max_square[col];
				int right = max_square[col + 1];
				max_square[col] = matrix[row][col] == '0' ? 0 :
					1 + min({bottom, right, bottom_right});
				bottom_right = bottom;
				int area = max_square[col] * max_square[col];
				if (max_area < area)
					max_area = area;
			}
		}

		return max_area;
	}
};

int main()
{
	vector<vector<char>> input[] = {
		{}, // 0
		{{'0'}}, // 0
		{{'1'}}, // 1
		{{'1', '1'}}, // 1
		{
			{'1','0'},
			{'1','1'},
		}, // 1
		{
			{'1','1'},
			{'1','1'},
		}, // 4
		{
			{'1','1','0'},
			{'1','1','1'},
			{'0','1','1'},
		}, // 4
		{
			{'1','1','1','0'},
			{'1','1','1','1'},
			{'0','1','1','0'},
		}, // 4
		{
			{'1','0','1','0','0'},
			{'1','0','1','1','1'},
			{'1','1','1','1','1'},
			{'1','0','0','1','0'},
		}, // 4
		{
			{'1','1','1','1','0'},
			{'0','1','1','1','1'},
			{'1','1','1','1','0'},
			{'1','1','0','1','1'},
		}, // 9
	};
	Solution solution;
	for (const auto& matrix: input) {
		cout << "Input: " << matrix << endl <<
			"Output: " << solution.maximalSquare(matrix) <<
			endl << endl;
	}
	return 0;
}
