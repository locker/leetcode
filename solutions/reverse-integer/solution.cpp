#include <iostream>
#include <limits>

using namespace std;

class Solution {
public:
	int reverse(int x) {
		int max = numeric_limits<int>::max();
		int min = numeric_limits<int>::min();

		if (x == min)
			return 0;

		int div = 1;
		for (int i = x > 0 ? x : -x; i >= 10; i /= 10)
			div *= 10;

		int mult = 1;
		int result = 0;
		while (true) {
			int i = (x / div) % 10;
			if (i >= 0) {
				if (i > max / mult)
					return 0;
				i *= mult;
				if (result > max - i)
					return 0;
			} else {
				if (i < min / mult)
					return 0;
				i *= mult;
				if (result < min - i)
					return 0;
			}
			result += i;
			div /= 10;
			if (div == 0)
				break;
			mult *= 10;
		}
		return result;
	}
};

int main()
{
	auto solution = Solution();
	int input[] = {
		-2147483648, -2147483642, -1234567899, -2147483012, -12345, -1,
		0, 1, 12345, 2147483012, 1234567899, 2147483642, 2147483647,
	};
	for (auto x: input)
		cout << x << " -> " << solution.reverse(x) << endl;
	return 0;
}
