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
			if (*mid > *begin) {
				// Case 1: 1 2 3 4 5 6 7
				//               ^
				if (*mid <= *(end - 1)) {
					if (result > *begin)
						result = *begin;
					break;
				}
				// Case 2: 3 4 5 6 7 1 2
				//               ^
				begin = mid + 1;
			} else {
				// Case 3: 6 7 1 2 3 4 5
				//               ^
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
		{1, 2, 3}, // 1
		{1, 2, 3, 0}, // 0
		{3, 4, 5, 1, 2}, // 1
		{4, 5, 1, 2, 3}, // 1
		{4, 5, 6, 7, 0, 1, 2}, // 0
	};
	Solution solution;
	for (const auto& nums: input) {
		cout << "Input: " << nums << endl <<
			"Output: " << solution.findMin(nums) <<
			endl << endl;
	}
	return 0;
}
