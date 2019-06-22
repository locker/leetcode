#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
	bool isSubsequence(const string& s, const string& t) {
		if (s.empty())
			return true;
		if (t.empty())
			return false;

		//
		// The solution is optimized for the case when t is very long
		// and used for multiple s. It has O(len(s) * log(len(t))) time
		// complexity provided the index is built just once. Without
		// indexing t, we could solve the problem without extra memory
		// using the greedy approach, but then the solution would have
		// O(max(len(s), len(t))) complexity.
		//

		unordered_map<char, vector<int>> index;
		for (auto it = t.begin(); it != t.end(); ++it)
			index[*it].push_back(it - t.begin());

		int pos = 0;
		for (auto c: s) {
			const auto& positions = index[c];
			auto it = lower_bound(positions.begin(),
					      positions.end(), pos);
			if (it == positions.end())
				return false;
			pos = *it + 1;
		}
		return true;
	}
};

int main()
{
	pair<string, string> input[] = {
		{"", ""}, // true
		{"a", ""}, // false
		{"", "a"}, // true
		{"a", "b"}, // false
		{"a", "a"}, // true
		{"ab", "xbxax"}, // false
		{"abc", "ahbgdc"}, // true
		{"axc", "ahbgdc"}, // false
	};
	Solution solution;
	for (const auto& p: input) {
		cout << "Input: s = \"" << p.first << "\", t = \"" <<
			p.second << '"' << endl << "Output: ";
		if (solution.isSubsequence(p.first, p.second))
			cout << "true";
		else
			cout << "false";
		cout << endl;
	}
	return 0;
}
