#include <iostream>
#include <stack>
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
	int maximalRectangle(const vector<vector<char>>& matrix) {
		if (matrix.empty())
			return 0;

		int n_rows = matrix.size();
		int n_cols = matrix[0].size();

		//
		// We will iterate from the last to the first row
		// calculating the max area among rectangles whose
		// top-left corner lays at the current row.
		//

		// Max rectangle area encountered so far.
		int max_area = 0;

		// Heights of columns starting at the current row.
		// Updated iteratively.
		vector<int> col_height(n_cols);

		// Describes a candidate for the max rectangle.
		struct Rect {
			// Column of the top-left corner.
			int col;
			// Number of rows spanned.
			int height;
			Rect(int c, int h) : col(c), height(h) {}
		};

		// Stack invariant: the rectangle having the max height
		// is always at the top.
		stack<Rect> max_rect;

		for (int row = n_rows - 1; row >= 0; --row) {
			for (int col = 0; col <= n_cols; ++col) {
				// Compute the height of the current column.
				int height = 0;
				if (col < n_cols) {
					if (matrix[row][col] == '1')
						height = ++col_height[col];
					else
						height = col_height[col] = 0;
				}
				// Calculate the max area among rectangles
				// having greater height.
				int last_col = col;
				while (!max_rect.empty() &&
				       max_rect.top().height >= height) {
					auto& r = max_rect.top();
					int area = (col - r.col) * r.height;
					if (max_area < area)
						max_area = area;
					last_col = r.col;
					max_rect.pop();
				}
				// Push a candidate for the max rectangle
				// to the stack.
				if (height > 0)
					max_rect.emplace(last_col, height);
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
		{{'1','0'}}, // 1
		{{'0','1'}}, // 1
		{{'1','1'}}, // 2
		{
			{'1','1'},
			{'1','0'},
		}, // 2
		{
			{'1','0','1'},
			{'1','1','1'},
		}, // 3
		{
			{'1','1','0'},
			{'1','1','1'},
		}, // 4
		{
			{'1','1','1','1','1'},
			{'1','1','0','0','1'},
			{'1','0','1','1','1'},
		}, // 5
		{
			{'1','0','1','0','0'},
			{'1','0','1','1','1'},
			{'1','1','1','1','1'},
			{'1','0','0','1','0'}
		}, // 6
		{
			{'1','1','1','1'},
			{'1','1','1','1'},
			{'1','1','1','1'},
		}, // 12
		{
			{'1','1','1','1','1','1','1','1'},
			{'1','1','1','1','1','1','1','0'},
			{'1','1','1','1','1','1','1','0'},
			{'1','1','1','1','1','0','0','0'},
			{'0','1','1','1','1','0','0','0'}
		}, // 21
	};
	Solution solution;
	for (const auto& matrix: input) {
		cout << "Input: " << matrix << endl <<
			"Output: " << solution.maximalRectangle(matrix) <<
			endl << endl;
	}
	return 0;
}
