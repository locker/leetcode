#include <iostream>
#include <limits>
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
	int jump(const vector<int>& nums) {
		int size = nums.size();
		if (size < 2)
			return 0; // already there

		int i = 0; // current index
		int count = 1; // number of jumps done

		while (i + nums[i] < size - 1) {
			//
			// The next best index to jump to is the one
			// from which we will be able to cover the max
			// distance. There's no point to consider other
			// indexes as the chosen one covers all jumps
			// that can be done from those.
			//
			int next = i + 1;
			for (int j = i + 1; j <= i + nums[i]; ++j) {
				if (j + nums[j] > next + nums[next])
					next = j;
			}
			i = next;
			++count;
		}
		return count;
	}
};

int main()
{
	vector<int> input[] = {
		{}, // 0
		{0}, // 0
		{1, 0}, // 1
		{2, 1, 0}, // 1
		{2, 3, 0, 1, 4}, // 2
		{2, 3, 1, 1, 4}, // 2
		{2, 3, 3, 1, 1, 5}, // 2
	};
	Solution solution;
	for (auto& nums: input)
		cout << nums << " => " << solution.jump(nums) << endl;
	return 0;
}
