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
	int findMin(const vector<int>& nums) {
		auto begin = nums.begin();
		auto end = nums.end();
		int result = *begin;
		while (begin < end) {
			auto mid = begin + (end - begin) / 2;
			if (*mid == *begin && *mid == *(end - 1)) {
				// Case 1: 1 1 1 0 1
				//             ^
				// Case 2: 1 0 1 1 1
				//             ^
				// There's no way to differentiate
				// the two cases without a linear
				// scan of the input array.
				++begin;
				--end;
			} else if (*mid >= *begin) {
				// Case 3: 1 1 2 3 4
				//             ^
				if (*mid <= *(end - 1)) {
					if (result > *begin)
						result = *begin;
					break;
				}
				// Case 4: 3 3 4 5 2
				//             ^
				begin = mid + 1;
			} else {
				// Case 5: 4 0 1 1 2
				//             ^
				end = mid;
			}
			if (result > *mid)
				result = *mid;
		}
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{1}, // 1
		{2, 1}, // 1
		{2, 1, 1}, // 1
		{2, 2, 1}, // 1
		{1, 2, 3}, // 1
		{1, 1, 2, 2, 3}, // 1
		{1, 1, 1, 2, 1}, // 1
		{1, 1, 1, 0, 1}, // 0
		{1, 2, 1, 1, 1}, // 1
		{1, 0, 1, 1, 1}, // 0
		{1, 2, 2, 3, 0}, // 0
		{3, 4, 5, 1, 2}, // 1
		{2, 2, 2, 0, 1}, // 0
		{4, 4, 5, 1, 1, 2, 3, 3}, // 1
		{2, 2, 4, 5, 6, 7, 7, 0, 1, 1, 2}, // 0
	};
	Solution solution;
	for (const auto& nums: input) {
		cout << "Input: " << nums << endl <<
			"Output: " << solution.findMin(nums) <<
			endl << endl;
	}
	return 0;
}
