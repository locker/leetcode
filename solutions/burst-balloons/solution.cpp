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
	int maxCoins(const vector<int>& nums) {
		int size = nums.size();
		if (size == 0)
			return 0;

		// dp[i][j] stores max coins that can be collected from array
		// [i, i + j) provided it is burst before adjacent arrays.
		vector<vector<int>> dp(size);
		for (int i = 0; i < size; ++i)
			dp[i].resize(size - i);

		for (int len = 1; len <= size; ++len) {
			for (int begin = 0; begin <= size - len; ++begin) {
				int end = begin + len;
				// Consider sub array [begin, end). Suppose
				// balloon mid is burst last. Then max coins
				// that can be collected from this sub array
				// can be calculated recurrently, by summing
				// max coins that can be collected from sub
				// arrays [begin, mid) and [mid + 1, end) and
				// coins collected from balloon mid (keep in
				// mind we assume it is burst last and this sub
				// array is burst before adjacent sub arrays).
				for (int mid = begin; mid < end; ++mid) {
					int val = nums[mid];
					if (begin > 0)
						val *= nums[begin - 1];
					if (end < size)
						val *= nums[end];
					if (mid > begin)
						val += dp[begin][mid - begin - 1];
					if (mid < end - 1)
						val += dp[mid + 1][end - mid - 2];
					if (dp[begin][len - 1] < val)
						dp[begin][len - 1] = val;
				}
			}
		}
		return dp[0][size - 1];
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{4}, // 4
		{4, 5}, // 25
		{3, 5, 8}, // 152
		{3, 1, 5, 8}, // 167
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.maxCoins(nums) << endl;
	return 0;
}
