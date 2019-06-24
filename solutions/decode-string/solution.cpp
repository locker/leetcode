#include <iostream>
#include <stack>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	string decodeString(const string& s) {
		stack<pair<string, int>> todo;
		todo.emplace(string(), 1);
		for (int i = 0; i < static_cast<int>(s.length()); ++i) {
			if (isdigit(s[i])) {
				char *end;
				int count = strtol(s.c_str() + i, &end, 10);
				todo.emplace(string(), count);
				i = end - s.c_str();
			} else if (s[i] == ']') {
				auto p = move(todo.top());
				todo.pop();
				for (int j = 0; j < p.second; ++j)
					todo.top().first.append(p.first);
			} else {
				todo.top().first.push_back(s[i]);
			}
		}
		return todo.top().first;
	}
};

int main()
{
	string input[] = {
		"", // ""
		"a", // "a"
		"2[]", // ""
		"0[a]", // ""
		"1[a]", // "a"
		"2[a]", // "aa"
		"2[ab]", // "abab"
		"3[a]2[bc]", // "aaabcbc"
		"3[a2[c]]", // "accaccacc"
		"2[abc]3[cd]ef", // "abcabccdcdcdef"
	};
	Solution solution;
	for (const auto& s: input) {
		cout << '"' << s << "\" => \"" <<
			solution.decodeString(s) << '"' << endl;
	}
	return 0;
}
