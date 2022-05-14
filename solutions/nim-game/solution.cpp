#include <iostream>
#include <utility>

using namespace std;

class Solution {
public:
	bool canWinNim(int n) {
		// 1, 2, 3 - win in one turn.
		// 4 - lose, because on the next turn there will be 1, 2, or 3
		// stones remaining.
		// 5, 6, 7 - win, because we can remove so many stones to leave
		// the opponent 4 stores, which will result in their loss.
		// 8 - lose.

		return n % 4 != 0;
	}
};

int main()
{
	const pair<int, bool> test_data[] = {
		{1, true},
		{2, true},
		{3, true},
		{4, false},
		{7, true},
		{8, false},
		{9, true},
		{12, false}
	};
	bool success = true;
	Solution solution;
	for (const auto& [n, expected] : test_data) {
		bool result = solution.canWinNim(n);
		cout << n << " -> " << (result ? "true" : "false") << endl;
		if (result != expected) {
			cout << "  ERROR: wrong!" << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
