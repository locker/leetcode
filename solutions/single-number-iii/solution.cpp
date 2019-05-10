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
	vector<int> singleNumber(const vector<int>& nums) {
		//
		// Let's denote the single numbers by a and b.
		//
		// First, find the bits that differ between a and b
		// by xor-ing the given numbers.
		//
		int a_xor_b = 0;
		for (auto x: nums)
			a_xor_b ^= x;
		//
		// Pick the first different bit. We know it exists as
		// a != b (otherwise they would pair with each other).
		//
		int bit = 0;
		while (!(a_xor_b >> bit & 1))
			++bit;
		//
		// Now we can divide all the given numbers in two
		// groups - one has the bit set, another doesn't.
		// a and b will be the only single numbers in the
		// two groups. To find them, we xor group numbers.
		//
		int a = 0;
		int b = 0;
		for (auto x: nums) {
			if (x >> bit & 1)
				a ^= x;
			else
				b ^= x;
		}
		return {a, b};
	}
};

int main()
{
	vector<int> input[] = {
		{1, 2}, // [1, 2]
		{5, 5, 2, 3, 3, 4}, // [2, 4]
		{9, 1, 9, 8, 7, 2, 2, 7}, // [1, 8]
		{6, 5, 4, 3, 2, 1, 5, 4, 3, 2}, // [1, 6]
		{10, 100, 5, 71, 71, 23, 5, 10, 23, 123}, // [123, 100]
		{1, 10, 100, 1000, 5, 1, 10, 100, 1000, 500}, // [5, 500]
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.singleNumber(nums) << endl;
	return 0;
}
