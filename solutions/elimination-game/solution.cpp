#include <iostream>
#include <tuple>

using namespace std;

namespace {

class Solution {
	int helper(int min, int max, int step, bool left) {
		if (min + step > max)
			return left ? min : max;
		if (left) {
			min += step;
			step *= 2;
			max = min + (max - min) / step * step;
		} else {
			max -= step;
			step *= 2;
			min = max - (max - min) / step * step;
		}
		return helper(min, max, step, !left);
	}
public:
	int lastRemaining(int n) {
		return helper(1, n, 1, true);
	}
};

} // namespace

int main()
{
	const tuple<int, int> test_data[] = {
		{1, 1},
		{2, 2},
		{3, 2},
		{4, 2},
		{5, 2},
		{6, 4},
		{7, 4},
		{8, 6},
		{9, 6},
	};
	bool success = true;
	Solution solution;
	for (const auto& [n, expected] : test_data) {
		int result = solution.lastRemaining(n);
		cout << n << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
