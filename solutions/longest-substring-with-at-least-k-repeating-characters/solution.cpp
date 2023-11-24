#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

namespace {

class Solution {
private:
	int helper(const string& s, int begin, int end, int k, int count[]) {
		int sub_count['z' - 'a' + 1] = {0, };
		int ret = 0;
		for (int i = begin; i <= end; ++i) {
			if (i == end) {
				ret = max(ret, end - begin);
				break;
			}
			if (count[s[i] - 'a'] >= k) {
				++sub_count[s[i] - 'a'];
				continue;
			}
			ret = max(ret, helper(s, begin, i, k, sub_count));
			begin = i + 1;
			for (char c = 'a'; c <= 'z'; ++c) {
				count[c - 'a'] -= sub_count[c - 'a'];
				sub_count[c - 'a'] = 0;
			}
		}
		return ret;
	}
public:
	int longestSubstring(const string& s, int k) {
		int count['z' - 'a' + 1] = {0, };
		for (char c : s)
			++count[c - 'a'];
		return helper(s, 0, s.size(), k, count);
	}
};

} // namespace

int main()
{
	const tuple<string, int, int> test_data[] = {
		{"aa", 3, 0},
		{"aba", 2, 0},
		{"aaabb", 3, 3},
		{"ababbc", 2, 5},
		{"ababacb", 3, 0},
	};
	bool success = false;
	Solution solution;
	for (const auto& [s, k, expected] : test_data) {
		int result = solution.longestSubstring(s, k);
		cout << "s = \"" << s << "\", k = " << k <<
			" -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
