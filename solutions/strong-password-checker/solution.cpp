#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

namespace {

class Solution {
public:
	int strongPasswordChecker(const string& password) {
		const int min_len = 6;
		const int max_len = 20;
		const int break_len = 3;
		const int len = password.length();
		bool has_digit = false;
		bool has_lc = false;
		bool has_uc = false;
		for (char c : password) {
			if (c >= '0' && c <= '9')
				has_digit = true;
			if (c >= 'a' && c <= 'z')
				has_lc = true;
			if (c >= 'A' && c <= 'Z')
				has_uc = true;
		}
		int min_edits = 0;
		if (!has_digit)
			++min_edits;
		if (!has_lc)
			++min_edits;
		if (!has_uc)
			++min_edits;
		int additions = 0;
		int modifications = 0;
		int removals = 0;
		if (len < min_len) {
			int modifications = 0;
			int i0 = 0;
			int new_len = len;
			for (int i = 1; i < len; ++i) {
				if (password[i] != password[i0]) {
					i0 = i;
				} else if ((i - i0 + 1) % break_len == 0) {
					if (new_len < min_len) {
						++new_len;
						++additions;
					} else {
						++modifications;
					}
				}
			}
			if (new_len < min_len)
				additions += min_len - new_len;
		} else if (len <= max_len) {
			int i0 = 0;
			for (int i = 1; i < len; ++i) {
				if (password[i] != password[i0]) {
					i0 = i;
				} else if ((i - i0 + 1) % break_len == 0) {
					++modifications;
				}
			}
		} else {
			int new_len = len;
			vector<int> groups;
			int i0 = 0;
			for (int i = 1; i <= len; ++i) {
				if (i == len || password[i] != password[i0]) {
					if (i - i0 >= break_len)
						groups.push_back(i - i0);
					i0 = i;
				}
			}
			auto cmp = [](int a, int b) {
				if (a % break_len != b % break_len)
					return a % break_len > b % break_len;
				return a > b;
			};
			make_heap(groups.begin(), groups.end(), cmp);
			while (!groups.empty() && new_len > max_len) {
				pop_heap(groups.begin(), groups.end(), cmp);
				int& len = groups.back();
				--len;
				--new_len;
				++removals;
				if (len >= break_len) {
					push_heap(groups.begin(), groups.end(), cmp);
				} else {
					groups.pop_back();
				}
			}
			removals += new_len - max_len;
			for (int count : groups)
				modifications += count / break_len;
		}
		return removals + max(additions + modifications, min_edits);
	}
};

} // namespace

int main()
{
	const tuple<string, int> test_data[] = {
		{"a", 5},
		{"aA1", 3},
		{"aaaGG", 1},
		{"aaaaaa", 2},
		{"aacbaa", 2},
		{"aaCbaa", 1},
		{"aaCa0a", 0},
		{"aaa111", 2},
		{"1337C0d3", 0},
		{"aaaaaaaaaaaaaaaaaaaa", 6},
		{"aaaaaaaaaaaaaaaaaaaaa", 7},
		{"aaaaaaaaaaaaaaaaaaaaB", 7},
		{"bbaaaaaaaaaaaaaaacccccc", 8},
		{"aaaaaaaAAAAAA6666bbbbaaaaaaABBC", 13},
	};
	bool success = true;
	Solution solution;
	for (const auto& [password, expected] : test_data) {
		int result = solution.strongPasswordChecker(password);
		cout << password << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
