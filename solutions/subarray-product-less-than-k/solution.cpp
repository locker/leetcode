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
	int numSubarrayProductLessThanK(const vector<int>& nums, int k) {
		// If k = 1, even a single-number subarray product is
		// greater than or equal to k.
		if (k == 1)
			return 0;

		// Current subarray boundaries and product.
		int product = 1;
		auto begin = nums.begin();
		auto end = nums.begin();

		// Scan the array from left to right counting subarrays.
		int count = 0;
		while (begin != nums.end()) {
			if (product < k && end != nums.end()) {
				// Account this subarray and all subarrays that
				// could be produced by increasing the left
				// boundary, as their products are surely less
				// than k.
				count += end - begin;
				// Extend the subarray to the right.
				product *= *end++;
			} else {
				// Shrink the subarray from the left and
				// account it if its product is less than k.
				if (product < k)
					++count;
				product /= *begin++;
			}
		}
		return count;
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{{}, 5}, // 0
		{{5}, 5}, // 0
		{{5}, 6}, // 1
		{{5, 4}, 10}, // 2
		{{5, 4}, 21}, // 3
		{{5, 4, 3}, 15}, // 4
		{{10, 5, 2, 6}, 100}, // 8
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& nums = p.first;
		int k = p.second;
		int n = solution.numSubarrayProductLessThanK(nums, k);
		cout << "Input: nums = " << nums << ", k = " << k << endl <<
			"Output: " << n << endl;
	}
	return 0;
}
