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
		// In the general case when all numbers are present exactly k
		// times except the only one that is present once, to find
		// the single number we need to sum corresponding bits of all
		// numbers modulo k - apparently the sums will give us the
		// binary representation of the single number. If k equals 2,
		// we can use xor operation available out of the box. For k
		// equal 3, we need to devise a way to sum bits modulo 3.
		//
		// A value modulo 3 can be represented by two bits. Let us
		// denote the higher bit by a, the lower bit by b, the bit of
		// the added number by x. A table of all possible combinations
		// of a, b, and x and the resulting value is presented below:
		//
		//   a  b  +  x  =  a' b'
		//   0  0  +  0  =  0  0
		//   0  0  +  1  =  0  1
		//   0  1  +  0  =  0  1
		//   0  1  +  1  =  1  0
		//   1  0  +  0  =  1  0
		//   1  0  +  1  =  0  0
		//
		// One can see that
		//
		//   a' = ~(b ^ x) & (a | b)
		//   b' = (b ^ x) & ~a
		//
		// So we just sum all the given numbers using the expressions
		// above and get the missing number bits in b.
		//
		int a = 0;
		int b = 0;
		for (int x: nums) {
			int a1 = ~(b ^ x) & (a | b);
			int b1 = (b ^ x) & ~a;
			a = a1;
			b = b1;
		}
		return b;
	}
};

int main()
{
	vector<int> input[] = {
		{10}, // 10
		{5, 5, 1, 5}, // 1
		{123, 13, 13, 13}, // 123
		{0, 1, 0, 1, 0, 1, 99}, // 99
		{1, 2, 3, 4, 1, 2, 3, 3, 2, 1}, // 4
		{100, 200, 300, 200, 200, 100, 100}, // 300
	};
	Solution solution;
	for (const auto& nums: input)
		cout << nums << " => " << solution.singleNumber(nums) << endl;
	return 0;
}
