#include <iostream>

using namespace std;

class Solution {
public:
	int arrangeCoins(int n) {
		if (n <= 1)
			return n;
		// In order to form a k step staircase, we need (1 + k) * k / 2
		// coins. Solving a qudratic equation would be way too boring.
		// Let's do binary search instead.
		int l = 1;
		int r = n;
		int steps = 0;
		while (l < r) {
			int m = l + (r - l) / 2;
			// Avoid integet overflow.
			long long coins = static_cast<long long>(m) * (m + 1) / 2;
			if (n >= coins) {
				steps = m;
				l = m + 1;
			} else {
				r = m;
			}
		}
		return steps;
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n <= 100; n < 10 ? ++n : n += 5)
		cout << n << " => " << solution.arrangeCoins(n) << endl;
	return 0;
}
