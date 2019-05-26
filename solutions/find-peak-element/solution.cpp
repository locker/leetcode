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
	int findPeakElement(const vector<int>& nums) {
		auto begin = nums.begin();
		auto end = nums.end();
		while (end - begin > 1) {
			auto mid = begin + (end - begin) / 2;
			if (*(mid - 1) < *mid)
				begin = mid;
			else
				end = mid;
		}
		return begin - nums.begin();
	}
};

int main()
{
	vector<int> input[] = {
		{1}, // 0
		{2, 1}, // 0
		{1, 2}, // 1
		{1, 3, 2}, // 1
		{1, 2, 3, 1}, // 2
		{1, 2, 1, 3, 5, 6, 4}, // 5
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.findPeakElement(nums) << endl;
	return 0;
}
