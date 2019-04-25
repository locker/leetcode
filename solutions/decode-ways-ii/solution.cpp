#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	int numDecodings(const string& s) {
		const long long MAX = 1000000007;
		int len = s.length();
		if (len == 0)
			return 0;

		int i = len;
		long long n0 = 1; // number of ways to decode string s[i:len]
		long long n1 = 1; // number of ways to decode string s[i+1:len]

		while (i > 0) {
			--i;
			auto n0_prev = n0;
			switch (s[i]) {
			case '0':
				n0 = 0;
				break;
			case '1':
				if (i == len - 1)
					break;
				if (s[i + 1] == '*')
					n0 += n1 * 9; // 1[1-9]
				else
					n0 += n1; // 1X
				break;
			case '2':
				if (i == len - 1)
					break;
				if (s[i + 1] == '*')
					n0 += n1 * 6; // 2[1-6]
				else if (s[i + 1] <= '6')
					n0 += n1; // 2X
				break;
			case '*':
				n0 *= 9; // [1-9]
				if (i == len - 1)
					break;
				if (s[i + 1] == '*') {
					n0 += n1 * 15; // 1[1-9] or 2[1-6]
				} else {
					n0 += n1; // 1X
					if (s[i + 1] <= '6')
						n0 += n1; // 2X
				}
				break;
			default:
				break;
			}
			n1 = n0_prev;
			n0 %= MAX;
		}
		return n0;
	}
};

int main()
{
	string input[] = {
		"", // 0
		"0", // 0
		"1", // 1
		"*", // 9
		"10", // 1
		"12", // 2
		"17", // 2
		"1*", // 18
		"3*", // 9
		"*7", // 10
		"*6", // 11
		"**", // 96
		"27", // 1
		"31", // 1
		"226", // 3
		"227", // 2
		"231", // 2
		"*0*0", // 4
		"2839", // 1
	};
	Solution solution;
	for (const auto& s: input)
		cout << '"' << s << "\" => " << solution.numDecodings(s) << endl;
	return 0;
}
