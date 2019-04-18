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
		out << endl;
		out << "  " << *it;
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	void setZeroes(vector<vector<int>>& matrix) {
		if (matrix.empty())
			return;
		bool zero_first_row = false;
		bool zero_first_col = false;
		int n_rows = matrix.size();
		int n_cols = matrix[0].size();
		for (int i = 0; i < n_rows; ++i) {
			for (int j = 0; j < n_cols; ++j) {
				if (matrix[i][j] == 0) {
					matrix[0][j] = 0;
					matrix[i][0] = 0;
					if (i == 0)
						zero_first_row = true;
					if (j == 0)
						zero_first_col = true;
				}
			}
		}
		for (int i = 1; i < n_rows; ++i) {
			if (matrix[i][0] == 0) {
				for (int j = 1; j < n_cols; ++j)
					matrix[i][j] = 0;
			}
		}
		for (int j = 1; j < n_cols; ++j) {
			if (matrix[0][j] == 0) {
				for (int i = 1; i < n_rows; ++i)
					matrix[i][j] = 0;
			}
		}
		if (zero_first_row) {
			for (int j = 0; j < n_cols; ++j)
				matrix[0][j] = 0;
		}
		if (zero_first_col) {
			for (int i = 0; i < n_rows; ++i)
				matrix[i][0] = 0;
		}
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{
		},
		{
			{1},
		},
		{
			{1, 0},
		},
		{
			{0},
			{1},
		},
		{
			{1, 0},
			{0, 1},
		},
		{
			{1, 1, 1},
			{1, 0, 1},
			{1, 1, 1},
		},
		{
			{0, 1, 2, 0},
			{3, 4, 5, 2},
			{1, 3, 1, 5},
		},
		{
			{1, 0, 1, 1},
			{0, 1, 1, 1},
			{1, 1, 0, 1},
			{1, 1, 1, 0},
		},
	};
	Solution solution;
	for (auto& matrix: input) {
		cout << "Input:" << endl << matrix << endl;
		solution.setZeroes(matrix);
		cout << "Output:" << endl << matrix << endl;
	}
	return 0;
}
