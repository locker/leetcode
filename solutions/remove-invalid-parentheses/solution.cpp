#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<string>& v)
{
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		out << '"' << x << '"';
		first = false;
	}
	out << ']';
	return out;
}

class Solution {
private:
	unordered_set<string> removeInvalidCloseParentheses(const string& s) {
		unordered_set<string> result = {""};
		auto start = s.begin();
		int balance = 0;
		for (auto it = s.begin(); it != s.end(); ++it) {
			if (*it == '(')
				++balance;
			if (*it == ')')
				--balance;
			if (balance >= 0)
				continue;
			balance = 0;
			unordered_set<string> new_result;
			for (string result_str : result) {
				result_str.append(start, it);
				new_result.insert(result_str);
				result_str.push_back(*it);
				bool prev_is_paren = true;
				for (int pos = result_str.size() - 1; pos >= 0; --pos) {
					if (result_str[pos] != ')') {
						prev_is_paren = false;
						continue;
					}
					if (prev_is_paren)
						continue;
					string new_str = result_str;
					new_str.erase(pos, 1);
					new_result.insert(new_str);
				}
			}
			swap(result, new_result);
			start = it + 1;
		}
		if (start != s.end()) {
			unordered_set<string> new_result;
			for (string result_str : result) {
				result_str.append(start, s.end());
				new_result.insert(result_str);
			}
			swap(result, new_result);
		}
		return result;
	}
	unordered_set<string> removeInvalidOpenParentheses(const string& s) {
		unordered_set<string> result = {""};
		auto start = s.rbegin();
		int balance = 0;
		for (auto it = s.rbegin(); it != s.rend(); ++it) {
			if (*it == '(')
				++balance;
			if (*it == ')')
				--balance;
			if (balance <= 0)
				continue;
			balance = 0;
			unordered_set<string> new_result;
			for (string result_str : result) {
				result_str.append(start, it);
				new_result.insert(result_str);
				result_str.push_back(*it);
				bool prev_is_paren = true;
				for (int pos = result_str.size() - 1; pos >= 0; --pos) {
					if (result_str[pos] != '(') {
						prev_is_paren = false;
						continue;
					}
					if (prev_is_paren)
						continue;
					string new_str = result_str;
					new_str.erase(pos, 1);
					new_result.insert(new_str);
				}
			}
			swap(result, new_result);
			start = it + 1;
		}
		unordered_set<string> new_result;
		for (string result_str : result) {
			if (start != s.rend())
				result_str.append(start, s.rend());
			reverse(result_str.begin(), result_str.end());
			new_result.insert(result_str);
		}
		swap(result, new_result);
		return result;
	}
public:
	vector<string> removeInvalidParentheses(const string& s) {
		unordered_set<string> result;
		auto tmp_result = removeInvalidCloseParentheses(s);
		for (string result_str : tmp_result) {
			auto new_result = removeInvalidOpenParentheses(result_str);
			result.merge(new_result);
		}
		return vector<string>(result.begin(), result.end());
	}
};

int main()
{
	pair<string, vector<string>> test_data[] = {
		{"", {""}},
		{"(", {""}},
		{")", {""}},
		{"a(b", {"ab"}},
		{"a)b", {"ab"}},
		{")(", {""}},
		{"a)b(c", {"abc"}},
		{"a(b)c", {"a(b)c"}},
		{"(()", {"()"}},
		{"())", {"()"}},
		{"a(b(c)d", {"ab(c)d", "a(bc)d"}},
		{"a(b(c)d)e)f", {"a(b(c)d)ef", "a(b(c)de)f", "a(b(cd)e)f"}},
		{"()())()", {"(())()", "()()()"}},
		{"(a)())()", {"(a())()", "(a)()()"}},
	};
	bool success = true;
	Solution solution;
	for (const auto& [s, expected] : test_data) {
		auto result = solution.removeInvalidParentheses(s);
		cout << '"' << s << "\" -> " << result << endl;
		if (unordered_set<string>(result.begin(), result.end()) !=
		    unordered_set<string>(expected.begin(), expected.end())) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
