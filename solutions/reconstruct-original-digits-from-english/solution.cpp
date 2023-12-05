#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>

using namespace std;

namespace {

class Solution {
public:
	string originalDigits(const string& s) {
		const pair<string, int> digits[] = {
			{"zero", 0},
			{"four", 4},
			{"three", 3},
			{"two", 2},
			{"eight", 8},
			{"six", 6},
			{"one", 1},
			{"five", 5},
			{"seven", 7},
			{"nine", 9},
		};
		int char_count['z' - 'a' + 1] = {0, };
		for (char c : s)
			++char_count[c - 'a'];
		string result;
		for (const auto& [digit_str, digit] : digits) {
			int count = numeric_limits<int>::max();
			for (char c : digit_str)
				count = min(count, char_count[c - 'a']);
			if (count > 0) {
				for (char c : digit_str)
					char_count[c - 'a'] -= count;
				result.append(count, '0' + digit);
			}
		}
		sort(result.begin(), result.end());
		return result;
	}
};

} // namespace

int main()
{
	const tuple<string, string> test_data[] = {
		{"owoztneoer", "012"},
		{"fviefuro", "45"},
		{"zeroonetwothreefourfivesixseveneightnine", "0123456789"},
	};
	bool success = true;
	Solution solution;
	for (const auto& [s, expected] : test_data) {
		auto result = solution.originalDigits(s);
		cout << s << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
