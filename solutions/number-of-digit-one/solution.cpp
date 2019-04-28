#include <iostream>

using namespace std;

class Solution {
public:
	int countDigitOne(int n) {
		if (n == 0)
			return 0;

		// Let k be 0-base index of the digit we are currently
		// looking at. We start from the rightmost digit (k = 0).

		// Number of 1s in numbers < 10^k, calculated recurrently:
		// f(10^k) = f(10^k) * 10 + 10^(k-1)
		int count_pow_10_k = 0;
		// Number of 1s in numbers less than or equal to the number
		// composed of the last k digits of n.
		int count = 0;
		// Equals n / (10^k).
		int m = n;
		// Equals 10^k.
		int pow_10_k = 1;

		while (true) {
			int digit = m % 10;

			// Account 1s in numbers < digit * 10^k.
			count += digit * count_pow_10_k;
			// Take into account the leading 1 in numbers
			// between 10^k and 2 * 10^k.
			if (digit > 1)
				count += pow_10_k;
			if (digit == 1)
				count += n - m * pow_10_k + 1;

			m /= 10;
			if (m == 0)
				break;

			// Proceed to the next digit.
			count_pow_10_k = count_pow_10_k * 10 + pow_10_k;
			pow_10_k *= 10;
		}
		return count;
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n <= 1000;
	     n < 10 ? ++n :
	     (n < 50 ? n += 5 :
	      (n < 100 ? n += 10 :
	       (n < 500 ? n += 50 : n += 100)))) {
		cout << n << " => " << solution.countDigitOne(n) << endl;
	}
	return 0;
}
