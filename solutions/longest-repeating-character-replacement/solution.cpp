#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>

using namespace std;

namespace {

class Solution {
public:
	int characterReplacement(const string& s, int k) {
		const int len = s.length();
		struct LetterRange {
			int begin;
			int end;
			LetterRange(int b, int e) : begin(b), end(e) {}
		};
		struct LetterState {
			int letter_count = 0;
			int change_count = 0;
			queue<LetterRange> ranges;
		};
		int result = 0;
		LetterState letter_state['Z' - 'A' + 1];
		for (auto& ls : letter_state)
			ls.ranges.emplace(0, 0);
		for (int i = 0; i < len; ++i) {
			char letter = s[i];
			auto& ls = letter_state[letter - 'A'];
			int count = len - ls.ranges.back().end;
			result = max(result, ls.letter_count +
				     min(k, ls.change_count + count));
			++ls.letter_count;
			if (i == 0 || s[i - 1] == letter) {
				++ls.ranges.back().end;
				continue;
			}
			while (true) {
				int count = i - ls.ranges.back().end;
				if (ls.change_count + count <= k) {
					ls.change_count += count;
					break;
				}
				auto r = ls.ranges.front();
				ls.ranges.pop();
				ls.letter_count -= r.end - r.begin;
				if (ls.ranges.empty())
					break;
				ls.change_count -= ls.ranges.front().begin - r.end;
			}
			ls.ranges.emplace(i, i + 1);
		}
		for (auto& ls : letter_state) {
			int count = max(len - ls.ranges.back().end,
					ls.ranges.front().begin - 1);
			result = max(result, ls.letter_count +
				     min(k, ls.change_count + count));
		}
		return result;
	}
};

} // namespace

int main()
{
	const tuple<string, int, int> test_data[] = {
		{"A", 0, 1},
		{"AB", 0, 1},
		{"AB", 1, 2},
		{"AAAA", 2, 4},
		{"ABAB", 2, 4},
		{"ABCDA", 3, 5},
		{"ABCDAX", 3, 5},
		{"AABABBA", 1, 4},
		{"ABCDEEEE", 4, 8},
		{"EEEEABCD", 4, 8},
		{"AAAAABBBBCBB", 4, 10},
		{"AAAAABBBBCBBA", 4, 10},
		{"EOEMQLLQTRQDDCOERARHGAAARRBKCCMFTDAQOLOKARBIJBISTGNKBQGKKTALSQNFSABASNOPBMMGDIOETPTDICRBOMBAAHINTFLH", 7, 11},
	};
	bool success = true;
	Solution solution;
	for (const auto& [s, k, expected] : test_data) {
		int result = solution.characterReplacement(s, k);
		cout << "s = \"" << s << "\", k = " << k <<
			" -> " << result << endl;
		if (result != expected) {
			cout << "  ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
