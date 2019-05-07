#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const vector<int>& indices)
{
	out << '[';
	for (auto it = indices.begin(); it != indices.end(); ++it) {
		if (it != indices.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

ostream& operator<<(ostream& out, const vector<string>& words)
{
	out << '[';
	for (auto it = words.begin(); it != words.end(); ++it) {
		if (it != words.begin())
			out << ',';
		out << '"' << *it << '"';
	}
	out << ']';
	return out;
}

class Solution {
public:
	vector<int> findSubstring(const string& s, const vector<string>& words) {
		if (words.empty())
			return {};

		int s_len = s.length();
		int word_len = words[0].length();
		if (word_len > s_len)
			return {};

		// Captured window boundaries.
		int start, end;

		// Map: word => number of times it's missing in
		// the captured window of s.
		unordered_map<string, int> missing;
		for (auto s: words)
			++missing[s];

		// Number of words still missing in the captured window.
		int missing_count = missing.size();

		// Shrink the captured window from the left by one word.
		auto shrink_window = [&]() {
			auto it = missing.find(s.substr(start, word_len));
			if (it != missing.end() && ++it->second == 1)
				++missing_count;
			start += word_len;
		};

		// List of indices of found substrings.
		vector<int> indices;

		for (int offset = 0; offset < word_len; ++offset) {
			start = end = offset;
			while (end + word_len <= s_len) {
				auto it = missing.find(s.substr(end, word_len));
				if (it == missing.end()) {
					// No match. Reset the window.
					while (start < end)
						shrink_window();
					end += word_len;
					start = end;
					continue;
				}
				// Shrink the window until we can include
				// the next word into it.
				while (it != missing.end() && it->second == 0)
					shrink_window();
				// Account the next word.
				if (--it->second == 0)
					--missing_count;
				if (missing_count == 0)
					indices.push_back(start);
				end += word_len;
			}
			// Reset the map before proceeding to the next iteration.
			while (start < end)
				shrink_window();
		}
		return indices;
	}
};

int main()
{
	pair<string, vector<string>> input[] = {
		{"aaaa", {"a"}}, // [0, 1, 2, 3]
		{"aaaa", {"a", "a"}}, // [0, 1, 2]
		{"babab", {"ab", "ab"}}, // [1]
		{"aabbcdaa", {"a", "b", "c", "d"}}, // [3]
		{"barfoothefoobarman", {"foo", "bar"}}, // [0, 9]
		{"wordgoodgoodgoodbestword", {"word","good","best","word"}}, // []
		{"wordgoodgoodgoodbestword", {"word","good","best","good"}}, // [8]
	};
	Solution solution;
	for (const auto &p: input) {
		const auto& s = p.first;
		const auto& words = p.second;
		cout << "Input: " << endl <<
			"  s = \"" << s << '"' << endl <<
			"  words = " << words << endl <<
			"Output: " << solution.findSubstring(s, words) <<
			endl << endl;
	}
	return 0;
}
