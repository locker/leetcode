#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	vector<int> findAnagrams(const string& s, const string& p) {
		vector<int> result;
		int s_len = s.length();
		int p_len = p.length();
		if (s_len < p_len)
			return result;
		int letter_count['z' - 'a' + 1] = { 0, };
		for (int i = 0; i < p_len; ++i) {
			++letter_count[s[i] - 'a'];
			--letter_count[p[i] - 'a'];
		}
		int i = 0;
		while (true) {
			bool is_anagram = true;
			for (int n: letter_count) {
				if (n != 0) {
					is_anagram = false;
					break;
				}
			}
			if (is_anagram)
				result.push_back(i);
			if (i + p_len >= s_len)
				break;
			--letter_count[s[i] - 'a'];
			++letter_count[s[i + p_len] - 'a'];
			++i;
		}
		return result;
	}
};

int main()
{
	pair<string, string> input[] = {
		{"", "a"}, // []
		{"a", "aa"}, // []
		{"ab", "ba"}, // [0]
		{"abab", "ab"}, // [0, 1, 2]
		{"cbaebabacd", "abc"}, // [0, 6]
	};
	Solution solution;
	for (const auto& p: input) {
		cout << "Input: s = \"" << p.first << "\", p = \"" <<
			p.second << '"' << endl << "Output: " <<
			solution.findAnagrams(p.first, p.second) <<
			endl << endl;
	}
	return 0;
}
