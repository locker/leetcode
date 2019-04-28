#include <iostream>

using namespace std;

class Solution {
	int trailingZeros(long long n) {
		int result = 0;
		while (n > 0)
			result += (n /= 5);
		return result;
	}
public:
	int preimageSizeFZF(int k) {
		//
		// A trailing zero can only be produced by multiplying 2 by 5.
		// As there's always more 5s than 2s in a factorial, the number
		// of trailing zeros equals the number of 5s in the factorial
		// product.
		//
		// If there's at least one number n such that n! has k trailing
		// zeros, then there are exactly 5 such numbers: (n // 5) * 5,
		// (n // 5) * 5 + 1, ..., (n // 5) * 5 + 4.
		//
		// So all we need to do is check if there's a number whose
		// factorial has exactly k trailing zeros.
		//
		// Number n has at least n // 5 and at most n trailing zeros
		// so the min/max numbers to look at are k and k * 5. Therefore
		// we can do binary search.
		//
		long long begin = k;
		long long end = k * 5LL + 1;

		while (begin < end) {
			long long mid = begin + (end - begin) / 2;
			int count = trailingZeros(mid);
			if (count == k)
				return 5;
			if (count > k)
				end = mid;
			else
				begin = mid + 1;
		}
		return 0;
	}
};

int main()
{
	Solution solution;
	for (int k = 0; k <= 100; k < 15 ? ++k : k += 5)
		cout << k << " => " << solution.preimageSizeFZF(k) << endl;
	return 0;
}
