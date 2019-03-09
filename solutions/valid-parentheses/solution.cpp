#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
	bool isValid(const string& s) {
		struct ParenthesisState {
			char type;
			int count;
			ParenthesisState(char type): type(type), count(1) {}
			bool isMatch(char c) {
				switch (type) {
				case '(': return c == ')';
				case '[': return c == ']';
				case '{': return c == '}';
				default: return false;
				}
			}
		};
		stack<ParenthesisState> parentheses;
		for (auto c: s) {
			switch (c) {
			case '(':
			case '[':
			case '{': {
				if (!parentheses.empty() &&
				    parentheses.top().type == c)
					++parentheses.top().count;
				else
					parentheses.emplace(c);
				break;
			}
			case ')':
			case ']':
			case '}': {
				if (parentheses.empty())
					return false;
				auto& top = parentheses.top();
				if (!top.isMatch(c))
					return false;
				if (--top.count == 0)
					parentheses.pop();
				break;
			}
			default:
				return false;
			}
		}
		return parentheses.empty();
	}
};

int main()
{
	auto solution = Solution();
	const char* input[] = {
		"", // true
		"()", // true
		"()[]{}", // true
		"(]", // false
		"([)]", // false
		"{[]}", // true
	};
	for (auto s: input)
		cout << "\"" << s << "\" => " << 
			(solution.isValid(s) ? "true" : "false") << endl;
	return 0;
}
