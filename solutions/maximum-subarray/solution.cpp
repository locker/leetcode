#include <algorithm>
#include <iostream>
#include <limits>
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
	int maxSubArray(const vector<int>& nums) {
		int size = nums.size();
		if (size == 0)
			return 0;
		int max_sum = numeric_limits<int>::min();
		int sum1 = 0; // max sum including the last negative
		int sum2 = 0; // sum since the last negative
		for (int i = 0; i < size; ++i) {
			if (nums[i] < 0) {
				sum1 = max(sum1, sum2) + nums[i];
				sum2 = 0;
				max_sum = max(max_sum, sum1);
			} else {
				sum1 += nums[i];
				sum2 += nums[i];
				max_sum = max({max_sum, sum1, sum2});
			}
		}
		return max_sum;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{1}, // 1
		{-1}, // -1
		{-3, -1, -2}, // -1
		{1, 3, 2}, // 6
		{1, -1, 1, -1}, // 1
		{1, 2, 3, -5, 1, 2}, // 6
		{-2, 1, -3, 4, -1, 2, 1, -5, 4}, // 6
	};
	Solution solution;
	for (auto& nums: input)
		cout << nums << " => " << solution.maxSubArray(nums) << endl;
	return 0;
}
