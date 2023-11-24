#include <iostream>
#include <string>
#include <tuple>

using namespace std;

namespace {

class Solution {
public:
	char findTheDifference(const string& s, const string& t) {
		int sc['z' - 'a' + 1] = {0, };
		int tc['z' - 'a' + 1] = {0, };
		for (char c : s)
			++sc[c - 'a'];
		for (char c : t)
			++tc[c - 'a'];
		for (char c = 'a'; c <= 'z'; ++c) {
			if (sc[c - 'a'] != tc[c - 'a'])
				return c;
		}
		return '\0';
	}
};

} // namespace

int main()
{
	const tuple<string, string, char> test_data[] = {
		{"", "y", 'y'},
		{"ab", "baa", 'a'},
		{"abcd", "abcde", 'e'},
	};
	bool success = true;
	Solution solution;
	for (const auto& [s, t, expected] : test_data) {
		char result = solution.findTheDifference(s, t);
		cout << "s = \"" << s << "\", t = \"" << t <<
			"\" -> '" << result << '\'' << endl;
		if (result != expected) {
			cout << "  ERROR: expected '" <<
				expected << '\'' << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
