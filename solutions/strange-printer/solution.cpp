#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	int strangePrinter(string s) {
		int len = s.length();
		if (len == 0)
			return 0;

		// dp[i][j] stores the minimal number of turns it takes
		// the printer to print substring s[i..i+j].
		vector<vector<int>> dp(len);
		for (int i = 0; i < len; ++i)
			dp[i].resize(len - i);

		// Iterate over each possible substring length ...
		for (int j = 0; j < len; ++j) {
			// Iterate over each possible substring start ...
			for (int i = 0; i < len - j; ++i) {
				// Minimal number of turns it takes to print
				// substring s[i..i+j].
				int min_turns = numeric_limits<int>::max();
				// First character in the substring.
				int c = s[i];
				// We can print c until the first different
				// character is found or include the next
				// occurrence of c or include the next two
				// occurrences of c and so forth. Enumerate
				// all possibilities.
				for (int k = 0; k <= j;) {
					// Minimal number of turns it takes
					// to print substring s[i..k-1].
					int turns = k > 0 ? dp[i][k - 1] : 1;

					// Find the next different character.
					while (k <= j && s[i + k] == c)
						++k;

					// Suppose we first print s[i..i+k-1],
					// then s[i+k..i+j].
					if (k <= j)
						turns += dp[i + k][j - k];
					min_turns = min(min_turns, turns);

					// Find the next equal character and
					// start over.
					while (k <= j && s[i + k] != c)
						++k;
				}
				dp[i][j] = min_turns;
			}
		}
		return dp[0][len - 1];
	}
};

int main()
{
	string input[] = {
		"", // 0
		"a", // 1
		"aa", // 1
		"aba", // 2
		"aaabbb", // 2
		"aababa", // 3
	};
	Solution solution;
	for (const auto& s: input) {
		cout << '"' << s << "\" => " <<
			solution.strangePrinter(s) << endl;
	}
	return 0;
}
