#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	bool rotateString(const string& a, const string& b) {
		int len = a.length();
		if (len != static_cast<int>(b.length()))
			return false;
		if (len == 0)
			return true;

		bool match = false;
		for (int k = 0; !match && k < len; ++k) {
			match = true;
			for (int i = 0; match && i < len; ++i) {
				int j = (i + k) % len;
				if (a[i] != b[j])
					match = false;
			}
		}
		return match;
	}
};

int main()
{
	pair<string, string> input[] = {
		{"", ""}, // true
		{"", "abc"}, // false
		{"abc", ""}, // false
		{"abc", "abc"}, // true
		{"abc", "cba"}, // false
		{"abcde", "cdeab"}, // true
		{"abcde", "abced"}, // false
	};
	Solution solution;
	for (const auto& p: input) {
		bool rotate = solution.rotateString(p.first, p.second);
		cout << "Input: A = '" << p.first << "', B = '" <<
			p.second << "'" << endl << "Output: " <<
			(rotate ? "true" : "false") << endl << endl;
	}
	return 0;
}
