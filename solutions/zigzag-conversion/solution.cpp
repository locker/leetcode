#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class Solution {
public:
	string convert(const string& s, int n) {
		if (n <= 1)
			return s;
		int len = s.length();
		string result;
		result.reserve(len);
		for (int i = 0; i < min(n, len); ++i) {
			int delta[2];
			if (i > 0 && i < n - 1) {
				delta[0] = 2 * (n - i - 1);
				delta[1] = 2 * i;
			} else {
				delta[0] = delta[1] = 2 * (n - 1);
			}
			int delta_idx = 0;
			for (int j = i; j < len; j += delta[delta_idx++ % 2])
				result.push_back(s[j]);
		}
		return result;
	}
};

int main()
{
	pair<const char *, int> input[] = {
		{ "", 1 },
		{ "PAYPALISHIRING", 1 },
		{ "PAYPALISHIRING", 3 },
		{ "PAYPALISHIRING", 4 },
		{ "PAYPALISHIRING", 100 },
	};
	Solution solution;
	for (auto it: input) {
		cout << '\"' << it.first << "\", " << it.second << " => \"" <<
			solution.convert(it.first, it.second) << '\"' << endl;
	}
	return 0;
}
