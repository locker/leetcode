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
	int majorityElement(const vector<int>& nums) {
		int major = 0;
		int count = 0;
		for (int val: nums) {
			if (count == 0) {
				// 'major' isn't the majority element among
				// elements scanned so far. Moreover, there's
				// no majority element among them, as 'major'
				// was the best candidate. Therefore the
				// majority element must be among the rest
				// of the array and we can start anew.
				major = val;
			}
			if (val == major)
				++count;
			else
				--count;
		}
		return major;
	}
};

int main()
{
	vector<int> input[] = {
		{0}, // 0
		{1, 1}, // 1
		{2, 3, 2}, // 2
		{3, 2, 3, 3}, // 3
		{3, 4, 1, 4, 4}, // 4
		{5, 5, 5, 5, 5, 5}, // 5
		{6, 7, 6, 7, 6, 7, 6}, // 6
		{1, 7, 2, 7, 7, 7, 7, 3}, // 7
		{9, 9, 9, 9, 8, 8, 8, 8, 8}, // 8
		{8, 8, 9, 9, 8, 8, 9, 9, 9, 9}, // 9
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.majorityElement(nums) << endl;
	return 0;
}
