#include <iostream>
#include <limits>
#include <string>

using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(const string& s) {
		int count[numeric_limits<unsigned char>::max() + 1] = { 0 };
		string::size_type i, j;
		int max_len = 0, len = 0;

		for (i = 0, j = 0; i < s.length(); ++i) {
			++len;
			int c = s[i];
			if (++count[c] == 1) {
				if (max_len < len)
					max_len = len;
				continue;
			}
			while (count[c] > 1) {
				int c_j = s[j++];
				--count[c_j];
				--len;
			}
		}
		return max_len;
	}
};

int main()
{
	const char *input[] = {
		"",
		"abcde",
		"abcabcbb",
		"bbbbb",
		"pwwkew",
	};
	auto solution = Solution();
	for (auto s: input) {
		cout << '\"' << s << "\" => " <<
			solution.lengthOfLongestSubstring(s) << endl;
	}
	return 0;
}
