#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T> v)
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
	int minPatches(vector<int>& nums, int n) {
		int size = nums.size();

		sort(nums.begin(), nums.end());

		// Currently checked number.
		long long i = 1;

		// Index of the min element in nums array that haven't been
		// accounted in the sum yet.
		int j = 0;

		// Number of elements that have been added to the array.
		int k = 0;

		// Loop invariant: all numbers < i can be formed by the sum
		// of some elements of nums array.
		while (i <= n) {
			if (j < size && nums[j] <= i) {
				// If we can form any number < i by summing
				// some elements of nums, we can form any
				// number < i+x where x is some number in
				// the array <= x.
				i += nums[j++];
			} else {
				// We can't form i. The best number to add
				// is i itself, because it will cover max
				// number of elements: i, i+1, ..., i+i-1.
				i += i;
				++k;
			}
		}
		return k;
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{{1}, 1}, // 0
		{{3}, 2}, // 2
		{{1}, 5}, // 2
		{{1, 3}, 6}, // 1
		{{1, 10, 5}, 20}, // 2
		{{1, 2, 2}, 5}, // 0
	};
	Solution solution;
	for (auto& p: input) {
		auto& nums = p.first;
		auto n = p.second;
		cout << "Input: nums = " << nums << ", n = " << n << endl;
		cout << "Output: " << solution.minPatches(nums, n) << endl;
	}
	return 0;
}
