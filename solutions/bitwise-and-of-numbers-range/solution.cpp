#include <iostream>
#include <utility>

using namespace std;

class Solution {
public:
	int rangeBitwiseAnd(int m, int n) {
		int result = 0;
		// For each bit ...
		for (int i = 0; i < 31; ++i) {
			int b1 = (m >> i) & 1;
			int b2 = (n >> i) & 1;
			//
			// If bit i is unset in any of the numbers,
			// then it can't be set in the result.
			//
			if (b1 == 0 || b2 == 0)
				continue;
			//
			// Otherwise it is set in the result iff
			// the difference between the two numbers
			// is less than 2^i. Just take a look at
			// the table below to realize that:
			//
			// bits     value
			// 0 0 0 0 0    0
			// 0 0 0 0 1    1 | bit #0 diff < 1
			// 0 0 0 1 0    2  | bit #1
			// 0 0 0 1 1    3  | diff < 2
			// 0 0 1 0 0    4   |
			// 0 0 1 0 1    5   | bit #2
			// 0 0 1 1 0    6   | diff < 4
			// 0 0 1 1 1    7   |
			// 0 1 0 0 0    8    |
			// 0 1 0 0 1    9    |
			// 0 1 0 1 0   10    |
			// 0 1 0 1 1   11    | bit #3
			// 0 1 1 0 0   12    | diff < 8
			// 0 1 1 0 1   13    |
			// 0 1 1 1 0   14    |
			// 0 1 1 1 1   15    |
			// 1 0 0 0 0   16
			//
			if (n - m > (1 << i))
				continue;
			result |= 1 << i;
		}
		return result;
	}
};

int main()
{
	pair<int, int> input[] = {
		{0, 1}, // 0
		{1, 2}, // 0
		{1, 3}, // 0
		{3, 5}, // 0
		{4, 6}, // 4
		{5, 7}, // 4
		{10, 15}, // 8
		{10, 11}, // 10
	};
	Solution solution;
	for (const auto& p: input) {
		int m = p.first;
		int n = p.second;
		cout << '[' << m << ',' << n << ']' << " => " <<
			solution.rangeBitwiseAnd(m, n) << endl;
	}
	return 0;
}
