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
	int singleNumber(const vector<int>& nums) {
		//
		// Simply xor all numbers: those that have duplicates will
		// result to 0 and hence only the single number remains in
		// the end result.
		//
		int result = 0;
		for (auto x: nums)
			result ^= x;
		return result;
	}
};

int main()
{
	vector<int> input[] = {
		{5}, // 5
		{5, 5, 2}, // 2
		{1, 2, 3, 1, 2}, // 3
		{10, 2, 2, 4, 4}, // 10
		{2, 2, 10, 10, 4, 4, 1}, // 1
		{1, 5, 2, 4, 3, 5, 4, 2, 1}, // 3
		{100, 200, 300, 40, 300, 200, 100}, // 40
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.singleNumber(nums) << endl;
	return 0;
}
