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
	bool search(const vector<int>& nums, int target) {
		auto begin = nums.begin();
		auto end = nums.end();
		while (begin < end) {
			auto mid = begin + (end - begin) / 2;
			if (*mid == target)
				return true;
			if (*mid == *begin && *mid == *(end - 1)) {
				//
				// Case 1: 1, 2, 1, 1, 1
				//               ^
				// Case 2: 1, 1, 1, 2, 1
				//               ^
				// There's no way to differentiate between
				// the two cases, but scan the array linearly.
				//
				++begin;
				--end;
			} else if (*mid >= *begin) {
				//
				// Example: 5, 5, 6, 7, 8, 1, 2, 5
				//                   ^
				//           part A       part B
				//
				if (target > *mid) {
					// Example: target = 8 is in part B.
					begin = mid + 1;
				} else if (target >= *begin) {
					// Example: target = 6 is in part A.
					end = mid;
				} else {
					// Example: target = 2 is in part B.
					begin = mid + 1;
				}
			} else {
				//
				// Example: 5, 5, 6, 1, 2, 3, 4, 5, 5
				//                      ^
				//            part A         part B
				//
				if (target < *mid) {
					// Example: target = 1 is in part A.
					end = mid;
				} else if (target < *begin) {
					// Example: target = 4 is in part B.
					begin = mid + 1;
				} else {
					// Example: target = 6 is in part A.
					end = mid;
				}
			}
		}
		return false;
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{ {}, 1 }, // false
		{ {1}, 2}, // false
		{ {10}, 10}, // true
		{ {1, 1}, 1}, // true
		{ {1, 3}, 3}, // true
		{ {1, 1, 3}, 2}, // false
		{ {1, 1, 3}, 3}, // true
		{ {1, 3, 3}, 1}, // true
		{ {1, 3, 1, 1}, 3}, // true
		{ {1, 1, 1, 3, 1}, 3}, // true
		{ {4, 1, 1, 3}, 1}, // true
		{ {4, 1, 1, 3}, 2}, // false
		{ {4, 1, 1, 3, 3}, 3}, // true
		{ {2, 5, 6, 0, 0, 1, 2}, 0}, // true
		{ {2, 5, 6, 0, 0, 1, 2}, 3}, // false
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& nums = p.first;
		auto target = p.second;
		cout << "Input: nums = " << nums << ", target = " <<
			target << endl << "Output: " <<
			(solution.search(nums, target) ? "true" : "false") <<
			endl << endl;
	}
	return 0;
}
