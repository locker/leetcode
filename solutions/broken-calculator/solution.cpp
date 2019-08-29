#include <iostream>
#include <utility>

using namespace std;

class Solution {
public:
	int brokenCalc(int X, int Y) {
		// Obviously, instead of transforming X we can transform Y by
		// either incrementing it or dividing it by 2 (if it's even, of
		// course). If at the current step Y is odd, then we have no
		// choice but increment it. Otherwise we divide it until it's
		// less than X, because this way it approaches X as fast as
		// possible. Finally, when it becomes less than X, we increment
		// it to match X.
		int count = 0;
		while (X < Y) {
			if (Y % 2 == 1) {
				++Y;
				++count;
			}
			Y /= 2;
			++count;
		}
		count += X - Y;
		return count;
	}
};

int main()
{
	pair<int, int> input[] = {
		{1, 1}, // 0: 1 = 1
		{2, 3}, // 2: 2 * 2 - 1 = 3
		{6, 7}, // 4: (6 - 1 - 1) * 2 - 1
		{5, 8}, // 2: (5 - 1) * 2
		{3, 10}, // 3: (3 * 2 - 1) * 2
		{1024, 1}, // 1023: 1024 - 1 - 1 - ... - 1 = 1
	};
	Solution solution;
	for (auto& p: input) {
		cout << "Input: X = " << p.first << ", Y = " << p.second << endl <<
			"output: " << solution.brokenCalc(p.first, p.second) << endl;
	}
	return 0;
}
