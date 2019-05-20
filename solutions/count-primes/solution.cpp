#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int countPrimes(int n) {
		if (n <= 2)
			return 0;

		// Array entry i stores true if number i is prime.
		// We first assume that all numbers are prime.
		// As we iterate over numbers < n we clear entries
		// corresponding to numbers that are found to be
		// composite.
		vector<bool> is_prime(n, true);

		int count = 0;
		for (int i = 2; i < n; ++i) {
			if (!is_prime[i])
				continue;
			// The number is prime. Account it and clear
			// all entries in the array corresponding to
			// numbers that can be produced by multiplying
			// it by any other number in the given range.
			// Note, we don't need to consider numbers < i,
			// because such products have been marked on
			// previous iterations.
			++count;
			for (int j = i; (long long) i * j < n; ++j)
				is_prime[i * j] = false;
		}
		return count;
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n <= 1000;
	     n < 10 ? n += 1 : n < 100 ? n += 10 : n += 100) {
		cout << n << " => " << solution.countPrimes(n) << endl;
	}
	return 0;
}
