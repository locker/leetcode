#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <utility>

using namespace std;

class Solution {
	unsigned divide_exp(unsigned dividend, unsigned divisor) {
		assert(dividend >= divisor);
		unsigned exp = 0;
		while (dividend >> (exp + 1) > divisor)
			++exp;
		return exp;
	}
public:
	int divide(int dividend_signed, int divisor_signed) {
		assert(divisor_signed != 0);
		bool negate = false;
		unsigned dividend = dividend_signed;
		if (dividend_signed < 0) {
			dividend = -dividend;
			negate = !negate;
		}
		unsigned divisor = divisor_signed;
		if (divisor_signed < 0) {
			divisor = -divisor;
			negate = !negate;
		}
		unsigned quotinent = 0;
		while (dividend >= divisor) {
			unsigned exp = divide_exp(dividend, divisor);
			quotinent += 1 << exp;
			dividend -= divisor << exp;
		}
		if (!negate) {
			return std::min(
				quotinent,
				(unsigned)numeric_limits<int>::max());
		} else {
			return -quotinent;
		}
	}
};

int main()
{
	pair<int, int> test_data[] = {
		{4, 4},
		{1, 3},
		{10, 3},
		{100, 5},
		{7, -3},
		{-20, -3},
		{-2147483648, -1},
		{-2147483648, -2147483648},
	};
	bool success = true;
	Solution solution;
	for (const auto& [dividend, divisor] : test_data) {
		int result = solution.divide(dividend, divisor);
		cout << dividend << " / " << divisor << " = " <<
			result << endl;
		int expected = std::min(
			(long long)dividend / divisor,
			(long long)numeric_limits<int>::max());
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
