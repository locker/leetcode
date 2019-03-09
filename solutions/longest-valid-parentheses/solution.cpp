#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Solution {
	template<typename iterator>
	int doLongestValidParentheses(iterator begin, iterator end, bool reverse) {
		int max_count = 0;
		int count = 0;
		int balance = 0;
		for (auto it = begin; it != end; ++it) {
			if (*it == '(')
				balance += reverse ? -1 : 1;
			if (*it == ')')
				balance += reverse ? 1 : -1;
			if (balance < 0) {
				count = 0;
				balance = 0;
			} else
				++count;
			if (balance == 0)
				max_count = max(max_count, count);
		}
		return max_count;
	}
public:
	int longestValidParentheses(const string& s) {
		int count1 = doLongestValidParentheses(s.begin(), s.end(), false);
		int count2 = doLongestValidParentheses(s.rbegin(), s.rend(), true);
		return max(count1, count2);
	}
};

int main()
{
	const char *input[] = {
		"", // 0
		"(", // 0
		"))", // 0
		"(()", // 2
		"())", // 2
		")()())", // 4
		"(()())", // 6
		"((()())", // 6
	};
	Solution solution;
	for (auto s: input) {
		cout << '"' << s << "\" => " <<
			solution.longestValidParentheses(s) << endl;
	}
	return 0;
}
