#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	string shortestPalindrome(const string& s) {
		int len = s.length();

		//
		// First, find the longest palindromic prefix of
		// the input string.
		//
		// A naive approach is to check whether substring s[0..k]
		// is a palindrome for each k = len ... 0, but that would
		// give us quadratic time complexity in the worst case.
		// We can do better.
		//
		// Let us define period l of string s as such a number
		// that s equals s0 + s0 + ... + s0[0..l0] where s0 is
		// a string of length l, l0 <= l. For example, string
		// "aaa" has period 1, string "abcabcab" has period 3,
		// string "abcd" has period 4.
		//
		// To check if string s is a palindrome, we iterate over
		// it from both ends comparing characters s[i++] and s[j--]
		// until i >= j or a mismatch is found (initially i = 0 and
		// j = len - 1). Suppose we found a mismatch after having
		// scanned k characters. Can substring s[0..len-p], p < k,
		// be a palindrome? Yes, but only if string s[0..k] has
		// period p. This follows directly from the definition of
		// the string period above. Do we need to rescan last p
		// characters of s[0..len-p]? No, they match first p
		// characters automatically, again by the definition of
		// the string period.
		//
		// Keeping that in mind, we can perform the task with linear
		// time complexity, as we can keep track of the period while
		// iterating linearly over a string.
		//
		int period = 1;
		int palindrome_len = len;
		int i = 0, i0 = 0, j = len - 1;

		while (i < j) {
			if (s[j] != s[i0]) {
				// The string isn't periodic anymore.
				// Reset the period.
				i0 = 0;
				period = i;
				//
				// We have two possible scenarios here,
				// illustrated by the examples below:
				// 1. abcabcd  | old period is 3
				//          ^  | new period is 7
				// 2. abcabca  | old period is 3
				//          ^  | new period is 6
				//
				if (s[j] != s[0])
					++period;
				else
					++i0;
			} else {
				++i0;
				i0 %= period;
			}
			if (s[i++] != s[j--]) {
				// Mismatch. Reset to the last period.
				i -= period;
				palindrome_len -= period;
			}
		}

		//
		// Second, reverse the substring following the found
		// palindrome to get the prefix of the final string.
		//
		string prefix = s.substr(palindrome_len, len);
		reverse(prefix.begin(), prefix.end());

		//
		// Third, prepend the input string with the prefix.
		//
		return prefix + s;
	}
};

int main()
{
	string input[] = {
		"", // ""
		"a", // "a"
		"aa", // "aa"
		"abcd", // "dcbabcd"
		"aabba", // "abbaabba"
		"aacecaaa", // "aaacecaaa"
		"babbbabbaba", // "ababbabbbabbaba"
	};
	Solution solution;
	for (const auto& s: input) {
		cout << "Input: \"" << s << '"' << endl << "Output: \"" <<
			solution.shortestPalindrome(s) << '"' << endl << endl;
	}
	return 0;
}
