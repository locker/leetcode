#include <iostream>

using namespace std;

class Solution {
public:
	int trailingZeroes(int n) {
		// A trailing zero is a product of 5 and 2. There are
		// always more 2s than 5s in a factorial so all we need
		// to do is count 5s participating in the product.
		int result = 0;
		while (n > 0) {
			result += (n /= 5);
		}
		return result;
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n <= 100; n < 10 ? ++n : n += 10)
		cout << n << " => " << solution.trailingZeroes(n) << endl;
	return 0;
}
