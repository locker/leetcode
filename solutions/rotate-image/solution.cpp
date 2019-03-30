#include <iomanip>
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
		out << setw(2) << *it;
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
	void rotate(vector<vector<int>>& matrix) {
		int n = matrix.size();
		for (int i = 0; i < n / 2; ++i) {
			for (int j = i; j < n - i - 1; ++j) {
				//         i,         j =>         j, n - i - 1
				//         j, n - i - 1 => n - i - 1, n - j - 1
				// n - i - 1, n - j - 1 => n - j - 1,         i
				// n - j - 1,         i =>         i,         j
				int& a = matrix[i][j];
				int& b = matrix[j][n - i - 1];
				int& c = matrix[n - i - 1][n - j - 1];
				int& d = matrix[n - j - 1][i];
				int a1 = a, b1 = b, c1 = c, d1 = d;
				a = d1, b = a1, c = b1, d = c1;
			}
		}
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
			{3, 4},
		},
		{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9},
		},
		{
			{ 5,  1,  9, 11},
			{ 2,  4,  8, 10},
			{13,  3,  6,  7},
			{15, 14, 12, 16}
		},
	};
	Solution solution;
	for (auto& matrix: input) {
		cout << "Input:" << endl << matrix << endl;
		solution.rotate(matrix);
		cout << "Output:" << endl << matrix << endl << endl;
	}
	return 0;
}
