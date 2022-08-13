#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	string reverseVowels(string s) {
		const string vowels = "aAeEiIoOuU";
		int i1 = 0;
		int i2 = s.size() - 1;
		while (i1 < i2) {
			if (vowels.find(s[i1]) == string::npos) {
				++i1;
				continue;
			}
			if (vowels.find(s[i2]) == string::npos) {
				--i2;
				continue;
			}
			swap(s[i1++], s[i2--]);
		}
		return s;
	}
};

int main()
{
	const pair<string, string> test_data[] = {
		{"ao", "oa"},
		{"aA", "Aa"},
		{"aoe", "eoa"},
		{"aob", "oab"},
		{"hello", "holle"},
		{"leetcode", "leotcede"},
	};
	bool success = true;
	Solution solution;
	for (const auto& [s, expected] : test_data) {
		auto result = solution.reverseVowels(s);
		cout << s << " => " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
