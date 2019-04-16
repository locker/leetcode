#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

template<typename T>
ostream& operator<<(ostream& out, const vector<vector<T>>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << endl;
		out << "  " << *it;
	}
	out << endl << ']';
	return out;
}

class Solution {
public:
	vector<vector<string>> groupAnagrams(const vector<string>& strs) {
		// Map: sorted string => found anagrams.
		unordered_map<string, vector<string>> map;
		for (const auto& s: strs) {
			string key = s;
			sort(key.begin(), key.end());
			map[key].push_back(s);
		}
		vector<vector<string>> result;
		for (auto& p: map)
			result.push_back(move(p.second));
		return result;
	}
};

int main()
{
	vector<string> input[] = {
		{},
		{"abc"},
		{"abc", "cba"},
		{"abc", "cba", "cbaa"},
		{"abc", "cba", "cbaa", "abac"},
		{"eat", "tea", "tan", "ate", "nat", "bat"},
	};
	Solution solution;
	for (const auto& strs: input) {
		cout << "Input: " << strs << endl << "Output: " << endl <<
			solution.groupAnagrams(strs) << endl << endl;
	}
	return 0;
}
