#include <iostream>
#include <utility>
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
	int minSubArrayLen(int s, const vector<int>& nums) {
		int len = nums.size();
		// Window boundaries in the nums array.
		int begin = 0, end = 0;
		// Sum of numbers in the window.
		int sum = 0;
		// Minimum window summing to >= s.
		int min_win_len = 0;
		while (begin < len) {
			// Expand the window to the right until
			// it sums to >= s.
			while (end < len && sum < s)
				sum += nums[end++];
			if (sum < s)
				break;
			// Now shrink the window from the left to
			// min sub-window summing to >= s.
			while (sum - nums[begin] >= s)
				sum -= nums[begin++];
			int win_len = end - begin;
			if (min_win_len == 0 || min_win_len > win_len)
				min_win_len = win_len;
			// Proceed to the next window.
			sum -= nums[begin++];
		}
		return min_win_len;
	}
};

int main()
{
	pair<int, vector<int>> input[] = {
		{1, {}}, // 0
		{1, {1}}, // 1
		{2, {1}}, // 0
		{1, {1, 2}}, // 1
		{2, {1, 1}}, // 2
		{4, {1, 2}}, // 0
		{5, {1, 2, 3}}, // 2
		{5, {1, 1, 2, 1}}, // 4
		{6, {3, 1, 2, 1, 1}}, // 3
		{7, {2, 3, 1, 2, 4, 3}}, // 2
		{80, {10, 5, 13, 4, 8, 4, 5, 11, 14, 9, 16, 10, 20, 8}}, // 6
	};
	Solution solution;
	for (const auto& p: input) {
		auto s = p.first;
		const auto& nums = p.second;
		cout << "Input: s = " << s << ", nums = " << nums << endl <<
			"Output: " << solution.minSubArrayLen(s, nums) << endl;
	}
	return 0;
}
