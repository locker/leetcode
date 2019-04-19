#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<int>>& matrix)
{
	int max = 0;
	for (auto row = matrix.begin(); row != matrix.end(); ++row) {
		for (auto cell = row->begin(); cell != row->end(); ++cell) {
			if (max < *cell)
				max = *cell;
		}
	}
	int width = 0;
	while (max > 0) {
		max /= 10;
		++width;
	}
	out << '[';
	for (auto row = matrix.begin(); row != matrix.end(); ++row) {
		if (row != matrix.begin())
			out << ',';
		out << endl << "  [";
		for (auto cell = row->begin(); cell != row->end(); ++cell) {
			if (cell != row->begin())
				out << ',';
			out << setw(width) << *cell;
		}
		out << ']';
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	bool searchMatrix(const vector<vector<int>>& matrix, int target) {
		if (matrix.empty())
			return false;
		int n_rows = matrix.size();
		int n_cols = matrix[0].size();
		int row = 0;
		int col = n_cols - 1;
		while (row < n_rows && col >= 0) {
			int val = matrix[row][col];
			if (target == val)
				return true;
			if (target > val)
				++row;
			else
				--col;
		}
		return false;
	}
};

int main()
{
	const vector<vector<int>> matrix = {
		{ 1,  4,  7, 11, 15},
		{ 2,  5,  8, 12, 19},
		{ 3,  6,  9, 16, 22},
		{10, 13, 14, 17, 24},
		{18, 21, 23, 26, 30}
	};
	cout << "matrix = " << matrix << endl;
	Solution solution;
	for (int target = 0; target < 32; ++target) {
		cout << "target = " << target << ": ";
		if (!solution.searchMatrix(matrix, target))
			cout << "not ";
		cout << "found" << endl;
	}
	return 0;
}
