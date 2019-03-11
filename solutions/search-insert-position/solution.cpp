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
			out << ", ";
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int searchInsert(const vector<int>& nums, int target) {
		int begin = 0;
		int end = nums.size();
		int ret = end;
		while (begin != end) {
			int mid = begin + (end - begin) / 2;
			if (nums[mid] == target)
				return mid;
			if (nums[mid] > target)
				end = ret = mid;
			else
				begin = mid + 1;
		}
		return ret;
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{ {}, 1 }, // 0
		{ {2}, 1 }, // 0
		{ {2}, 3 }, // 1
		{ {1, 3, 5, 6}, 5 }, // 2
		{ {1, 3, 5, 6}, 2 }, // 1
		{ {1, 3, 5, 6}, 7 }, // 4
		{ {1, 3, 5, 6}, 0 }, // 0
	};
	Solution solution;
	for (auto& p: input) {
		cout << p.first << ", " << p.second << " => " <<
			solution.searchInsert(p.first, p.second) << endl;
	}
	return 0;
}
