#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<int>>& matrix) {
	for (const auto& row : matrix) {
		for (int val : row)
			out << val << ' ';
		out << endl;
	}
	return out;
}

class NumMatrix {
private:
	vector<vector<int>> sums;
public:
	NumMatrix(vector<vector<int>> matrix) {
		const int n = matrix.size();
		const int m = matrix[0].size();
		sums = move(matrix);
		for (int i = 1; i < n; ++i)
			sums[i][0] += sums[i - 1][0];
		for (int j = 1; j < m; ++j)
			sums[0][j] += sums[0][j - 1];
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j < m; ++j) {
				long long sum = sums[i][j];
				sum += sums[i - 1][j] + sums[i][j - 1];
				sum -= sums[i - 1][j - 1];
				sums[i][j] = sum;
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		long long sum = sums[row2][col2];
		if (row1 > 0)
			sum -= sums[row1 - 1][col2];
		if (col1 > 0)
			sum -= sums[row2][col1 - 1];
		if (row1 > 0 && col1 > 0) 
			sum += sums[row1 - 1][col1 - 1];
		return sum;
	}
};

int main()
{
	const pair<vector<vector<int>>, vector<tuple<int, int, int, int, int>>> test_data[] = {
		{
			{
				{1},
				{-7},
			},
			{
				{0, 0, 0, 0, 1},
				{1, 0, 1, 0, -7},
				{0, 0, 1, 0, -6},
			},
		},
		{
			{
				{3, 0, 1, 4, 2},
				{5, 6, 3, 2, 1},
				{1, 2, 0, 1, 5},
				{4, 1, 0, 1, 7},
				{1, 0, 3, 0, 5},
			}, 
			{
				{0, 0, 0, 0, 3},
				{1, 1, 1, 1, 6},
				{1, 0, 1, 1, 11},
				{0, 0, 0, 1, 3},
				{2, 1, 4, 3, 8},
				{1, 1, 2, 2, 11},
				{1, 2, 2, 4, 12},
			},
		},
	};
	bool success = true;
	for (const auto& [matrix, args] : test_data) {
		cout << "Matrix:" << endl << matrix;
		NumMatrix nm(matrix);
		for (const auto& [row1, col1, row2, col2, expected] : args) {
			int result = nm.sumRegion(row1, col1, row2, col2);
			cout << "row1=" << row1 << ", col1=" << col1 <<
				", row2=" << row2 << ", col2=" << col2 <<
				" -> " << result << endl;
			if (result != expected) {
				cout << "  ERROR: expected " << expected << endl;
				success = false;
			}
		}
	}
	return success ? 0 : 1;
}
