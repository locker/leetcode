#include <iostream>

using namespace std;

class Solution {
public:
	int countNumbersWithUniqueDigits(int n) {
		if (n == 0)
			return 1; // number 0
		if (n > 10)
			return 0; // apparently

		// Account numbers 0-9.
		int count = 10;

		//
		// Account numbers 10 pow i <= x < 10 pow (i + 1).
		//
		// We can choose any of the numbers 1-9 for the first digit.
		// For the second and subsequent digits we can choose any of
		// the numbers 0-9 except the ones chosen for the preceding
		// digits.
		//
		int choices = 9;
		for (int i = 1; i < n; ++i ) {
			choices *= (10 - i);
			count += choices;
		}
		return count;
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n < 12; ++n)
		cout << n << " => " << solution.countNumbersWithUniqueDigits(n) << endl;
	return 0;
}
