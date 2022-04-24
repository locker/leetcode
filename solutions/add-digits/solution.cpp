#include <iostream>
#include <utility>

using namespace std;

class Solution {
public:
	int addDigits(int num) {
		if (num == 0)
			return 0;
		int x = num % 9;
		return x != 0 ? x : 9;
	}
};

int main()
{
	const pair<int, int> test_data[] = {
		{0, 0},
		{1, 1},
		{5, 5},
		{15, 6},
		{38, 2},
		{99, 9},
		{100, 1},
		{998, 8},
	};
	bool success = true;
	Solution solution;
	for (const auto& [num, expected] : test_data) {
		int result = solution.addDigits(num);
		cout << num << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
