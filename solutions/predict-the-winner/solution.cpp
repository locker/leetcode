#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	bool PredictTheWinner(const vector<int>& nums) {
		//
		// Let f(i, j) and g(i, j) be max scores of players one and two
		// respectively in case the game is played on sub-array a[i:j],
		// 0 <= i <= j <= n. Apparently,
		//
		//   f(a[i:j]) + g(a[i:j]) = SUM(a[k]) = s(i, j)
		//                            i<=k<=j
		//
		//   f(i, j) = MAX(a[i] + g(i + 1, j), a[j] + g(i, j - 1))
		//           = MAX(s(i, j) - f(i + 1, j), s(i, j) - f(i, j - 1))
		//           = s(i, j) - MIN(f(i + 1, j), f(i, j - 1))
		//
		//   s(i, j) = SUM(a[k]) - SUM(a[k]) = S(j) - S(i)
		//              0<=k<=j     0<=k<=i
		//
		int size = nums.size();
		if (size == 0)
			return true;

		// Pre-compute sub-array sums so that we can find the sum of
		// any sub-array a[i:j] as sums[j] - sums[i].
		vector<int> sums(nums);
		for (int i = 1; i < size; ++i)
			sums[i] += sums[i - 1];

		// Stores values of f for all possible sub-arrays of length
		// sub_size. Initially sub_size is 1 so dp equals nums.
		vector<int> dp(nums);
		for (int sub_size = 2; sub_size <= size; ++sub_size) {
			int prev = dp[size - sub_size + 1]; // f(i + 1, j)
			for (int first = size - sub_size; first >= 0; --first) {
				int last = first + sub_size - 1;
				int sum = sums[last];
				if (first > 0)
					sum -= sums[first - 1];
				int curr = dp[first]; // f(i, j - 1)
				dp[first] = sum - min(curr, prev);
				prev = curr;
			}
		}
		return dp[0] >= sums[size - 1] - dp[0];
	}
};

int main()
{
	vector<int> input[] = {
		{}, // true
		{1}, // true
		{1, 2}, // true
		{1, 2, 3}, // true
		{1, 5, 2}, // false
		{1, 5, 233, 7}, // true
	};
	Solution solution;
	for (const auto& nums: input) {
		cout << nums << " => " << (solution.PredictTheWinner(nums) ?
					   "true" : "false") << endl;
	}
	return 0;
}
