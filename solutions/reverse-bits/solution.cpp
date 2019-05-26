#include <bitset>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	uint32_t reverseBits(uint32_t n) {
		uint32_t result = 0;
		for (int i = 0; i < 32; ++i)
			result |= ((n >> i) & 1) << (31 - i);
		return result;
	}
};

int main()
{
	string input[] = {
		"00000000000000000000000000000000",
		"00000000000000000000000010000000",
		"10000000000000000000000000000000",
		"00000000000000000000000000001011",
		"11000000000000000000000000011001",
		"00000010100101000001111010011100",
		"11111111111111111111111111111101",
		"11111111111111111111111111111111",
	};
	Solution solution;
	for (const auto& s: input) {
		bitset<32> val(s);
		cout << val << " => ";
		val = solution.reverseBits(val.to_ulong());
		cout << val << endl;
	}
	return 0;
}
