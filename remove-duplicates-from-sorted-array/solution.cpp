#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& nums, int count)
{
	cout << '[';
	for (int i = 0; i < count; ++i) {
		if (i > 0)
			cout << ", ";
		cout << nums[i];
	}
	cout << ']';
}

class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)
			return 0;

		int count = 1;
		for (int i = 1; i < size; ++i) {
			if (nums[i] != nums[i - 1])
				nums[count++] = nums[i];
		}
		return count;
	}
};

int main()
{
	vector<int> input[] = {
		{ },
		{ 1 },
		{ 1, 2 },
		{ 1, 1, 2 },
		{ 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 },
	};
	Solution solution;
	for (auto& nums: input) {
		print(nums, nums.size());
		int count = solution.removeDuplicates(nums);
		cout << " => ";
		print(nums, count);
		cout << endl;
	}
	return 0;
}
