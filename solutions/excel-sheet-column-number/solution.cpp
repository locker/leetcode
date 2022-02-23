#include <cassert>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	int titleToNumber(const string& title) {
		int num = 0;
		unsigned exp = 1;
		for (auto it = title.rbegin(); it != title.rend(); ++it) {
			auto c = *it;
			assert(c >= 'A' && c <= 'Z');
			int val = c - 'A' + 1;
			num += val * exp;
			exp *= 26;
		}
		return num;
	}
};

int main()
{
	pair<string, int> test_data[] = {
		{"A", 1},
		{"C", 3},
		{"Z", 26},
		{"AA", 27},
		{"AB", 28},
		{"FXSHRXW", 2147483647},
	};
	bool success = true;
	Solution solution;
	for (const auto& [title, expected] : test_data) {
		auto result = solution.titleToNumber(title);
		cout << title << " => " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
