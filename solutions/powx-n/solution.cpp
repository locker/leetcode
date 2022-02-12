#include <cmath>
#include <iostream>
#include <tuple>

using namespace std;

class Solution {
public:
	double myPow(double x, int n) {
		if (n == 0)
			return 1;
		if (x == 0)
			return 0;
		long long l = n;
		if (l < 0) {
			l = -l;
			x = 1 / x;
		}
		double result = 1;
		while (l > 0) {
			if (l % 2)
				result *= x;
			l /= 2;
			x *= x;
		}
		return result;
	}
};

int main()
{
	pair<double, int> test_data[] = {
		{0, 0},
		{0, 5},
		{1, 0},
		{1, 5},
		{2.5, 0},
		{2.5, 1},
		{2, 10},
		{2.1, 3},
		{2, -2},
		{32, 4},
		{32, -2},
		{1, -2147483648},
	};
	const double precision = 1e-5;
	bool success = true;
	Solution solution;
	for (auto [x, n] : test_data) {
		double result = solution.myPow(x, n);
		cout << x << " ^ " << n << " = " << result << endl;
		double expected = pow(x, n);
		if (fabs(expected - result) > precision) {
			cout << "ERROR: expected " << expected << endl;
			success = false;
		}
	}
	return success ? 0 : 1;
}
