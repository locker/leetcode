#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
	int numSquares(int n) {
		// Entry i stores true if we've already found the least
		// number of squares summing to i.
		vector<bool> done(n + 1);

		//
		// BFS queue.
		//
		// At level i we mark all numbers that can be represented as
		// sums of i squares. We use -1 as the end of level marker.
		// Once we've marked the given number, we are done.
		//
		queue<int> todo;
		todo.push(0);
		todo.push(-1);

		for (int level = 0; ; ) {
			int curr = todo.front();
			todo.pop();
			if (curr == -1) {
				// End of level. Proceed to the next one.
				++level;
				todo.push(-1);
				continue;
			}
			if (done[curr]) {
				// Already seen this one, no need to repeat.
				continue;
			}
			done[curr] = true;

			// Append all numbers <= n that are sums of this number
			// and a perfect square to the queue as they belong to
			// the next BFS level.
			for (int i = 1; ; ++i) {
				long long next = (long long) i * i + curr;
				if (next == n) {
					// Found the given number, return.
					return level + 1;
				}
				if (next > n)
					break;
				todo.push(next);
			}
		}
	}
};

int main()
{
	Solution solution;
	for (int i = 1; i <= 100; i < 20 ? ++i : i += 10)
		cout << i << " => " << solution.numSquares(i) << endl;
	return 0;
}
