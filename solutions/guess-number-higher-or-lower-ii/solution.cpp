#include <algorithm>
#include <iostream>
#include <limits>
#include <tuple>
#include <utility>

using namespace std;

namespace {

class Solution {
public:
	int getMoneyAmount(int n) {
		vector<vector<int>> dp(n + 1);
		dp[0].resize(n + 1);
		for (int i = 1; i <= n; ++i) {
			dp[i].resize(n - i + 1);
			if (i == 1)
				continue;
			for (int j = 0; j <= n - i; ++j) {
				dp[i][j] = numeric_limits<int>::max();
				for (int k = 1; k <= i; ++k) {
					dp[i][j] = min(dp[i][j],
						       j + k + max(dp[k - 1][j],
								   dp[i - k][j + k]));
				}
			}
		}
		return dp[n][0];
	}
};

} // namespace

int main()
{
	const tuple<int, int> test_data[] = {
		{1, 0},
		{2, 1},
		{10, 16},
		{15, 30},
		{16, 34},
		{17, 38},
	};
	bool success = true;
	Solution solution;
	for (const auto& [n, expected] : test_data) {
		int result = solution.getMoneyAmount(n);
		cout << "n = " << n << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
