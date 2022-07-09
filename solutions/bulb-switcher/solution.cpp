#include <cmath>
#include <iostream>
#include <utility>

using namespace std;

class Solution {
public:
	int bulbSwitch(int n) {
		// Every number has an even number of factors unless it's
		// a perfect square:
		//
		// 6: 1 * 6, 2 * 3
		// 16: 1 * 16, 2 * 8, 4 * 4
		// 20: 1 * 20, 2 * 10, 4 * 5
		// 25: 1 * 25, 5 * 5
		//
		// So only those bulbs will be turned on after n iterations
		// whose numbers are perfect squares.
		return sqrt(n);
	}
};

int main()
{
	const pair<int, int> test_data[] = {
		{0, 0},
		{1, 1},
		{2, 1},
		{3, 1},
		{4, 2},
		{5, 2},
		{6, 2},
		{7, 2},
		{8, 2},
		{9, 3},
	};
	bool success = false;
	Solution solution;
	for (const auto& [n, expected] : test_data) {
		int result = solution.bulbSwitch(n);
		cout << n << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
