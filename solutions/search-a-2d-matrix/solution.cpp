#include <iomanip>
#include <iostream>
#include <utility>
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
		int n = n_rows * n_cols;
		int begin = 0;
		int end = n;
		while (begin < end) {
			int mid = begin + (end - begin) / 2;
			int row = mid / n_cols;
			int col = mid % n_cols;
			int val = matrix[row][col];
			if (val == target)
				return true;
			if (val > target)
				end = mid;
			else
				begin = mid + 1;
		}
		return false;
	}
};

int main()
{
	pair<vector<vector<int>>, int> input[] = {
		{
			{},
			1, // false
		},
		{
			{{1}},
			1, // true
		},
		{
			{{2}},
			1, // false
		},
		{
			{{1, 2, 3}},
			2, // true
		},
		{
			{{1, 2, 4}},
			3, // false
		},
		{
			{
				{ 1, 10},
				{11, 20},
			},
			11, // true
		},
		{
			{
				{ 1, 10},
				{12, 20},
			},
			11, // false
		},
		{
			{
				{1,   3,  5,  7},
				{10, 11, 16, 20},
				{23, 30, 34, 50},
			},
			3, // true
		},
		{
			{
				{1,   3,  5,  7},
				{10, 11, 16, 20},
				{23, 30, 34, 50},
			},
			13, // false
		},
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& matrix = p.first;
		auto target = p.second;
		bool result = solution.searchMatrix(matrix, target);
		cout << "Input:" << endl <<
			"matrix = " << matrix << endl <<
			"target = " << target << endl <<
			"Output: " << (result ? "true" : "false") <<
			endl << endl;
	}
	return 0;
}
