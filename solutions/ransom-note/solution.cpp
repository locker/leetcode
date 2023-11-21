#include <iostream>
#include <string>
#include <tuple>

using namespace std;

namespace {

class Solution {
public:
	bool canConstruct(const string& ransom_note, const string& magazine) {
		int missing = 0;
		int count['z' - 'a' + 1] = {0, };
		for (char c : ransom_note) {
			int i = c - 'a';
			if (count[i]++ == 0)
				missing++;
		}
		for (char c : magazine) {
			int i = c - 'a';
			if (count[i] == 0)
				continue;
			if (--count[i] > 0)
				continue;
			if (--missing == 0)
				return true;
		}
		return false;
	}
};

} // namespace

int main()
{
	const tuple<string, string, bool> test_data[] = {
		{"a", "b", false},
		{"aa", "ab", false},
		{"aa", "aab", true},
	};
	bool success = true;
	Solution solution;
	for (const auto& [ransom_note, magazine, expected] : test_data) {
		bool result = solution.canConstruct(ransom_note, magazine);
		cout << "ransom_note = " << ransom_note <<
			", magazine = " << magazine << " -> " <<
			(result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: wrong result" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
