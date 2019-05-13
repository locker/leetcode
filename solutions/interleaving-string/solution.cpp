#include <iostream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>

using namespace std;

namespace std {
template<> struct hash<pair<int, int>> {
	size_t operator()(const pair<int, int>& val) const {
		return hash<int>{}(val.first) ^ (hash<int>{}(val.second) << 1);
	}
};
};

class Solution {
public:
	bool isInterleave(const string& s1, const string& s2, const string& s3) {
		int len1 = s1.length();
		int len2 = s2.length();
		int len3 = s3.length();
		if (len1 + len2 != len3)
			return false;

		// Stack of positions to check. Stores pairs (i1, i2)
		// that identify s1 and s2 indexes to check against s3
		// at i1 + i2. We start with i1 = 0 and i2 = 0.
		stack<pair<int, int>> todo;
		todo.emplace(0, 0);

		// Dynamic programming element: set of pairs (i1, i2)
		// that have already been checked. Apparently, this
		// limits the time complexity of the algorithm by
		// O(len1 * len2).
		unordered_set<pair<int, int>> done;

		while (!todo.empty()) {
			auto p = todo.top();
			todo.pop();
			if (done.find(p) != done.end())
				continue; // already seen this one

			int i1 = p.first;
			int i2 = p.second;
			if (i1 == len1 && i2 == len2)
				return true; // reached the string end

			done.emplace(i1, i2);

			// Advance i1 and/or i2 if possible and repeat.
			int i3 = i1 + i2;
			if (i1 < len1 && s1[i1] == s3[i3])
				todo.emplace(i1 + 1, i2);
			if (i2 < len2 && s2[i2] == s3[i3])
				todo.emplace(i1, i2 + 1);
		}
		return false;
	}
};

int main()
{
	tuple<string, string, string> input[] = {
		{"", "", ""}, // true
		{"", "", "a"}, // false
		{"a", "", "a"}, // true
		{"a", "a", "a"}, // false
		{"a", "b", "ab"}, // true
		{"abb", "abc", "abbcba"}, // false
		{"aabcc", "dbbca", "aadbbcbcac"}, // true
		{"aabcc", "dbbca", "aadbbbaccc"}, // false
	};
	Solution solution;
	for (const auto& t: input) {
		const auto& s1 = get<0>(t);
		const auto& s2 = get<1>(t);
		const auto& s3 = get<2>(t);
		auto result = solution.isInterleave(s1, s2, s3);
		cout << "Input: s1 = \"" << s1 << "\", " <<
			"s2 = \"" << s2 << "\", " <<
			"s3 = \"" << s3 << '"' << endl <<
			"Output: " << (result ? "true" : "false") <<
			endl << endl;
	}
	return 0;
}
