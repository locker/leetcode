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
	bool canJump(const vector<int>& nums) {
		int size = nums.size();
		if (size < 2)
			return true;
		int distance = 0;
		for (int i = size - 2; i >= 0; --i) {
			if (nums[i] <= distance)
				++distance;
			else
				distance = 0;
		}
		return distance == 0;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // true
		{0}, // true
		{1, 0}, // true
		{0, 0}, // false
		{1, 0, 0}, // false
		{2, 1, 0}, // true
		{0, 2, 1}, // false
		{2, 3, 1, 1, 4}, // true
		{3, 2, 1, 0, 4}, // false
		{3, 2, 1, 0, 1, 2}, // false
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => " <<
			(solution.canJump(nums) ? "true" : "false") << endl;
	}
	return 0;
}
