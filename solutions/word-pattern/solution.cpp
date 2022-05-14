#include <iostream>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
	bool wordPattern(const string& p, const string& s) {
		const int p_len = p.length();
		const int s_len = s.length();
		unordered_set<string_view> words;
		unordered_map<char, string_view> letter_word;
		int i = 0, j = 0;
		while (i < p_len && j < s_len) {
			char letter = p[i];
			int count = 0;
			while (j + count < s_len && s[j + count] != ' ')
				++count;
			string_view word(s.c_str() + j, count);
			auto found = letter_word.find(letter);
			if (found == letter_word.end()) {
				if (words.find(word) != words.end())
					return false;
				letter_word[letter] = word;
				words.insert(word);
			} else {
				if (found->second != word)
					return false;
			}
			j += count + 1;
			++i;
		}
		return i >= p_len && j >= s_len;
	}
};

int main()
{
	const tuple<string, string, bool> test_data[] = {
		{"", "", true},
		{"w", "", false},
		{"", "what", false},
		{"f", "freak", true},
		{"fw", "weird", false},
		{"f", "weird freak", false},
		{"fw", "weird freak", true},
		{"ff", "weird freak", false},
		{"abba", "dog cat cat dog", true},
		{"abba", "dog dog dog dog", false},
		{"abba", "dog cat cat fish", false},
		{"aaaa", "dog cat cat dog", false},
	};
	bool success = true;
	Solution solution;
	for (const auto& [pattern, s, expected] : test_data) {
		bool result = solution.wordPattern(pattern, s);
		cout << "pattern = \"" << pattern << "\", s = \"" << s << "\" -> " <<
			(result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: wrong!" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
