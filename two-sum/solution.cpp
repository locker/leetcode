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
		for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
			for (int j = i + 1; j < static_cast<int>(nums.size()); ++j) {
				if (nums[i] + nums[j] == target)
					return {i, j};
			}
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
