#include <iostream>
#include <limits>

using namespace std;

class Solution {
public:
	int mySqrt(int x) {
		if (x <= 1)
			return x;
		int begin = 1;
		int end = x;
		while (begin < end) {
			int mid = begin + (end - begin) / 2;
			int sqrt = x / mid;
			if (sqrt == mid)
				return mid;
			if (sqrt < mid)
				end = mid;
			else
				begin = mid + 1;
		}
		return begin - 1;
	}
};

int main()
{
	int input[] = {
		0, // 0
		1, // 1
		4, // 2
		8, // 2
		9, // 3
		27, // 5
		35, // 5
		36, // 6
		50, // 7
	};
	Solution solution;
	for (int x: input)
		cout << "sqrt(" << x << ") = " << solution.mySqrt(x) << endl;
	return 0;
}
