#include <iostream>
#include <limits>

using namespace std;

class Solution {
public:
	bool isUgly(int num) {
		if (num <= 0)
			return false;
		while (num % 2 == 0)
			num /= 2;
		while (num % 3 == 0)
			num /= 3;
		while (num % 5 == 0)
			num /= 5;
		return num == 1;
	}
};

int main()
{
	int input[] = {
		numeric_limits<int>::min(),
		-100, -60, -55, 0, 1, 2, 3, 4, 5, 7,
		10, 14, 20, 32, 47, 48, 55, 125, 375,
		numeric_limits<int>::max(),
	};
	Solution solution;
	for (int num: input) {
		cout << num << " is ";
		if (!solution.isUgly(num))
			cout << "not ";
		cout << "ugly" << endl;
	}
	return 0;
}
