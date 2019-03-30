#include <iostream>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << endl << "  " << *it;
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	vector<int> spiralOrder(const vector<vector<int>>& matrix) {
		if (matrix.empty())
			return {};
		int n_rows = matrix.size();
		int n_cols = matrix[0].size();
		vector<int> result;
		result.reserve(n_rows * n_cols);
		int i1 = 0, i2 = n_rows - 1;
		int j1 = 0, j2 = n_cols - 1;
		while (i1 <= i2 && j1 <= j2) {
			for (int j = j1; j <= j2 && i1 <= i2; ++j)
				result.push_back(matrix[i1][j]);
			++i1;
			for (int i = i1; i <= i2 && j1 <= j2; ++i)
				result.push_back(matrix[i][j2]);
			--j2;
			for (int j = j2; j >= j1 && i1 <= i2; --j)
				result.push_back(matrix[i2][j]);
			--i2;
			for (int i = i2; i >= i1 && j1 <= j2; --i)
				result.push_back(matrix[i][j1]);
			++j1;
		}
		return result;
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{},
		{
			{1},
		},
		{
			{1, 2},
		},
		{
			{1},
			{2},
		},
		{
			{1, 2},
			{3, 4},
		},
		{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9},
		},
		{
			{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9,10,11,12},
		},
		{
			{1},
			{2},
			{3},
			{4},
			{5},
			{6},
			{7},
			{8},
			{9},
			{10},
		},
		{
			{1, 2, 3},
			{4, 5, 6},
		},
	};
	Solution solution;
	for (auto& matrix: input) {
		cout << "Input:" << endl << matrix << endl <<
			"Output: " << solution.spiralOrder(matrix) <<
			endl << endl;
	}
	return 0;
}
