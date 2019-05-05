#include <iostream>
#include <string>

using namespace std;

class Solution {
	bool doValidPalindrome(const string& s, int first, int last,
			       bool may_delete_char) {
		int i = first;
		int j = last;
		while (i < j) {
			if (s[i] == s[j]) {
				++i;
				--j;
			} else if (may_delete_char) {
				return doValidPalindrome(s, i + 1, j, false) ||
					doValidPalindrome(s, i, j - 1, false);
			} else {
				return false;
			}
		}
		return true;
	}
public:
	bool validPalindrome(const string& s) {
		return doValidPalindrome(s, 0, s.length() - 1, true);
	}
};

int main()
{
	string input[] = {
		"", // true
		"a", // true
		"ab", // true
		"abc", // false
		"cbc", // true
		"cabc", // true
		"abaab", // true
		"abcdbc", // false
	};
	Solution solution;
	for (const auto& s: input) {
		cout << '"' << s << "\" can";
		if (!solution.validPalindrome(s))
			cout << "not";
		cout << " be made a palindrome" << endl;
	}
	return 0;
}
