#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	string& reverseWords(string& s) {
		// Remove leading/trailing/multiple spaces in place
		// and reverse all words.
		auto start = s.begin();
		auto out = s.begin();
		for (auto it = s.begin(); it != s.end(); ++it) {
			if (*it == ' ')
				continue;
			if (out != s.begin() &&
			    it != s.begin() && *(it - 1) == ' ') {
				// Reverse the last word before
				// starting a new one.
				reverse(start, out);
				*out++ = ' ';
				start = out;
			}
			*out++ = *it;
		}
		// Reverse the last word.
		reverse(start, out);
		// Shrink the string size.
		s.resize(out - s.begin());
		// Reverse the whole string.
		reverse(s.begin(), s.end());
		return s;
	}
};

int main()
{
	string input[] = {
		"",
		"  ",
		" abc ",
		" a b c ",
		" ab  bc  ca ",
		"the sky is blue",
		"  hello world!  ",
		"a good   example",
	};
	Solution solution;
	for (auto& s: input) {
		cout << '"' << s << "\" => \"";
		cout << solution.reverseWords(s) << '"' << endl;
	}
	return 0;
}
