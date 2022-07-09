#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	bool first = true;
	for (const auto& x : v) {
		if (!first)
			out << ',';
		out << x;
		first = false;
	}
	out << ']';
	return out;
}

class Solution {
public:
	int maxProduct(const vector<string>& words) {
		const int size = words.size();
		vector<uint32_t> maps(size, 0);
		for (int i = 0; i < size; ++i) {
			for (char c : words[i]) {
				assert(c >= 'a' && c <= 'z');
				maps[i] |= 1 << (c - 'a');
			}
		}
		int max_product = 0;
		for (int i = 0; i < size; ++i) {
			for (int j = i + 1; j < size; ++j) {
				if ((maps[i] & maps[j]) == 0) {
					int product = words[i].length() * words[j].length();
					max_product = max(max_product, product);
				}
			}
		}
		return max_product;
	}
};

int main()
{
	const pair<vector<string>, int> test_data[] = {
		{{"abcw", "baz", "foo", "bar", "xtfn", "abcdef"}, 16},
		{{"a", "ab", "abc", "d", "cd", "bcd", "abcd"}, 4},
		{{"a", "aa", "aaa", "aaaa"},  0},
	};
	bool success = true;
	Solution solution;
	for (const auto& [words, expected] : test_data) {
		int result = solution.maxProduct(words);
		cout << words << " -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
