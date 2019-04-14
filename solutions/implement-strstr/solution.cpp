#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	int strStr(const string& haystack, const string& needle) {
		if (needle.empty())
			return 0;
		int needle_len = needle.length();
		int haystack_len = haystack.length();
		for (int i = 0; i < haystack_len; ++i) {
			if (needle_len > haystack_len - i)
				break;
			int j;
			for (j = 0; j < needle_len; j++) {
				if (haystack[i + j] != needle[j])
					break;
			}
			if (j == needle_len)
				return i;
		}
		return -1;
	}
};

int main()
{
	pair<string, string> input[] = {
		{ "", "" }, // 0
		{ "a", "" }, // 0
		{ "", "a" }, // -1
		{ "hello", "ll" }, // 2
		{ "aaaaa", "bba" }, // -1
		{ "abababc", "ab" }, // 0
		{ "abc", "abcdef" }, // -1
		{ "hello, world", "world" }, // 7
	};
	Solution solution;
	for (const auto& p: input) {
		const auto& haystack = p.first;
		const auto& needle = p.second;
		cout << "Input: haystack = \"" << haystack <<
			"\", needle = \"" << needle << '"' << endl <<
			"Output: " << solution.strStr(haystack, needle) <<
			endl << endl;
	}
	return 0;
}
