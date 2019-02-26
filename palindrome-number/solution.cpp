#include <iostream>

using namespace std;

class Solution {
public:
	bool isPalindrome(int x) {
		if (x < 0)
			return false;

		int n = 0;
		int digit[16];
		do {
			digit[n++] = x % 10;
			x /= 10;
		} while (x > 0);

		int i, j;
		for (i = 0, j = n - 1; i < j; i++, j--) {
			if (digit[i] != digit[j])
				return false;
		}
		return true;
	}
};

int main()
{
	auto solution = Solution();
	int input[] = { 121, -121, 0, 1, 10, 765567, 345345, 12321 };
	for (auto x: input) {
		cout << x << " is" << (solution.isPalindrome(x) ? "" : " not")
			<< " a palindrome" << endl;
	}
	return 0;
}
