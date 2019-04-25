#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	int numDecodings(const string& s) {
		int len = s.length();
		if (len == 0)
			return 0;

		int i = len;
		int n0 = 1; // number of ways to decode string s[i:len]
		int n1 = 1; // number of ways to decode string s[i+1:len]

		while (i > 0) {
			if (s[--i] == '0') {
				n1 = n0;
				n0 = 0;
				continue;
			}
			auto n0_prev = n0;
			if (i < len - 1 &&
			    (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6')))
				n0 += n1;
			n1 = n0_prev;
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
		"10", // 1
		"12", // 2
		"17", // 2
		"27", // 1
		"31", // 1
		"226", // 3
		"227", // 2
		"231", // 2
		"1010", // 1
	};
	Solution solution;
	for (const auto& s: input)
		cout << '"' << s << "\" => " << solution.numDecodings(s) << endl;
	return 0;
}
