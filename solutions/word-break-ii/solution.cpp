#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
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
	vector<string> wordBreak(const string& input,
				 const vector<string>& dict) {
		int input_len = input.length();
		if (input_len == 0)
			return {""};

		int dict_size = dict.size();
		if (dict_size == 0)
			return {};

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

		// Maps a position in the input string to all positions
		// leading to it.
		unordered_map<int, vector<int>> backtrack;

		bool found = false;
		while (!todo.empty()) {
			int pos = todo.top();
			todo.pop();
			if (pos == input_len) {
				found = true;
				continue;
			}
			if (done.find(pos) != done.end())
				continue;
			for (int i = 0; i < dict_size; ++i) {
				if (match(pos, i)) {
					int next = pos + dict[i].length();
					backtrack[next].push_back(pos);
					todo.push(next);
				}
			}
			done.insert(pos);
		}
		if (!found)
			return {};

		// Now convert backtracking info to the result set
		// by inserting spaces into proper places.
		vector<string> result;

		vector<pair<vector<int>::iterator,
			    vector<int>::iterator>> chosen;
		int pos = input_len;
		while (true) {
			while (pos != 0) {
				auto it = backtrack.find(pos);
				chosen.emplace_back(it->second.begin(),
						    it->second.end());
				pos = *it->second.begin();
			}

			string s;
			for (auto it = chosen.rbegin() + 1;
			     pos != input_len; ++it) {
				int next = (it != chosen.rend() ?
					    *it->first : input_len);
				if (!s.empty())
					s.push_back(' ');
				s.append(input, pos, next - pos);
				pos = next;
			}
			result.push_back(move(s));

			++chosen.back().first;
			while (chosen.back().first == chosen.back().second) {
				chosen.pop_back();
				if (chosen.empty())
					return result;
				++chosen.back().first;
			}
			pos = *chosen.back().first;
		}
	}
};

int main()
{
	pair<string, vector<string>> input[] = {
		{"", {}},
		{"test", {}},
		{"test", {"test"}},
		{"leetcode", {"leet", "code"}},
		{"applepenapple", {"apple", "pen"}},
		{"helloworld", {"hell", "low", "world", "lord"}},
		{"helloworld", {"hell", "low", "world", "hello"}},
		{"catsandog", {"cats", "dog", "sand", "and", "cat"}},
		{"catsanddog", {"cat", "cats", "and", "sand", "dog"}},
		{"pineapplepenapple",
		 {"apple", "pen", "applepen", "pine", "pineapple"}},
	};
	Solution solution;
	for (const auto& p: input) {
		cout << '"' << p.first << "\", " << p.second << " => " <<
			solution.wordBreak(p.first, p.second) << endl;
	}
	return 0;
}
