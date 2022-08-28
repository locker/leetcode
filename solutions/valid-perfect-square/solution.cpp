#include <iostream>
#include <utility>

using namespace std;

class Solution {
public:
	bool isPerfectSquare(int num) {
		if (num == 1)
			return true;
		int64_t lo = 1;
		int64_t hi = num;
		while (hi > lo) {
			int64_t mid = lo + (hi - lo) / 2;
			int64_t square = mid * mid;
			if (square == num)
				return true;
			if (square > num)
				hi = mid;
			else
				lo = mid + 1;
		}
		return false;
	}
};

int main()
{
	const pair<int, bool> test_data[] = {
		{1, true},
		{2, false},
		{3, false},
		{4, true},
		{7, false},
		{9, true},
		{14, false},
		{16, true},
	};
	Solution solution;
	bool success = true;
	for (auto [num, expected] : test_data) {
		bool result = solution.isPerfectSquare(num);
		cout << num << " => " << (result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: wrong result" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
