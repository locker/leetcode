#include <iostream>
#include <string>
#include <unordered_map>
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

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << endl << "  " << *it;
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	vector<vector<string>> partition(const string& s) {
		int len = s.length();
		if (len == 0)
			return {};
		//
		// First, build a map of all palindromes.
		// Key: index in the string.
		// Value: lengths of palindromes starting at the index.
		//
		unordered_map<int, vector<int>> palindromes;
		for (int i = 0; i < len; ++i) {
			// One character palindrome.
			palindromes[i].push_back(1);
			// Odd palindromes with the center at the current
			// character.
			for (int j = 1; i - j >= 0 && i + j < len; ++j) {
				if (s[i - j] != s[i + j])
					break;
				palindromes[i - j].push_back(2 * j + 1);
			}
			// Even palindromes with the center at the gap
			// between the current and the previous characters.
			for (int j = 1; i - j >= 0 && i + j - 1 < len; ++j) {
				if (s[i - j] != s[i + j - 1])
					break;
				palindromes[i - j].push_back(2 * j);
			}
		}

		//
		// Now build a list of all possible palindrome partitions.
		//
		vector<vector<string>> result;

		// Backtracking state: part number => pair of iterators.
		// The first iterator points to the current choice, while
		// the second iterator is the end of all choices.
		vector<pair<vector<int>::iterator,
			    vector<int>::iterator>> backtrack;

		int pos = 0;
		do {
			// Append palindromes until we reach the end
			// of the string.
			while (pos < len) {
				auto it = palindromes.find(pos);
				backtrack.emplace_back(it->second.begin(),
						       it->second.end());
				pos += *it->second.begin();
			}

			// Append the found partition to the result.
			vector<string> partition;
			int part_start = 0;
			for (auto& p: backtrack) {
				int part_len = *p.first;
				auto part = s.substr(part_start,
						     part_len);
				partition.push_back(move(part));
				part_start += part_len;
			}
			result.push_back(move(partition));

			// Back track until we find the next choice
			// or run out of choices.
			while (!backtrack.empty()) {
				auto& p = backtrack.back();
				pos -= *p.first;
				if (++p.first != p.second) {
					pos += *p.first;
					break;
				}
				backtrack.pop_back();
			}
		} while (!backtrack.empty());
		return result;
	}
};

int main()
{
	string input[] = {
		"",
		"a",
		"aa",
		"aaa",
		"aba",
		"aab",
		"aabb",
		"ababa",
	};
	Solution solution;
	for (const auto& s: input) {
		cout << "Input: \"" << s << '"' << endl <<
			"Output: " << solution.partition(s) << endl;
	}
	return 0;
}
