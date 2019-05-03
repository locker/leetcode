#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<vector<int>>& triangle)
{
	int max_val = 0;
	for (auto row = triangle.begin(); row != triangle.end(); ++row) {
		for (auto it = row->begin(); it != row->end(); ++it)
			max_val = max(max_val, *it);
	}
	int width = 1;
	while ((max_val /= 10) > 0)
		++width;

	int indent = 2 + width * (triangle.size() - 1);
	out << '[' << endl;
	for (auto row = triangle.begin(); row != triangle.end(); ++row) {
		for (int i = 0; i < indent; ++i)
			out << ' ';
		indent -= width;
		out << '[';
		for (auto it = row->begin(); it != row->end(); ++it) {
			if (it != row->begin())
				out << ',';
			out << setw(width) << *it;
		}
		out << ']';
		if (row != triangle.end() - 1)
			out << ',';
		out << endl;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		int size = triangle.size();
		for (int i = size - 2; i >= 0; --i) {
			for (int j = 0; j < i + 1; ++j) {
				triangle[i][j] += min(triangle[i + 1][j],
						      triangle[i + 1][j + 1]);
			}
		}
		return triangle[0][0];
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{
			{10},
		}, // 10
		{
			  {10},
			{11, 7},
		}, // 17
		{
			    { 5},
			  { 3,11},
			{21,15, 4},
		}, // 20
		{
			   {2},
			  {3,4},
			 {6,5,7},
			{4,1,8,3},
		}, // 11
	};
	Solution solution;
	for (auto& triangle: input) {
		cout << "Input:" << endl << triangle << endl;
		cout << "Output: " << solution.minimumTotal(triangle) <<
			endl << endl;
	}
	return 0;
}
