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
	int firstMissingPositive(vector<int>& nums) {
		int size = nums.size();
		if (size == 0)
			return 1;
		// Modify the array so that value X, 1 <= X <= size,
		// is at index X 1-base.
		for (int i = 0; i < size; ) {
			int val = nums[i];
			if (val >= 1 && val <= size &&
			    val != i + 1 && nums[val - 1] != nums[i])
				swap(nums[val - 1], nums[i]);
			else
				++i;
		}
		// Look for the first array entry that doesn't equal
		// its 1-base index. This will be the first positive
		// integer missing in the array.
		for (int i = 0; i < size; ++i) {
			if (nums[i] != i + 1)
				return i + 1;
		}
		return size + 1;
	}
};

int main()
{
	vector<int> input[] = {
		{ }, // 1
		{ 1 }, // 2
		{ 1, 2, 0 }, // 3
		{ 1, 2, 2, 3 }, // 3
		{ 3, 4, -1, 1}, // 2
		{ 7, 8, 9, 11, 12}, // 1
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => ";
		cout << solution.firstMissingPositive(nums) << endl;
	}
	return 0;
}
