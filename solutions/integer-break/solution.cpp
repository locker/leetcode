#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
private:
	static vector<int> cache;
public:
	int integerBreak(int n) {
		cache.resize(max(static_cast<int>(cache.size()), n + 1));
		if (n <= 2)
			return 1;
		if (cache[n] != 0)
			return cache[n];
		int result = 0;
		for (int i = 1; i <= n / 2; ++i)
			result = max({result, i * (n - i), i * integerBreak(n - i)});
		cache[n] = result;
		return result;
	}
};

vector<int> Solution::cache;

int main()
{
	const pair<int, int> test_data[] = {
		{2, 1},
		{3, 2},
		{4, 4},
		{5, 6},
		{10, 36},
	};
	bool success = true;
	Solution solution;
	for (auto [n, expected] : test_data) {
		int result = solution.integerBreak(n);
		cout << n << " => " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
