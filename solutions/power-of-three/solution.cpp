#include <iostream>
#include <limits>
#include <utility>

using namespace std;

class Solution {
private:
	static constexpr int calculateMaxPowerOfThree() {
		const long long max = numeric_limits<int>::max();
		long long val = 1;
		while (val * 3 < max)
			val *= 3;
		return val;
	}
public:
	bool isPowerOfThree(int n) {
		static constexpr int maxPowerOfThree = calculateMaxPowerOfThree();
		return n > 0 && maxPowerOfThree % n == 0;
	}
};

int main()
{
	const pair<int, bool> test_data[] = {
		{1, true},
		{-1, false},
		{27, true},
		{0, false},
		{9, true},
		{-9, false},
		{81, true},
	};
	bool success = true;
	Solution solution;
	for (const auto [n, expected] : test_data) {
		bool result = solution.isPowerOfThree(n);
		cout << n << (result ? " is " : " is not ") <<
			"a power of three" << endl;
		if (result != expected) {
			cout << "  ERROR: wrong answer" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
