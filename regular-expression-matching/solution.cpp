#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	bool isMatch(const string& input, const string& pattern) {
		int input_len = input.length();
		int pattern_len = pattern.length();
		set<pair<int, int>> done;
		stack<pair<int, int>> todo;
		todo.emplace(0, 0);
		while (!todo.empty()) {
			if (done.find(todo.top()) != done.end()) {
				todo.pop();
				continue;
			}
			done.insert(todo.top());
			int input_pos = todo.top().first;
			int pattern_pos = todo.top().second;
			todo.pop();
			if (pattern_pos == pattern_len) {
				if (input_pos == input_len)
					return true;
				continue;
			}
			char pattern_char = pattern[pattern_pos++];
			if (pattern_pos < pattern_len && pattern[pattern_pos] == '*') {
				todo.emplace(input_pos, pattern_pos + 1);
				--pattern_pos;
			}
			if (input_pos != input_len &&
			    (pattern_char == '.' || pattern_char == input[input_pos])) {
				todo.emplace(input_pos + 1, pattern_pos);
			}
		}
		return false;
	}
};

int main()
{
	pair<const char*, const char*> input[] = {
		{ "", "" }, // true
		{ "", "a*" }, // true
		{ "", ".*" }, // true
		{ "abc", "" }, // false
		{ "", "abc" }, // false
		{ "aa", "a" }, // false
		{ "aa", "a*" }, // true
		{ "ab", ".*" }, // true
		{ "aab", "c*a*b*" }, // true
		{ "mississippi", "mis*is*p*." }, // false
		{ "abxbcybc", "ab.*bc.*bc" }, // true
		{ "abbcxyzbc", "ab.*bc.*bc" }, // true
		{ "abbcxyzb", "ab.*bc.*bc" }, // false
		{ "abcd", ".*.*d" }, // true
	};
	Solution solution;
	for (const auto& it: input) {
		cout << '\"' << it.first << "\", \"" << it.second << "\" => " <<
			(solution.isMatch(it.first, it.second) ? "true" : "false") << endl;
	}
	return 0;
}
