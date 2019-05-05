#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	bool isPalindrome(const string& s) {
		int i = 0;
		int j = s.length() - 1;
		while (i < j) {
			if (!isalnum(s[i])) {
				++i;
			} else if (!isalnum(s[j])) {
				--j;
			} else if (tolower(s[i]) == tolower(s[j])) {
				++i;
				--j;
			} else
				return false;
		}
		return true;
	}
};

int main()
{
	string input[] = {
		"", // true
		" ", // true
		"A", // true
		"AB", // false
		"AA", // true
		"ABA", // true
		" B ", // true
		" BA ", // false
		" B A B  ", // true
		"Don't nod", // true
		"Don't ever nod", // false
		"race car", // true
		"race a car", // false
		"A man, a plan, a canal: Panama", // true
	};
	Solution solution;
	for (const auto& s: input) {
		cout << '"' << s << "\" is ";
		if (!solution.isPalindrome(s))
			cout << "not ";
		cout << "a palindrome" << endl;
	}
	return 0;
}
