#include <iostream>
#include <queue>

using namespace std;

class Solution {
public:
	int nthUglyNumber(int n) {
		// Ugly number bases.
		static const int base[] = {2, 3, 5};
		static const int base_count = sizeof(base) / sizeof(base[0]);

		// Next ugly number (declared 'unsigned' to avoid integer
		// overflow warning).
		unsigned val = 1;

		// Queue i contains ugly numbers generated by multiplying bases
		// with indexes <= i.
		queue<unsigned> next[base_count];
		for (int i = 0; i < base_count; ++i)
			next[i].push(base[i]);

		while (--n > 0) {
			// Pop the minimal number among the queues.
			int min_idx = 0;
			for (int i = 1; i < base_count; ++i) {
				if (next[i].front() < next[min_idx].front())
					min_idx = i;
			}
			val = next[min_idx].front();
			next[min_idx].pop();
			// Push numbers that can be generated from it.
			// Note, if we pop a value from queue i, we push
			// values only to queues >= i. This guarantees
			// uniqueness.
			for (int i = min_idx; i < base_count; ++i)
				next[i].push(val * base[i]);
		}
		return val;
	}
};

int main()
{
	Solution solution;
	for (int n = 1; n <= 1000;
	     n < 10 ? n += 1 : n < 100 ? n += 10 : n += 100) {
		cout << n << " => " << solution.nthUglyNumber(n) << endl;
	}
	return 0;
}