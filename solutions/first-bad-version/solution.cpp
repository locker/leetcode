#include <iostream>
#include <utility>

using namespace std;

int bad_version;

bool isBadVersion(int version) {
	return version >= bad_version;
}

class Solution {
public:
	int firstBadVersion(int n) {
		unsigned int b = 1;
		unsigned int e = static_cast<unsigned int>(n) + 1;
		while (b != e) {
			unsigned int m = b / 2 + e / 2;
			if (isBadVersion(m)) {
				e = m;
			} else {
				b = m + 1;
			}
		}
		return b;
	}
};

int main()
{
	pair<int, int> test_data[] = {
		{1, 1},
		{3, 3},
		{3, 1},
		{5, 4},
		{8, 1},
		{8, 2},
		{8, 3},
		{8, 4},
		{8, 5},
		{8, 6},
		{8, 7},
		{8, 8},
		{9, 1},
		{9, 4},
		{9, 5},
		{9, 9},
	};
	bool success = true;
	Solution solution;
	for (const auto& [n, expected] : test_data) {
		bad_version = expected;
		int result = solution.firstBadVersion(n);
		cout << "n = " << n << ", bad = " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
