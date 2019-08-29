#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
public:
	int minSteps(int n) {
		// Array entry k stores the min number of steps required
		// to produce exactly (k + 1) characters; dp[0] = 0 since
		// we start with one character.
		vector<int> dp(n, numeric_limits<int>::max());
		dp[0] = 0;
		for (int i = 1; i < n; ++i) {
			// We can produce i * j characters from i characters,
			// j >= 2, by copying all characters and pasting them
			// (j - 1) times.
			for (int j = 2; i * j <= n; ++j) {
				dp[i * j - 1] = min(dp[i * j - 1],
						    dp[i - 1] + 1 + (j - 1));
			}
		}
		return dp[n - 1];
	}
};

int main()
{
	Solution solution;
	for (int n = 1; n <= 100; n < 10 ? ++n : n += 10)
		cout << n << " => " << solution.minSteps(n) << endl;
	return 0;
}
