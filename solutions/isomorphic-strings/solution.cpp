#include <iostream>
#include <limits>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	bool isIsomorphic(const string& s, const string& t) {
		if (s.length() != t.length())
			return false;
		const int map_size = numeric_limits<char>::max() + 1;
		char map1[map_size] = { 0, };
		char map2[map_size] = { 0, };
		for (auto it1 = s.begin(), it2 = t.begin();
		     it1 != s.end(); ++it1, ++it2) {
			int c1 = *it1, c2 = *it2;
			if (map1[c1] == 0)
				map1[c1] = c2;
			if (map2[c2] == 0)
				map2[c2] = c1;
			if (map1[c1] != c2)
				return false;
			if (map2[c2] != c1)
				return false;
		}
		return true;
	}
};

int main()
{
	pair<string, string> input[] = {
		{"", ""}, // true
		{"a", ""}, // false
		{"a", "b"}, // true
		{"ab", "aa"}, // false
		{"aa", "bb"}, // true
		{"aa", "bc"}, // false
		{"egg", "add"}, // true
		{"foo", "bar"}, // false
		{"paper", "title"}, // true
	};
	Solution solution;
	for (const auto& p: input) {
		cout << '"' << p.first << "\" and \"" << p.second << '"';
		if (solution.isIsomorphic(p.first, p.second))
			cout << " are ";
		else
			cout << " are not ";
		cout << "isomorphic strings" << endl;
	}
	return 0;
}
