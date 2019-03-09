#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ", ";
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		int size = nums.size();
		if (size < 3)
			return 0;
		sort(nums.begin(), nums.end());
		int closest_sum = nums[0] + nums[1] + nums[2];
		int min_delta = closest_sum - target;
		if (min_delta < 0)
			min_delta = -min_delta;
		for (int k = 0; k < size - 2; ++k) {
			for (int i = k + 1, j = size - 1; i < j; ) {
				int sum = nums[i] + nums[j] + nums[k];
				int delta;
				if (sum >= target) {
					delta = sum - target;
					--j;
				}
				if (sum <= target) {
					delta = target - sum;
					++i;
				}
				if (delta < min_delta) {
					min_delta = delta;
					closest_sum = sum;
				}
				if (delta == 0)
					return target;
			}
		}
		return closest_sum;
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{{}, 2}, // 0
		{{1}, 1}, // 0
		{{1, 2}, 3}, // 0
		{{1, 2, 3}, 6}, // 6
		{{-1, 2, 1, -4}, 1}, // 2
		{{5, 30, 5, 5, 14, 3}, 25}, // 24
	};
	Solution solution;
	for (auto p: input) {
		cout << p.first << ", " << p.second << " => ";
		cout << solution.threeSumClosest(p.first, p.second) << endl;
	}
	return 0;
}
