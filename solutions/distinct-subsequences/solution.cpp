#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
	int numDistinct(const string& s, const string& t) {
		if (s.empty() || t.empty())
			return 0;
		//
		// Let F(S, T) return the number of distinct subsequences
		// of S equal to T. Apparently
		//
		//   F(S, T) = F(S[1:], T) if S[0] != T[0]
		//   F(S, T) = F(S[1:], T) + F(S[1:], T[1:]) otherwise
		//
		// This leads us to a classic dynamic programming solution
		// when we fill a len(T) by len(S) matrix where cell at
		// row i column j stores the value of F(S[i:], T[j:]).
		// Since we fill the matrix row by row starting from the
		// last row and to fill a cell we only need to know values
		// of its neighbors, we don't really need to keep the whole
		// matrix in memory and can get along with just one row.
		//
		int s_len = s.length();
		int t_len = t.length();
		// Use 'unsigned' to suppress the integer overflow warning.
		// We don't really care about overflows.
		vector<unsigned> dp(t_len);
		for (int i = s_len - 1; i >= 0; --i) {
			// We can assume that F(S[i:], T[len(T):]) = 1.
			unsigned prev = 1;
			for (int j = t_len - 1; j >= 0; --j) {
				unsigned curr = dp[j];
				if (s[i] == t[j])
					dp[j] += prev;
				prev = curr;
			}
		}
		return dp[0];
	}
};

int main()
{
	pair<string, string> input[] = {
		{"", ""}, // 0
		{"a", ""}, // 0
		{"", "a"}, // 0
		{"a", "aa"}, // 0
		{"a", "a"}, // 1
		{"ab", "a"}, // 1
		{"ba", "a"}, // 1
		{"aba", "a"}, // 2
		{"baba", "ba"}, // 3
		{"rabbbit", "rabbit"}, // 3
		{"badgbag", "bag"}, // 4
		{"babgbag", "bag"}, // 5
	};
	Solution solution;
	for (const auto& p: input) {
		cout << "Input: S = \"" << p.first << "\", T = \"" <<
			p.second << '"' << endl << "Output: " <<
			solution.numDistinct(p.first, p.second) << endl;
	}
	return 0;
}
