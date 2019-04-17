#include <iostream>

using namespace std;

class Solution {
public:
	int climbStairs(int n) {
		//
		// At the i-th loop iteration 'curr' stores the number
		// of ways to climb a staircase of i steps while 'prev'
		// stores the number of ways to climb a staircase of i-1
		// steps. Climbing a staircase of i+1 steps is equivalent
		// to either taking one step after climbing i steps or
		// taking two steps after climbing i-1 steps.
		//
		int curr = 1;
		int prev = 0;
		for (int i = 0; i < n; ++i) {
			int next = curr + prev;
			prev = curr;
			curr = next;
		}
		return curr;
	}
};

int main()
{
	Solution solution;
	for (int n = 1; n <= 10; ++n)
		cout << n << " => " << solution.climbStairs(n) << endl;
	return 0;
}
