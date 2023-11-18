#include <iostream>

using namespace std;

namespace {

class Solution {
public:
	int getSum(int a, int b) {
		while (b != 0) {
			int c = a ^ b;
			b = (a & b) << 1;
			a = c;
		}
		return a;
	}
};

} // namespace

int main()
{
	bool success = true;
	Solution solution;
	for (int a = -1000; a <= 1000; ++a) {
		for (int b = -1000; b <= 1000; ++b) {
			int expected = a + b;
			int result = solution.getSum(a, b);
			if (result != expected) {
				cout << "ERROR: wrong result for " <<
					a << " + " << b << ": got " <<
					result << ", expected " <<
					expected << endl;
				success = false;
			}
		}
	}
	return success ? 0 : 1;
}
