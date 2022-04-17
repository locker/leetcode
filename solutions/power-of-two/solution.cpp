#include <iostream>
#include <utility>

using namespace std;

class Solution {
public:
	bool isPowerOfTwo(int n) {
		return n > 0 && ((n - 1) & n) == 0;
	}
};

int main()
{
	pair<int, bool> test_data[] = {
		{0, false},
		{1, true},
		{2, true},
		{3, false},
		{4, true},
		{5, false},
		{16, true},
		{21, false},
		{-1, false},
		{-2, false},
		{-3, false},
		{-4, false},
	};
	bool success = true;
	Solution solution;
	for (const auto& [n, expected] : test_data) {
		bool result = solution.isPowerOfTwo(n);
		cout << n << " is " << (result ? "" : "not ") <<
			"a power of two" << endl;
		if (result != expected) {
			cout << "  ERROR: wrong result" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
