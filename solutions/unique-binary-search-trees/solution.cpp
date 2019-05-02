#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int numTrees(int n) {
		// Array entry i stores the number of ways to build
		// a binary search tree of i elements.
		vector<int> num(n + 1);
		num[0] = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < i; ++j)
				num[i] += num[j] * num[i - j - 1];
		}
		return num[n];
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n <= 10; ++n)
		cout << n << " => " << solution.numTrees(n) << endl;
	return 0;
}
