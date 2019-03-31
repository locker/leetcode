#include <iostream>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& matrix)
{
	out << '[';
	for (auto row = matrix.begin(); row != matrix.end(); ++row) {
		if (row != matrix.begin())
			out << ',';
		out << endl << "  [";
		for (auto elem = row->begin(); elem != row->end(); ++elem) {
			if (elem != row->begin())
				out << ',';
			out << *elem;
		}
		out << ']';
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	int uniquePathsWithObstacles(const vector<vector<int>>& obstacles) {
		int m = obstacles.size();
		int n = obstacles[0].size();
		//
		// At iteration i, array entry j will store the number
		// of unique paths from (i, j) to the finish.
		//
		// Extra entry (n + 1) always stores 0. It is needed to
		// avoid branching in the loop below.
		//
		// We don't really care about integer overflow. Use
		// 'unsigned' to suppress warnings, because 'integer'
		// overflow behavior is undefined.
		//
		vector<unsigned> count(n + 1, 0);
		// There's exactly one path from the finish point to itself.
		count[n - 1] = 1;
		for (int i = m - 1; i >= 0; i--) {
			for (int j = n - 1; j >= 0; j--) {
				if (obstacles[i][j] == 0) {
					// Account paths from down and right
					// neighbors.
					count[j] += count[j + 1];
				} else {
					// The cell is blocked, no paths going
					// through it.
					count[j] = 0;
				}
			}
		}
		return count[0];
	}
};

int main()
{
	vector<vector<int>> input[] = {
		{
			{0, 0},
		}, // 1
		{
			{0, 0},
			{0, 0},
		}, // 2
		{
			{0, 1},
			{0, 0},
		}, // 1
		{
			{0, 0, 0},
			{0, 1, 0},
			{0, 0, 0},
		}, // 2
		{
			{0, 1, 0},
			{0, 1, 0},
			{0, 0, 0},
		}, // 1
		{
			{0, 0, 0},
			{0, 0, 0},
			{1, 1, 0},
		}, // 3
		{
			{0, 0, 1},
			{0, 0, 1},
			{1, 0, 0},
		}, // 2
	};
	Solution solution;
	for (auto& obstacles: input) {
		cout << "Input:" << endl << obstacles << endl << "Output: " <<
			solution.uniquePathsWithObstacles(obstacles) <<
			endl << endl;
	}
	return 0;
}
