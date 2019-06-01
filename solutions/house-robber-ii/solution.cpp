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
	int rob(const vector<int>& nums) {
		// First, let's simplify the task and assume that houses
		// are not arranged in a circle.
		//
		// Let n be the number of houses we can rob. Let f(i) be
		// the max amount of money we could rob tonight if there
		// were only houses i, i+1, ..., n-1, i = 0, 1, ..., n-1.
		// We want to find f(0).
		//
		// Apparently,
		//
		//   f(n-1) = x[n-1]
		//   f(n-2) = max(x[n-2], x[n-1])
		//   f(i) = max(f(i+1), x[i] + f(i+2)), i = 0, 1, ... n-3
		//
		// If houses are arranged in a circle, then if we choose
		// to rob house 0, we can't rob house n-1 and vice versa.
		// Hence we should choose max of f(0..n-2) and f(1..n-1).
		//
		int n = nums.size();
		if (n == 0)
			return 0;
		if (n == 1)
			return nums[0];
		if (n == 2)
			return max(nums[0], nums[1]);

		int f[2];
		f[(n - 2) % 2] = nums[n - 2];
		f[(n - 3) % 2] = max(nums[n - 3], nums[n - 2]);

		int g[2];
		g[(n - 1) % 2] = nums[n - 1];
		g[(n - 2) % 2] = max(nums[n - 2], nums[n - 1]);

		for (int i = n - 4; i >= 0; --i) {
			int val;
			val = max(f[(i + 1) % 2], nums[i] + f[(i + 2) % 2]);
			f[i % 2] = val;
			val = max(g[(i + 2) % 2], nums[i + 1] + g[(i + 3) % 2]);
			g[(i + 1) % 2] = val;
		}
		return max(f[0], g[1]);
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{3}, // 3
		{4, 5}, // 5
		{2, 3, 2}, // 3
		{2, 3, 4}, // 4
		{1, 2, 3, 1}, // 4
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.rob(nums) << endl;
	return 0;
}
