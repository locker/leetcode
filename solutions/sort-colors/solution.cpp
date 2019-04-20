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
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	void sortColors(vector<int>& nums) {
		auto one_begin = nums.end();
		auto two_begin = nums.end();
		for (auto it = nums.begin(); it != nums.end(); ++it) {
			switch (*it) {
			case 2:
				if (two_begin == nums.end())
					two_begin = it;
				break;
			case 1:
				if (two_begin != nums.end()) {
					swap(*it, *two_begin++);
					if (one_begin == nums.end())
						one_begin = two_begin - 1;
				} else if (one_begin == nums.end()) {
					one_begin = it;
				}
				break;
			case 0:
				if (one_begin != nums.end())
					swap(*it, *one_begin++);
				if (two_begin != nums.end())
					swap(*it, *two_begin++);
				break;
			default:
				break;
			}
		}
	}
};

int main()
{
	vector<int> input[] = {
		{},
		{0},
		{1},
		{2},
		{2, 1},
		{2, 0},
		{0, 1, 2},
		{1, 1, 0, 0, 2, 2},
		{1, 0, 1, 2, 0, 2, 1},
		{2, 2, 2, 1, 1, 1, 0},
		{0, 1, 2, 0, 1, 2, 0},
	};
	Solution solution;
	for (auto& nums: input) {
		cout << nums << " => ";
		solution.sortColors(nums);
		cout << nums << endl;
	}
	return 0;
}
