#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		first = false;
		out << x;
	}
	out << ']';
	return out;
}

class Solution {
public:
	bool increasingTriplet(const vector<int>& nums) {
		const int size = nums.size();
		int i0 = -1;
		int j0 = -1;
		int i1 = -1;
		for (int i = 0; i < size; ++i) {
			if (i0 == -1) {
				i0 = i;
			} else if (j0 == -1) {
				if (nums[i] > nums[i0])
					j0 = i;
				else
					i0 = i;
			} else if (nums[i] > nums[j0]) {
				return true;
			} else if (nums[i] > nums[i0]) {
				j0 = i;
			} else if (i1 == -1 || nums[i] <= nums[i1]) {
				i1 = i;
			} else {
				i0 = i1;
				j0 = i;
				i1 = -1;
			}
		}
		return false;
	}
};

int main()
{
	const pair<vector<int>, bool> test_data[] = {
		{{}, false},
		{{1}, false},
		{{1, 2}, false},
		{{1, 2, 3}, true},
		{{1, 2, 1}, false},
		{{1, 2, 3, 4, 5}, true},
		{{5, 4, 3, 2, 1}, false},
		{{2, 1, 5, 0, 4, 6}, true},
		{{20, 100, 10, 12, 5, 13}, true},
	};
	bool success = true;
	Solution solution;
	for (const auto& [nums, expected] : test_data) {
		bool result = solution.increasingTriplet(nums);
		cout << nums << " => " << (result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: wrong result" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
