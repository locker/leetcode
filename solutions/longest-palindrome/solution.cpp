#include <iostream>
#include <string>
#include <tuple>

using namespace std;

namespace {

class Solution {
public:
	int longestPalindrome(const string& s) {
		int count[('z' - 'a' + 1) * 2] = {0, };
		for (char c : s) {
			if (c >= 'a' && c <= 'z')
				++count[c - 'a'];
			if (c >= 'A' && c <= 'Z')
				++count['z' - 'a' + 1 + c - 'A'];
		}
		int result = 0;
		bool has_odd = false;
		for (int c : count) {
			result += c / 2 * 2;
			if (c % 2 != 0)
				has_odd = true;
		}
		if (has_odd)
			++result;
		return result;
	}
};

} // namespace

int main()
{
	const tuple<string, int> test_data[] = {
		{"a", 1},
		{"abccccdd", 7},
		{"AAAAAA", 6},
	};
	bool success = true;
	Solution solution;
	for (const auto& [s, expected] : test_data) {
		int result = solution.longestPalindrome(s);
		cout << s << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
