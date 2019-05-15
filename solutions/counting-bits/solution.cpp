#include <iostream>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
	out << '[';
	for (auto it = v.begin(); it != v.end(); ++it) {
		if (it != v.begin())
			out << ',';
		out << *it;
	}
	out << ']';
	return out;
}

class Solution {
public:
	vector<int> countBits(int num) {
		//
		// Decimal  Binary   Bit count
		//    0      0000    0 = f(0)
		//    1      0001    1 = 1 + f(0)
		//    2      0010    1 = 1 + f(0)
		//    3      0011    2 = 1 + f(1)
		//    4      0100    1 = 1 + f(0)
		//    5      0101    2 = 1 + f(1)
		//    6      0110    2 = 1 + f(2)
		//    7      0111    3 = 1 + f(3)
		//    8      1000    1 = 1 + f(0)
		//    9      1001    2 = 1 + f(1)
		//   10      1010    2 = 1 + f(2)
		//   11      1011    3 = 1 + f(3)
		//   12      1100    2 = 1 + f(4)
		//   13      1101    3 = 1 + f(5)
		//   14      1110    3 = 1 + f(6)
		//   15      1111    4 = 1 + f(7)
		//
		// You should see the pattern now.
		//
		vector<int> count(num + 1);
		int shift = 1;
		for (int i = 1; i <= num; ++i) {
			if (i == shift * 2)
				shift *= 2;
			count[i] = 1 + count[i - shift];
		}
		return count;
	}
};

int main()
{
	Solution solution;
	for (int i = 0; i <= 20; i += (i < 5 ? 1 : 5))
		cout << i << " => " << solution.countBits(i) << endl;
	return 0;
}
