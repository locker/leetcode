#include <iostream>
#include <utility>

using namespace std;

class Solution {
public:
	bool isPowerOfFour(int n) {
		if (n <= 0)
			return false;
		if (((n - 1) & n) != 0)
			return false;
		int c = 0;
		while (n != 0) {
			n >>= 1;
			++c;
		}
		return c % 2 == 1;
	}
};

int main()
{
	const pair<int, bool> test_data[] = {
		{-1, false},
		{0, false},
		{1, true},
		{2, false},
		{4, true},
		{5, false},
		{8, false},
		{16, true},
		{32, false},
		{64, true},
		{65, false},
		{128, false},
		{256, true},
	};
	bool success = true;
	Solution solution;
	for (const auto [n, expected] : test_data) {
		bool result = solution.isPowerOfFour(n);
		cout << n << (result ? " is " : " isn't ") <<
			"a power of four" << endl;
		if (result != expected) {
			cout << "  ERROR: wrong" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
