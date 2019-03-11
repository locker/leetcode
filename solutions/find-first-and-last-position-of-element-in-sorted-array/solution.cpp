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
	vector<int> searchRange(const vector<int>& nums, int target) {
		vector<int> result(2, -1);
		int begin = 0;
		int end = nums.size();
		while (begin != end) {
			int mid = begin + (end - begin) / 2;
			if (nums[mid] == target)
				result[0] = mid;
			if (nums[mid] >= target)
				end = mid;
			else
				begin = mid + 1;
		}
		if (result[0] == -1)
			return result;
		begin = 0;
		end = nums.size();
		while (begin != end) {
			int mid = begin + (end - begin) / 2;
			if (nums[mid] == target)
				result[1] = mid;
			if (nums[mid] > target)
				end = mid;
			else
				begin = mid + 1;
		}
		return result;
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{ {}, 1 }, // -1, -1
		{ {1}, 2 }, // -1, -1
		{ {2}, 2 }, // 0, 0
		{ {1, 3, 5, 6}, 5 }, // 2, 2
		{ {5, 7, 7, 8, 8, 10}, 7 }, // 1, 2
		{ {5, 7, 7, 8, 8, 10}, 8 }, // 3, 4
	};
	Solution solution;
	for (auto& p: input) {
		cout << p.first << ", " << p.second << " => " <<
			solution.searchRange(p.first, p.second) << endl;
	}
	return 0;
}
