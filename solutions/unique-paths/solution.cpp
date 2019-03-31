#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
	int uniquePaths(int m, int n) {
		if (m < n)
			return uniquePaths(n, m);
		if (n == 1)
			return 1;
		//
		// At iteration i, array entry j will store the number
		// of unique paths from (i, j) to the finish.
		//
		vector<int> count(n, 1);
		for (int i = 1; i < m; ++i) {
			for (int j = 1; j < n; ++j)
				count[j] += count[j - 1];
		}
		return count[n - 1];
	}
};

int main()
{
	pair<int, int> input[] = {
		{1, 1}, // 1
		{1, 2}, // 1
		{3, 1}, // 1
		{3, 2}, // 3
		{4, 4}, // 20
		{7, 3}, // 28
		{4, 6}, // 56
	};
	Solution solution;
	for (auto& p: input) {
		cout << p.first << 'x' << p.second << " => " <<
			solution.uniquePaths(p.first, p.second) << endl;
	}
	return 0;
}
