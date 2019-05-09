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
	int missingNumber(const vector<int>& nums) {
		int n = nums.size();
		//
		// Let
		//
		//   s1 = 0 ^ 1 ^ 2 ^ ... ^ n,
		//   s2 = 0 ^ 1 ^ ... ^ (x-1) ^ (x+1) ^ (x+2) ^ ... ^ n,
		//
		// where x is the missing number, ^ denotes exclusive or.
		//
		// Then s2 = s1 ^ x hence x = s1 ^ s2.
		//
		int s1 = n;
		int s2 = 0;
		for (int i = 0; i < n; ++i) {
			s1 ^= i;
			s2 ^= nums[i];
		}
		return s1 ^ s2;
	}
};

int main()
{
	vector<int> input[] = {
		{1}, // 0
		{0}, // 1
		{1, 2}, // 0
		{2, 0}, // 1
		{0, 1}, // 2
		{1, 2, 3}, // 0
		{2, 0, 3}, // 1
		{3, 1, 0}, // 2
		{0, 2, 1}, // 3
		{1, 2, 4, 3}, // 0
		{2, 0, 4, 3}, // 1
		{3, 4, 0, 1}, // 2
		{4, 2, 0, 1}, // 3
		{0, 3, 2, 1}, // 4
		{9, 6, 4, 2, 3, 5, 7, 0, 1}, // 8
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.missingNumber(nums) << endl;
	return 0;
}
