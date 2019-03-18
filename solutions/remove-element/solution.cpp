#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& nums)
{
	out << '[';
	for (auto it = nums.begin(); it != nums.end(); ++it) {
		if (it != nums.begin())
			out << ", ";
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int removeElement(vector<int>& nums, int val) {
		auto out = nums.begin();
		for (auto it = nums.begin(); it != nums.end(); ++it) {
			if (*it == val)
				continue;
			if (out != it)
				*out = *it;
			++out;
		}
		return out - nums.begin();
	}
};

int main()
{
	pair<vector<int>, int> input[] = {
		{{}, 1},
		{{1}, 1},
		{{1, 1}, 1},
		{{3, 2, 2, 3}, 3},
		{{0, 1, 2, 2, 3, 0, 4, 2}, 2},
	};
	Solution solution;
	for (auto& p: input) {
		auto& nums = p.first;
		int val = p.second;
		cout << nums << ", " << val << " => ";
		int size = solution.removeElement(nums, val);
		nums.resize(size);
		cout << nums << endl;
	}
	return 0;
}
