#include <iostream>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v) {
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
	vector<int> twoSum(vector<int>& nums, int target) {
		int i, j;
		for (i = 0, j = nums.size() - 1; i < j; ) {
			int sum = nums[i] + nums[j];
			if (sum == target)
				return {i + 1, j + 1};
			if (sum < target)
				++i;
			else
				--j;
		}
		return {};
	}
};

int main()
{
	vector<int> nums{2, 7, 11, 15};
	int target = 9;
	auto result = Solution().twoSum(nums, target);

	cout << "input: " << nums << ", " << target << endl;
	cout << "output: " << result << endl;
	return 0;
}
