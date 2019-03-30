#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	int lengthOfLastWord(const string& s) {
		int length = 0;
		bool found_word = false;
		for (auto it = s.rbegin(); it != s.rend(); ++it) {
			if (*it != ' ') {
				++length;
				found_word = true;
			} else {
				if (found_word)
					break;
			}
		}
		return length;
	}
};

int main()
{
	string input[] = {
		"",
		"  ",
		"abc",
		"a b c",
		"abc  ",
		"abc abcde ",
		"abc abcdef",
	};
	Solution solution;
	for (auto& s: input) {
		cout << '"' << s << '"' << " => " <<
			solution.lengthOfLastWord(s) << endl;
	}
	return 0;
}
