#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	bool isMatch(const string& input, const string& pattern) {
		int input_len = input.length();
		int pattern_len = pattern.length();
		int input_pos = 0;
		int pattern_pos = 0;
		int input_pos_star = -1;
		int pattern_pos_star = -1;
		while (input_pos < input_len) {
			if (pattern_pos < pattern_len &&
			    (pattern[pattern_pos] == '?' ||
			     pattern[pattern_pos] == input[input_pos])) {
				++input_pos;
				++pattern_pos;
			} else if (pattern_pos < pattern_len &&
				   pattern[pattern_pos] == '*') {
				input_pos_star = input_pos;
				pattern_pos_star = pattern_pos++;
			} else if (pattern_pos_star >= 0) {
				input_pos = input_pos_star + 1;
				pattern_pos = pattern_pos_star;
			} else {
				return false;
			}
		}
		while (pattern[pattern_pos] == '*')
			++pattern_pos;
		return pattern_pos == pattern_len;
	}
};

int main()
{
	pair<const char*, const char*> input[] = {
		{"", ""}, //true
		{"a", ""}, // false
		{"", "*"}, // true
		{"aa", "a"}, // false
		{"aa", "*"}, // true
		{"cb", "?a"}, // false
		{"adceb", "**a**b"}, // true
		{"acdcb", "a*c?b"}, // false
	};
	Solution s;
	for (auto& p: input) {
		cout << '"' << p.first << "\", \"" << p.second << "\" => " <<
			(s.isMatch(p.first, p.second) ? "true" : "false") << endl;
	}
	return 0;
}
