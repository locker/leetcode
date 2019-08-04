#include <iostream>

using namespace std;

class Solution {
public:
	bool checkPerfectNumber(int num) {
		if (num <= 1)
			return false;
		int sum = 1;
		for (int i = 2; i * i <= num; ++i) {
			if (num % i == 0) {
				sum += i;
				int j = num / i;
				if (i != j)
					sum += j;
			}
			if (sum > num)
				break;
		}
		return sum == num;
	}
};

int main()
{
	int left = 0, right = 10000;
	cout << "Perfect numbers between " << left << " and " << right << ": [";

	Solution solution;
	bool first = true;
	for (int num = left; num <= right; ++num) {
		if (solution.checkPerfectNumber(num)) {
			if (first)
				first = false;
			else
				cout << ',';
			cout << num;
		}
	}
	cout << ']' << endl;
	return 0;
}
