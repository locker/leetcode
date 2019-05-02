#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<string>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << '"' << *it << '"';
	}
	out << ']';
	return out;
}

class Solution {
public:
	bool wordBreak(const string& input, const vector<string>& dict) {
		int input_len = input.length();
		if (input_len == 0)
			return true;

		int dict_size = dict.size();
		if (dict_size == 0)
			return false;

		// Coefficients used for calculating rolling hash.
		vector<unsigned> coef(input_len);
		coef[0] = 13;
		for (int i = 1; i < input_len; ++i)
			coef[i] = coef[i - 1] * coef[0];

		// Rolling hashes of input prefixes.
		vector<unsigned> input_hash(input_len);
		for (int i = 0; i < input_len; ++i) {
			input_hash[i] = i > 0 ? input_hash[i - 1] : 0;
			input_hash[i] += coef[i] * input[i];
		}

		// Rolling hashes of dictionary words.
		vector<unsigned> dict_hash(dict_size);
		for (int i = 0; i < dict_size; ++i) {
			int len = dict[i].length();
			if (len > input_len)
				continue;
			for (int j = 0; j < len; ++j)
				dict_hash[i] += coef[j] * dict[i][j];
		}

		// Check if a dictionary word matches the input string
		// starting from the given position.
		auto match = [&](int pos, int i) {
			int len = dict[i].length();
			if (len > input_len - pos)
				return false;
			unsigned mult = 1;
			unsigned hash = input_hash[pos + len - 1];
			if (pos > 0) {
				mult = coef[pos - 1];
				hash -= input_hash[pos - 1];
			}
			if (hash != mult * dict_hash[i])
				return false;
			return input.compare(pos, len, dict[i]) == 0;
		};

		// Match the input string with every dictionary word
		// one by one until the end is reached or we run out
		// of options.

		// Input positions to examine.
		stack<int> todo;
		todo.push(0);

		// Input positions that have already been examined
		// and can be safely skipped.
		unordered_set<int> done;

		while (!todo.empty()) {
			int pos = todo.top();
			if (pos == input_len)
				return true;
			todo.pop();
			if (done.find(pos) != done.end())
				continue;
			for (int i = 0; i < dict_size; ++i) {
				if (match(pos, i))
					todo.push(pos + dict[i].length());
			}
			done.insert(pos);
		}
		return false;
	}
};

int main()
{
	pair<string, vector<string>> input[] = {
		{"", {}}, // true
		{"test", {}}, // false
		{"test", {"test"}}, // true
		{"leetcode", {"leet", "code"}}, // true
		{"applepenapple", {"apple", "pen"}}, // true
		{"helloworld", {"hell", "low", "world", "lord"}}, // false
		{"helloworld", {"hell", "low", "world", "hello"}}, // true
		{"catsandog", {"cats", "dog", "sand", "and", "cat"}}, // false
		{"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		 {"a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa"}}, // true
		{"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab",
		 {"a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa"}}, // false
	};
	Solution solution;
	for (const auto& p: input) {
		bool result = solution.wordBreak(p.first, p.second);
		cout << '"' << p.first << "\", " << p.second <<
			" => " << (result ? "true" : "false") << endl;
	}
	return 0;
}
