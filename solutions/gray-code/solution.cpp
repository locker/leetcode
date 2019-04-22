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
	vector<int> grayCode(int n) {
		//
		// Steps of the algorithm:
		//
		// 1. Let X be the current value of the gray code. Init with 0.
		// 2. Let B be a bit mask of flipped bits. Init with 0.
		// 3. Append X to the result.
		// 4. Iterate through B until an unset bit is found. Let C be
		//    its ordinal number (base 0). Set it and clear all lower
		//    bits.
		// 5. If C is greater than or equal to N, stop.
		// 6. Otherwise flip bit C of X.
		// 7. Go to step 3.
		//
		// Proof of correctness:
		//
		// 1. N = 0: B = 0, X = 0 => C = 0, stop.
		//    Result = [0]. Correct.
		// 2. N = 1: B = 0, X = 0 => C = 0, B = 1, X = 1 => C = 1, stop.
		//    Result = [0, 1]. Correct.
		// 3. By design the algorithm returns all values with the
		//    highest bit N before any value with the highest bit N+1.
		// 4. Suppose the algorithm correctly enumerates gray code
		//    values with the highest bit <= N. Let X0 be the last
		//    number returned by the algorithm. The next value will
		//    be (1<<(N+1))|X0, which is correct. Then the algorithm
		//    will return (1<<(N+1))|X1, (1<<(N+1))|X2, ..., where
		//    X0, X1, X2, ... is a correct gray code sequence according
		//    to our assumption. This means that the algorithm returns
		//    a correct gray code sequence with the highest set bit N+1
		//    after enumerating all gray code values with the highest
		//    bit <= N. Proven by induction.
		//
		// Note, B actually behaves as a binary representation of
		// a monotonically growing sequence of integers 0, 1, 2, 3, ...
		// When iterating from integer i-1 to i, we flip bit C in X
		// such that bit C is set in i and unset in i-1, i.e.
		//
		//   1 << C = (i | (i - 1)) & ~(i - 1)
		//
		// Flipping bit C in X can be done with the aid of the XOR
		// operator:
		//
		//   X ^= 1 << C
		//
		int val = 0;
		vector<int> result;
		result.push_back(val);
		for (int i = 1; i < (1 << n); ++i) {
			val ^= (i | (i - 1)) & ~(i - 1);
			result.push_back(val);
		}
		return result;
	}
};

int main()
{
	Solution solution;
	for (int n = 0; n < 6; ++n)
		cout << n << " => " << solution.grayCode(n) << endl;
	return 0;
}
