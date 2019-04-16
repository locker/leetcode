#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	bool isAnagram(const string& s, const string& t) {
		int letter_count['z' - 'a' + 1] = { 0, };
		for (char c: s)
			++letter_count[c - 'a'];
		for (char c: t)
			--letter_count[c - 'a'];
		for (int n: letter_count) {
			if (n != 0)
				return false;
		}
		return true;
	}
};

int main()
{
	pair<string, string> input[] = {
		{"", ""}, // true
		{"abc", ""}, // false
		{"", "abc"}, // false
		{"abc", "abcc"}, // false
		{"aabc", "abc"}, // false
		{"car", "rat"}, // false
		{"car", "arc"}, // true
		{"anagram", "nagaram"}, //true
	};
	Solution solution;
	for (const auto& p: input) {
		cout << '"' << p.first << "\" is ";
		if (!solution.isAnagram(p.first, p.second))
			cout << "not ";
		cout << "an anagram of \"" << p.second << '"' << endl;
	}
	return 0;
}
