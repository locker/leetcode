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
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int search(const vector<int>& nums, int target) {
		auto begin = nums.begin();
		auto end = nums.end();
		while (begin < end) {
			auto mid = begin + (end - begin) / 2;
			if (*mid == target)
				return mid - nums.begin();
			if (*mid > *begin) {
				//
				// Example: 4, 5, 6, 7, 8, 1, 2, 3
				//                   ^
				//           part A      part B
				//
				if (target > *mid) {
					// Example: target = 9 is in part B.
					begin = mid + 1;
				} else if (target >= *begin) {
					// Example: target = 5 is in part A.
					end = mid;
				} else {
					// Example: target = 2 is in part B.
					begin = mid + 1;
				}
			} else {
				//
				// Example 7, 8, 1, 2, 3, 4, 5, 6
				//                  ^
				//          part A      part B
				//
				if (target < *mid) {
					// Example: target = 1 is in part A.
					end = mid;
				} else if (target < *begin) {
					// Example: target = 5 is in part B.
					begin = mid + 1;
				} else {
					// Example: target = 8 is in part A.
					end = mid;
				}
			}
		}
		return -1;
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{ {}, 1 }, // -1
		{ {1}, 2}, // -1
		{ {10}, 10}, // 0
		{ {3, 1}, 3}, // 0
		{ {3, 1}, 1}, // 1
		{ {1, 4, 5 }, 4 }, // 1
		{ {1, 8, 10 }, 5 }, // -1
		{ {1, 2, 3, 0}, 3 }, // 2
		{ {4, 6, 8, 2, 3}, 1 }, // -1
		{ {4, 5, 6, 7, 0, 1, 2}, 4 }, // 0
		{ {4, 5, 6, 7, 0, 1, 2}, 7 }, // 3
		{ {4, 5, 6, 7, 0, 1, 2}, 3 }, // -1
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& nums = p.first;
		auto target = p.second;
		cout << "Input: nums = " << nums <<
			", target = " << target << endl <<
			"Output: " << solution.search(nums, target) <<
			endl << endl;
	}
	return 0;
}
