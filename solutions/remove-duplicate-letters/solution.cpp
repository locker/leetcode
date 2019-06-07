#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	string removeDuplicateLetters(const string& s) {
		if (s.length() <= 1)
			return s;

		// Counts each character remaining in the input string.
		int count['z' - 'a' + 1] = { 0, };
		for (auto c: s)
			++count[c - 'a'];

		// Flag corresponding to a character is set if the character
		// has been appended to the result.
		vector<bool> appended('z' - 'a' + 1);

		// Output string.
		string out;

		for (auto c: s) {
			--count[c - 'a'];

			if (appended[c - 'a']) {
				// The same character has already been appended
				// to the output. We must not append it twice.
				// Assuming the string built so far is the
				// smallest in lexicographical order, we can
				// skip this occurrence.
				continue;
			}

			// Remove all characters that are greater than this one
			// and can be removed (i.e. have other occurrences in
			// the input string). Appending this character before
			// any of them will obviously produce a smaller string.
			while (!out.empty() && out.back() > c &&
			       count[out.back() - 'a'] > 0) {
				appended[out.back() - 'a'] = false;
				out.pop_back();
			}

			// Append this character.
			out.push_back(c);
			appended[c - 'a'] = true;
		}

		return out;
	}
};

int main()
{
	string input[] = {
		"", // ""
		"a", // "a"
		"aa", // "aa",
		"aba", // "ab",
		"cbc", // "bc",
		"abc", // "abc"
		"bcabc", // "abc"
		"abacb", // "abc"
		"bbcaac", // "bac"
		"bddbccd", // "bcd"
		"cbacdcbc", // "acdb"
	};
	Solution solution;
	for (const auto& s: input) {
		cout << '"' << s << "\" => \"" <<
			solution.removeDuplicateLetters(s) << '"' << endl;
	}
	return 0;
}
