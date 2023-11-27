#include <iostream>
#include <tuple>

using namespace std;

namespace {

class Solution {
public:
	int findNthDigit(int n) {
		int digit_count = 1;
		long long base = 1;
		long long number_count = 9;
		while (n > number_count * digit_count) {
			base *= 10;
			n -= number_count * digit_count;
			number_count *= 10;
			++digit_count;
		}
		--n;
		int num = base + n / digit_count;
		for (int digit = digit_count - n % digit_count - 1; digit > 0; --digit)
			num /= 10;
		return num % 10;
	}
};

} // namespace

int main()
{
	const tuple<int, int> test_data[] = {
		{1, 1},
		{3, 3},
		{5, 5},
		{9, 9},
		{11, 0},
		{12, 1},
		{13, 1},
		{14, 1},
		{15, 2},
		{16, 1},
		{17, 3},
	};
	bool success = true;
	Solution solution;
	for (const auto& [n, expected] : test_data) {
		int result = solution.findNthDigit(n);
		cout << n << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
