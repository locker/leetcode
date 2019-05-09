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
	int findDuplicate(const vector<int>& nums) {
		int n = nums.size();
		//
		// We know that the duplicate number is between 1 and n,
		// inclusive. If the number of array entries <= k is <= k,
		// the duplicate number must be > k, otherwise it is <= k.
		// We can count array entries <= k in O(n) time. Hence using
		// the binary search technique we can find the duplicate in
		// O(n*log(n)) time.
		//
		int a = 1;
		int b = n;
		while (a != b) {
			int c = 0;
			int k = (a + b) / 2;
			for (int x: nums) {
				if (x <= k)
					++c;
			}
			if (c <= k)
				a = k + 1;
			else
				b = k;
		}
		return a;
	}
};

int main()
{
	vector<int> input[] = {
		{1, 1}, // 1
		{1, 2, 1}, // 1
		{2, 1, 2}, // 2
		{1, 3, 2, 1}, // 1
		{3, 1, 2, 2}, // 2
		{3, 3, 2, 1}, // 3
		{1, 3, 4, 2, 1}, // 1
		{1, 3, 4, 2, 2}, // 2
		{3, 1, 3, 4, 2}, // 3
		{4, 1, 3, 4, 2}, // 4
		{4, 1, 3, 1, 2, 5}, // 1
		{4, 1, 3, 2, 2, 5}, // 2
		{3, 1, 3, 4, 2, 5}, // 3
		{3, 1, 4, 4, 2, 5}, // 4
		{5, 1, 3, 4, 2, 5}, // 5
		{1, 1, 1, 3, 5, 2}, // 1
		{2, 2, 2, 2, 5, 2}, // 2
		{2, 3, 3, 3, 5, 4}, // 3
		{4, 4, 4, 4, 4, 1}, // 4
		{5, 5, 5, 5, 5, 5}, // 5
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.findDuplicate(nums) << endl;
	return 0;
}
