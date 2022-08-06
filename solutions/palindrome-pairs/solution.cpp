#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		out << x;
		first = false;
	}
	out << ']';
	return out;
}

struct VectorPairHash {
	size_t operator()(const vector<int>& v) const {
		return hash<int>()(v[0]) ^ hash<int>()(v[1]);
	}
};

class Solution {
private:
	bool isPalindrome(const string& s) {
		const int l = s.length();
		for (int i = 0; i < l / 2; ++i) {
			if (s[i] != s[l - i - 1])
				return false;
		}
		return true;
	}
public:
	vector<vector<int>> palindromePairs(const vector<string>& words) {
		const int word_count = words.size();
		unordered_map<string, int> word_idx;
		for (int i = 0; i < word_count; ++i) {
			auto s = words[i];
			reverse(s.begin(), s.end());
			word_idx.emplace(move(s), i);
		}
		vector<vector<int>> palindrome_pairs;
		for (int i = 0; i < word_count; ++i) {
			const auto& s = words[i];
			const int l = s.length();
			for (int k = 0; k <= l; ++k) {
				auto it = word_idx.find(s.substr(0, k));
				if (it != word_idx.end() && it->second != i &&
				    isPalindrome(s.substr(k))) {
					vector<int> pair = {i, it->second};
					palindrome_pairs.push_back(move(pair));
				}
				if (k == 0)
					continue;
				it = word_idx.find(s.substr(k));
				if (it != word_idx.end() && it->second != i &&
				    isPalindrome(s.substr(0, k))) {
					vector<int> pair = {it->second, i};
					palindrome_pairs.push_back(move(pair));
				}
			}
		};
		return palindrome_pairs;
	}
};

int main()
{
	pair<vector<string>, vector<vector<int>>> test_data[] = {
		{
			{"abcd", "dcba", "lls", "s", "sssll"},
			{{0, 1}, {1, 0}, {3, 2}, {2, 4}},
		},
		{
			{"bat", "tab", "cat"},
			{{0, 1}, {1, 0}},
		},
		{
			{"a", ""},
			{{0, 1}, {1, 0}},
		},
	};
	bool success = true;
	Solution solution;
	for (const auto& [words, expected] : test_data) {
		auto result = solution.palindromePairs(words);
		cout << words << " => " << result << endl;
		if (unordered_multiset<vector<int>, VectorPairHash>(result.begin(), result.end()) !=
		    unordered_multiset<vector<int>, VectorPairHash>(expected.begin(), expected.end())) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
