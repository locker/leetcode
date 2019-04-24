#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

class Solution {
public:
	string minWindow(const string& s, const string& t) {
		int len = s.length();
		if (s.empty() || t.empty())
			return "";

		// Current window.
		int win_pos = 0, win_len = 0;
		// Minimal window.
		int min_win_pos = 0, min_win_len = 0;
		// Set if a window containing all characters of t
		// has been found and min_win_pos and min_win_len
		// are valid.
		bool min_win_found = false;
		// Map: character of t => number of times it's
		// missing in the current window of s.
		unordered_map<char, int> missing_count;
		for (auto c: t)
			++missing_count[c];
		// Number of characters of t that remains to be found.
		int missing_chars = missing_count.size();

		while (true) {
			// Expand the current window to the right
			// until all characters of t are found.
			while (win_pos + win_len < len && missing_chars > 0) {
				auto c = s[win_pos + win_len++];
				auto it = missing_count.find(c);
				if (it != missing_count.end()) {
					if (--it->second == 0)
						--missing_chars;
				}
			}
			if (missing_chars > 0) {
				// Scanned the whole string till the end
				// and haven't found a fit window. Stop.
				break;
			}

			// Shrink the window from the left while
			// it still contains all characters of t.
			int next_win_pos = win_pos;
			do {
				auto c = s[next_win_pos++];
				auto it = missing_count.find(c);
				if (it != missing_count.end() &&
				    it->second++ == 0)
					++missing_chars;
			} while (missing_chars == 0);

			win_len -= next_win_pos - win_pos - 1;
			win_pos = next_win_pos - 1;

			// Check if the found window is a better fit.
			if (!min_win_found || win_len < min_win_len) {
				min_win_pos = win_pos;
				min_win_len = win_len;
				min_win_found = true;
			}

			// Proceed to the next window.
			win_pos = next_win_pos;
			--win_len;
		}
		return s.substr(min_win_pos, min_win_len);
	}
};

int main()
{
	pair<string, string> input[] = {
		{"", "A"}, // ""
		{"A", ""}, // ""
		{"A", "AA"}, // ""
		{"AA", "A"}, // "A"
		{"AA", "AA"}, // "AA"
		{"ABA", "B"}, // "B"
		{"ABAB", "ABC"}, // ""
		{"BACBA", "BCB"}, // "BACB"
		{"AXXBXXCXBXAC", "ABC"}, // "BXAC"
		{"ADOBECODEBANC", "ABC"}, // "BANC"
	};
	Solution solution;
	for (const auto& p: input) {
		cout << '"' << p.first << "\", \"" << p.second << "\" => \"" <<
			solution.minWindow(p.first, p.second) << '"' << endl;
	}
	return 0;
}
