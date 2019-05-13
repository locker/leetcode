#include <bitset>
#include <iostream>

using namespace std;

class Solution {
public:
	int hammingWeight(uint32_t n) {
		int count = 0;
		while (n != 0) {
			if (n & 1)
				++count;
			n >>= 1;
		}
		return count;
	}
};

int main()
{
	string input[] = {
		"00000000000000000000000000000000", // 0
		"00000000000000000000000010000000", // 1
		"10000000000000000000000000000000", // 1
		"00000000000000000000000000001011", // 3
		"11000000000000000000000000011001", // 5
		"11111111111111111111111111111101", // 31
		"11111111111111111111111111111111", // 32
	};
	Solution solution;
	for (const auto& s: input) {
		bitset<32> val(s);
		cout << val << " => " <<
			solution.hammingWeight(val.to_ulong()) << endl;
	}
	return 0;
}
