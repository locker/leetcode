#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
	typedef string::const_iterator iterator;
	typedef pair<iterator, iterator> substring;

	int longestPalindromeAt(const string& s, substring& pos) {
		int len = pos.second - pos.first;
		while (pos.first != s.begin() && pos.second != s.end()) {
			if (*(pos.first - 1) != *pos.second)
				break;
			--pos.first;
			++pos.second;
			len += 2;
		}
		return len;
	}
public:
	string longestPalindrome(const string& s) {
		substring longest(s.begin(), s.begin());
		for (auto it = s.begin(); it != s.end(); ++it) {
			substring pos(it, it);
			if (longestPalindromeAt(s, pos) >
			    longest.second - longest.first)
				longest = pos;
			pos = substring(it, it + 1);
			if (longestPalindromeAt(s, pos) >
			    longest.second - longest.first)
				longest = pos;
		}
		return string(longest.first, longest.second);
	}
};

int main()
{
	const char *input[] = {
		"",
		"b",
		"bc",
		"bbb",
		"babad",
		"babaab",
		"cbbd",
	};
	Solution solution;
	for (auto s: input) {
		cout << '\"' << s << "\" => \"" <<
			solution.longestPalindrome(s) << '\"' << endl;
	}
	return 0;
}
