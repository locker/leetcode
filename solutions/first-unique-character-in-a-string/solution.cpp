#include <iostream>
#include <string>
#include <tuple>

using namespace std;

namespace {

class Solution {
public:
	int firstUniqChar(const string& s) {
		int count['z' - 'a' + 1] = {0, };
		for (char c : s)
			++count[c - 'a'];
		for (int i = 0; i < (int)s.length(); ++i) {
			if (count[s[i] - 'a'] == 1)
				return i;
		}
		return -1;
	}
};

} // namespace

int main()
{
	const tuple<string, int> test_data[] = {
		{"leetcode", 0},
		{"loveleetcode", 2},
		{"aabb", -1},
	};
	bool success = true;
	Solution solution;
	for (const auto& [s, expected] : test_data) {
		int result = solution.firstUniqChar(s);
		cout << s << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
