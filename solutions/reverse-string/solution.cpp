#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
	void reverseString(vector<char>& s) {
		int len = s.size();
		for (int i = 0; i < len / 2; ++i) {
			swap(s[i], s[len - i - 1]);
		}
	}
};

int main()
{
	const pair<string, string> test_data[] = {
		{"a", "a"},
		{"ab", "ba"},
		{"abc", "cba"},
		{"hello", "olleh"},
		{"Hannah", "hannaH"},
	};
	bool success = true;
	Solution solution;
	for (const auto& [s, expected] : test_data) {
		vector<char> v(s.begin(), s.end());
		solution.reverseString(v);
		string result(v.begin(), v.end());
		cout << s << " => " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
