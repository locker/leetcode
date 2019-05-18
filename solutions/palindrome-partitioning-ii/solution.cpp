#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	int minCut(const string& s) {
		int len = s.length();
		if (len <= 1)
			return 0;

		// palindromes[i] stores lengths of all palindromes starting
		// at character i.
		vector<vector<int>> palindromes(len);
		for (int i = 0; i < len; ++i) {
			for (int j = i, k = i; j >= 0 && k < len; --j, ++k) {
				if (s[j] != s[k])
					break;
				palindromes[j].push_back(k - j + 1);
			}
			for (int j = i, k = i + 1; j >= 0 && k < len; --j, ++k) {
				if (s[j] != s[k])
					break;
				palindromes[j].push_back(k - j + 1);
			}
		}

		// min_cut[i] stores the minimal number of cuts needed
		// to partition sub string starting at character i.
		vector<int> min_cut(len, numeric_limits<int>::max());

		for (int i = len - 1; i >= 0; --i) {
			for (int j: palindromes[i]) {
				if (i + j == len) {
					min_cut[i] = 0;
					break;
				}
				min_cut[i] = min(min_cut[i], 1 + min_cut[i + j]);
			}
		}
		return min_cut[0];
	}
};

int main()
{
	string input[] = {
		"", // 0
		"a", // 0
		"aa", // 0
		"aaa", // 0
		"aba", // 0
		"aab", // 1
		"aabb", // 1
		"babb", // 1
		"abab", // 1
		"abbc", // 2
		"abacbcb", // 2
		"abcdabc", // 6
	};
	Solution solution;
	for (const auto& s: input)
		cout << '"' << s << "\" => " << solution.minCut(s) << endl;
	return 0;
}
