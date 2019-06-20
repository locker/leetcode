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
	int maxProduct(const vector<int>& nums) {
		if (nums.empty())
			return 0;
		auto it = nums.begin();
		int curr_min = *it;
		int curr_max = *it;
		int max_product = *it;
		for (++it; it != nums.end(); ++it) {
			int n = *it;
			int next_min = n;
			int next_max = n;
			if (n > 0) {
				if (curr_max > 0)
					next_max *= curr_max;
				if (curr_min <= 0)
					next_min *= curr_min;
			} else if (n < 0) {
				if (curr_min <= 0)
					next_max *= curr_min;
				if (curr_max > 0)
					next_min *= curr_max;
			}
			curr_min = next_min;
			curr_max = next_max;
			max_product = max(max_product, curr_max);
		}
		return max_product;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{5}, // 5
		{-5}, // -5
		{-2, 0, -1}, // 0
		{-5, -5, -5}, // 25
		{2, 3, -2, 4}, // 6
		{2, 0, 1, -3, 0, 0, 2}, // 2
	};
	Solution solution;
	for (auto& nums: input)
		cout << nums << " => " << solution.maxProduct(nums) << endl;
	return 0;
}
