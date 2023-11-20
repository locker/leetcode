#include <iostream>
#include <tuple>

using namespace std;

namespace {

int pick;

int guess(int num)
{
	if (num > pick)
		return -1;
	if (num < pick)
		return 1;
	return 0;
}

class Solution {
public:
	int guessNumber(int n) {
		int b = 1;
		int e = n;
		while (b <= e) {
			int m = b + (e - b) / 2;
			int r = guess(m);
			if (r == 0)
				return m;
			if (r > 0)
				b = m + 1;
			else
				e = m - 1;
		}
		return b;
	}
};

} // namespace

int main()
{
	const tuple<int, int> test_data[] = {
		{10, 6},
		{1, 1},
		{2, 1},
		{123, 1},
		{42, 42},
		{50, 26},
		{50, 25},
		{50, 24},
	};
	bool success = true;
	Solution solution;
	for (const auto& [n, p] : test_data) {
		cout << "n = " << n << ", pick = " << p << endl;
		pick = p;
		int guess = solution.guessNumber(n);
		if (guess != pick) {
			cout << "  ERROR: guessed " << guess << endl;
			success = false;
		}
	}
	return success ? 0 : -1;
}
